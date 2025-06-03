/*
 * gerp.h
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/6/23
 * Purpose: gerp is a class that represents the gerp program, containing the 
 * index of a directory and all of the commands possible. Clients are able to 
 * search the index for inputted words for either the sensitive or insensitive 
 * (@i) case. The program then writes to the given output file, giving it the 
 * filepath, the line number, and the line string of the lines where the given 
 * word is found. gerp also gives clients the ability to create a new output 
 * file for the lines to be written to (@f). The last command is @q or @quit 
 * that ends the query loop and the overall program. To make the index, gerp 
 * uses a Hash table of buckets of Word objects, where the table is a vector of 
 * vectors of Word objects and the buckets are vectors of Word objects.
 */

#ifndef __GERP_H__
#define __GERP_H__

#include "Hash.h"
#include "Line.h"
#include "FSTree.h"
#include "DirNode.h"

class gerp
{
    public:
        gerp(std::string directoryName);
        void run(std::ofstream &ofs);

        // temporary test functions
        // Hash getHashTable();
        // std::vector<Line> getLineVector();
        // DirNode *getRootFileTree();

    private:
        // member vars
        Hash hashTable;
        std::vector<Line> lineVector;
        std::vector<std::string> filepathVector;
        DirNode *rootFileTree;

        // member funcs
        void getWordsAndLines(DirNode *r, std::string parentsString);
        void getWordsAndLinesHelper(std::string filepath);
        void getWords(Line l);
        std::string stripNonAlphaNum(std::string input);
        bool isValidChar(char c);
        std::string toInsensitiveWord(std::string w);
        void handleSearch(std::string w, bool sens, std::ofstream &ofs);
        void checkFound(std::string w, bool found, bool sens, 
        std::ofstream &ofs);
        void writeLineToFile(int lineI, std::ofstream &ofs);
};

#endif