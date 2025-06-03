/*
 * gerp.cpp
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/6/23
 * Purpose: This file contains an implementation of the gerp class.
 */

#include "gerp.h"

using namespace std;
#include <istream>
#include <fstream>
#include <sstream>
#include <iostream>

/*
 * Name: gerp
 * Purpose: Constructor for the gerp class
 * Argument: A string holding the directory name
 * Return: None
 * Effects: Creates the file tree that holds all the subdirectories and files in
 * a given directory, exits program if unable to find directory
 */
gerp::gerp(string directoryName) {
    FSTree directoryTree;

    // checks that directories are reachable and exits if not
    try {
        directoryTree = FSTree(directoryName);
    } catch (const runtime_error &e) {
        cout << "Could not build index, exiting.\n";
        exit(EXIT_FAILURE);
    }

    rootFileTree = directoryTree.getRoot();
    Hash hash;
    hashTable = hash;
    getWordsAndLines(rootFileTree, directoryName);
}

/*
 * Name: run
 * Purpose: Runs and executes the query loop that users run the program
 * Arguments: A reference to the output stream that outputs will print to
 * Return: None
 * Effects: None
 */
void gerp::run(ofstream &ofs) {
    string comm;

    // continues through input file till end of file (or cin till @q)
    while (not cin.eof()) {
        cout << "Query? ";
        cin >> comm;
        
        if (comm == "@q" or comm == "@quit") {
            cout << "Goodbye! Thank you and have a nice day.\n";
            return;
        } else if (comm == "@f") {
            string outputFile;
            cin >> outputFile;
            ofs.close();
            ofs.open(outputFile);
        } else if (comm == "@i" or comm == "@insensitive") {
            cin >> comm;
            handleSearch(comm, false, ofs);
        } else {
            handleSearch(comm, true, ofs);
        }
        if (cin.eof()) {
            cout << "Query? ";
        }
    }

    cout << "Goodbye! Thank you and have a nice day.\n";
    ofs.close();
}

/*
 * Name: getWordsAndLines
 * Purpose: Recursively traverses the FS tree getting all the filepaths and 
 * using those to read in the files
 * Argument: A string holding the filepath to a file and a pointer to the
 * DirNode representing the root of the subtree
 * Return: None
 * Effects: None
 */
void gerp::getWordsAndLines(DirNode *r, string parentsString) {
    int numSubDirs = r->numSubDirs();
    int numFiles = r->numFiles();
    // if no sub directories --> go through all files
    if (not r->hasSubDir()) {
        for (int i = 0; i < numFiles; i++) {
            string filepath = parentsString + "/" + r->getFile(i);
            getWordsAndLinesHelper(filepath);
        }
    }
    else {
        // goes through any files before entering next sub directories
        for (int i = 0; i < numFiles; i++) {
            string filepath = parentsString + "/" + r->getFile(i);
            getWordsAndLinesHelper(filepath);
        }
        // goes through next sub directories recursively
        for (int i = 0; i < numSubDirs; i++) {
            DirNode *subDirectory(r->getSubDir(i));
            string subDirectoryName = subDirectory->getName();
            string newParentsString = parentsString + "/" + subDirectoryName;
            getWordsAndLines(subDirectory, newParentsString);
        }
    }
}

/*
 * Name: getWordsAndLinesHelper
 * Purpose: Adds all the lines from a given file into the line vector in Line
 * structs and inserts every word in the file into the hash table
 * Argument: A string with the filepath to get to that file
 * Return: None
 * Effects: None
 */
void gerp::getWordsAndLinesHelper(string filepath) {
    ifstream in;
    in.open(filepath);
    string lineStr;
    int lineNum = 1;
    filepathVector.push_back(filepath);
    int fileIndex = filepathVector.size() - 1;

    while (getline(in, lineStr)) {
        Line currLine(lineStr, fileIndex, lineNum);
        lineVector.push_back(currLine);
        getWords(currLine);
        lineNum++;
    }
}

/*
 * Name: getWords
 * Purpose: Adds all of the words from a given Line struct's linestring to the 
 * hash table
 * Argument: A given Line object
 * Return: None
 * Effects: None
 */
void gerp::getWords(Line l) {
    istringstream in(l.lineString);
    string wordStr;
    if (l.lineString.size() == 0) {
        return;
    }
    
    while (not in.eof()) {
        in >> wordStr;
        wordStr = stripNonAlphaNum(wordStr);
        if (wordStr != "") {
            Word currWord(wordStr, lineVector.size() - 1);
            hashTable.insert(currWord);
        }
    }
}

/*
 * Name: stripNonAlphaNum
 * Purpose: Takes a string and removes any non alphabetical or numerical
 * characters from the start and end of it
 * Arguments: String that could contain starting or trailing invalid characters
 * Return: String stripped of starting and trailing invalid characters
 * Effects: None
 */
string gerp::stripNonAlphaNum(string input) {
    int countStart = 0;
    int countEnd = input.size();
    bool firstChar = false;
    bool lastChar = false;
    int size = input.size();

    while (not firstChar) {
        if (countStart == size or size == 0) {
            return "";
        }
        char currChar = input[countStart];
        if (isValidChar(currChar)) {
            firstChar = true;
        } else {
            countStart++;
        }
    }
    while (not lastChar) {
        char currChar = input[countEnd];
        if (isValidChar(currChar)) {
            lastChar = true;
        }
        else {
            countEnd--;
        }
    }  
    return input.substr(countStart, countEnd - countStart + 1);
}

/*
 * Name: isValidChar
 * Purpose: Checks if a given character is alphabetical or numerical
 * Arguments: A character to be checked
 * Return: True if it is alphabetical or numerical and false otherwise
 * Effects: None
 */
bool gerp::isValidChar(char c) {
    int cVal = int(c);
    
    // characters 0-9
    if (cVal > 47 and cVal < 58) {
        return true;
    }
    // characters A-Z
    if (cVal > 64 and cVal < 91) {
        return true;
    }
    // characters a-z
    if (cVal > 96 and cVal < 123) {
        return true;
    }
    
    return false;
}

/*
 * Name: toInsensitiveWord
 * Purpose: Takes a word and returns the same word with no capital letters
 * Arguments: The string to be made lowercase
 * Return: The lowercase word
 * Effects: None
 */
string gerp::toInsensitiveWord(string w) {
    string insensitiveWord = "";
    int stringSize = w.size();

    for (int i = 0; i < stringSize; i++) {
        char charToAdd = w[i];
        if (int(charToAdd) >= 65 and int(charToAdd) <= 90) {
            charToAdd = w[i] + 32;
        }
        insensitiveWord += charToAdd;
    }

    return insensitiveWord;
}

/*
 * Name: handleSearch
 * Purpose: Searches through index and writes lines containing given word to 
 * output file
 * Arguments: string of word, boolean for if sensitive search, and a reference 
 * to the output file stream
 * Return: None
 * Effects: None
 */
void gerp::handleSearch(string w, bool sens, ofstream &ofs) {
    w = stripNonAlphaNum(w);
    // ends function if given string is empty
    if (w.size() == 0) {
        checkFound(w, false, sens, ofs);
        return;
    }
    string insensWord = toInsensitiveWord(w);
    vector <Word> wordVector = hashTable.getBucket(insensWord);
    int numWords = wordVector.size();
    int prevLineIndex = -1;
    int lineI;
    bool foundWord = false;
    // goes through all word objects in bucket corresponding to given word
    for (int i = 0; i < numWords; i++) {
        lineI = wordVector[i].lineIndex;
        if (sens) {
            if (prevLineIndex != lineI and wordVector[i].word == w) {
                prevLineIndex = wordVector[i].lineIndex;
                writeLineToFile(lineI, ofs);
                foundWord = true;
            }
        } else {
            if (prevLineIndex != lineI and 
            wordVector[i].wordInsensitive == insensWord) {
                prevLineIndex = wordVector[i].lineIndex;
                writeLineToFile(lineI, ofs);
                foundWord = true;
            }
        }
    }
    checkFound(w, foundWord, sens, ofs);
}

/*
 * Name: checkFound
 * Purpose: Writes to output file when unable to find given word 
 * Arguments: string of word, boolean for if found in index, boolean for if 
 * sensitive search, and a reference to the output file stream
 * Return: None
 * Effects: None
 */
void gerp::checkFound(string w, bool found, bool sens, std::ofstream &ofs) {
    if (not found and sens) {
        ofs << w << " Not Found. Try with @insensitive or @i.\n";
    } else if (not found and not sens) {
        ofs << w << " Not Found.\n";
    }
}

/*
 * Name: writeLineToFile
 * Purpose: Prints the path to the line, the line number, and the line string
 * of a given line to a given output filestream
 * Arguments: An integer with the index in the line vector that a word came from
 * and a reference to the output file stream
 * Return: None
 * Effects: None
 */
void gerp::writeLineToFile(int lineI, ofstream &ofs) {
    ofs << filepathVector[lineVector[lineI].fileNum] << ":" << 
    lineVector[lineI].lineNum << ": " << lineVector[lineI].lineString << endl;
}

// TEMPORARY PUBLIC TESTERS
// Hash gerp::getHashTable() {
//     return hashTable;
// }

// vector<Line> gerp::getLineVector() {
//     return lineVector;
// }

// DirNode *gerp::getRootFileTree() {
//     return rootFileTree;
// }