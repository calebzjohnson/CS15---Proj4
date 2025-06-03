/*
 * unit_tests.h
 * Authors: Caleb Johnson and Owen Short
 * Date: 11/28/23
 * Purpose: This file uses the unit_test framework to test our implementation 
 * of the phase one and two functions stripNonAlphaNum, the word constructor 
 * (Word), hash constructor (Hash), insert (Hash), rehash (Hash), and gerp 
 * constructor (gerp).
 */

#include "stringProcessing.h"
#include "Word.h"
#include "Line.h"
#include "Hash.h"
#include "gerp.h"

#include <cassert>
#include <functional>

void dummy() {}

// STRING PROCESSING TESTS
// ensures string processing works on a string with no special characters
void string_processing_string() {
    std::string test = stripNonAlphaNum("hello");
    
    assert(test == "hello");
}

// ensures string processing works on a string with special characters at the
// start
void string_processing_start_symbols() {
    std::string test = stripNonAlphaNum("$#%&hello");
    
    assert(test == "hello");
}

// ensures string processing works on a string with special characters at the
// end
void string_processing_end_symbols() {
    std::string test = stripNonAlphaNum("hello$#%&");
    
    assert(test == "hello");
}

// ensures string processing works on a string with special characters in the
// middle of the string
void string_processing_middle_symbols() {
    std::string test = stripNonAlphaNum("he&l#l*o");
    
    assert(test == "he&l#l*o");
}

// ensures string processing works on a string with special characters at the
// start, end, and middle of the string
void string_processing_all_symbols() {
    std::string test = stripNonAlphaNum("$#%&he&l#l*o$#%&");
    
    assert(test == "he&l#l*o");
}

// ensures string processing works on a string with just symbols
void string_processing_just_symbols() {
    std::string test = stripNonAlphaNum("!@#^&*$");

    assert(test == "");
}

// ensures string processing works when given an empty string
void string_processing_empty() {
    std::string test = stripNonAlphaNum("");

    assert(test == "");
}

// ensures string processing works when given a single letter word
void string_processing_one_char() {
    std::string test = stripNonAlphaNum("a");

    assert(test == "a");
}

// ensures string processing works on a single letter word surrounded by symbols
void string_processing_one_char_symbols() {
    std::string test1 = stripNonAlphaNum("{a");
    std::string test2 = stripNonAlphaNum("2}");
    std::string test3 = stripNonAlphaNum("{2}");
    std::string test4 = stripNonAlphaNum("!@#&$*2)))}");

    assert(test1 == "a");
    assert(test2 == "2");
    assert(test3 == "2");
    assert(test4 == "2");
}

// WORD AND LINE TESTS
// ensures word constructor works properly
void word_lowercase() {
    Word test("hello", 5);

    assert(test.word == "hello");
    assert(test.lineIndex == 5);
    assert(test.wordInsensitive == "hello");
}

// ensures make insensitive works on a word of all capitals
void word_uppercase() {
    Word test("HELLO", 5);

    assert(test.word == "HELLO");
    assert(test.lineIndex == 5);
    assert(test.wordInsensitive == "hello");
}

// ensures make insensitive works properly on an empty word
void word_empty() {
    Word test("", 5);

    assert(test.word == "");
    assert(test.lineIndex == 5);
    assert(test.wordInsensitive == "");
}

// ensures make insensitive works properly on a word with a mix of characters
void word_mixed_chars() {
    Word test("Abc$$DEFZ@)", 5);

    assert(test.word == "Abc$$DEFZ@)");
    assert(test.lineIndex == 5);
    assert(test.wordInsensitive == "abc$$defz@)");
}

// ensures line constructor works properly
void line_constructor() {
    Line test("Hello, this is our test.", 5, 10);

    assert(test.lineString == "Hello, this is our test.");
    assert(test.fileNum == 5);
    assert(test.lineNum == 10);
}

// HASH TESTS
// ensures the constructor associates the correct member variable values
// void hash_constructor() {
//     Hash hash;
    
//     assert(hash.getLoadFactor() == 0);
//     assert(hash.getHashSize() == 20000);
//     assert(hash.getBucketsFilled() == 0);
// }

// // ensures insert inserts a test word to the correct bucket in the table
// void hash_insert_1el() {
//     Hash hash;
//     Word test("test", 5);
//     hash.insert(test);

//     std::vector <std::vector <Word>> table = hash.getTable();
//     int bucketIndex = std::hash<std::string>{}(test.wordInsensitive) % 
//         table.size();
//     std::vector <Word> bucket = table[bucketIndex];

//     assert(bucket[0].word == "test");
// }

// ensures insert puts two of the same words with different capitalizations into
// the same list
// void hash_insert_diff_caps() {
//     Hash hash;
//     Word testNoCaps("test", 10);
//     Word testWithCaps("TeSt", 5);
//     Word testAllCaps("TEST", 8);
//     hash.insert(testNoCaps);
//     hash.insert(testWithCaps);
//     hash.insert(testAllCaps);

//     std::vector <std::vector <Word>> table = hash.getTable();
//     int bucketIndex = std::hash<std::string>{}(testNoCaps.wordInsensitive) % 
//         table.size();
//     std::vector <Word> bucket = table[bucketIndex];

//     assert(bucket[0].word == "test");
//     assert(bucket[1].word == "TeSt");
//     assert(bucket[2].word == "TEST");
// }

// ensures insert puts two of the same words with different capitalizations into
// the same list
// void hash_rehash() {
//     Hash hash;
//     Word word1("one", 10);
//     Word word2("two", 5);
//     Word word3("three", 8);
//     Word word4("four", 10);
//     Word word5("five", 5);
//     Word word6("six", 8);
//     Word word7("seven", 10);
//     Word word8("eight", 5);
//     Word word9("nine", 5);
//     Word word10("ten", 10);

//     hash.insert(word1);
//     hash.insert(word2);
//     hash.insert(word3);
//     hash.insert(word4);
//     hash.insert(word5);
//     hash.insert(word6);
//     hash.insert(word7);

//     std::vector < std::vector <Word>> table = hash.getTable();
//     int tableSize = table.size();
//     assert(tableSize == 10);

//     hash.insert(word8);
//     hash.insert(word9);
//     hash.insert(word10);
//     table = hash.getTable();
//     tableSize = table.size();

//     assert(tableSize == 20);

//     int bucketIndex = std::hash<std::string>{}(word1.wordInsensitive) % 
//     table.size();
//     std::vector <Word> bucket = table[bucketIndex];
//     assert(bucket[0].word == "one");
// }


// // GERP TESTS
// // ensures the constructor works on an empty directory
// void gerp_constructor_emptydir() {
//     gerp gerp("test_dir_empty");
//     Hash hash = gerp.getHashTable();
//     std::vector <std::vector <Word>> hashVector = hash.getTable();
//     std::vector <Line> lineVector = gerp.getLineVector();
//     int hashSize = hashVector.size();

//     for (int i = 0; i < hashSize; i++) {
//         assert(hashVector[i].size() == 0);
//     }
//     assert(lineVector.empty());
// }

// // ensures the constructor works on a directory with just files
// void gerp_constr_filedir() {
//     gerp gerp("test_dir");
//     Hash hash = gerp.getHashTable();
//     std::vector <std::vector <Word>> hashVector = hash.getTable();
//     std::vector <Line> lineVector = gerp.getLineVector();
    
//     assert(lineVector.size() == 5);

//     int helloIndex = std::hash<std::string>{}("hello") % hashVector.size();
//     int worldIndex = std::hash<std::string>{}("world") % hashVector.size();
//     int theseIndex = std::hash<std::string>{}("these") % hashVector.size();
//     int wordsIndex = std::hash<std::string>{}("words") % hashVector.size();
//     int areIndex = std::hash<std::string>{}("are") % hashVector.size();
//     int inIndex = std::hash<std::string>{}("in") % hashVector.size();
//     int fileIndex = std::hash<std::string>{}("file") % hashVector.size();
//     int twoIndex = std::hash<std::string>{}("2") % hashVector.size();

//     std::vector <Word> helloVector = hashVector[helloIndex];

//     assert(helloVector[0].wordInsensitive == "hello");
//     assert(helloVector.size() == 4);
    
//     std::vector <Word> worldVector = hashVector[worldIndex];

//     assert(worldVector[0].word == "world");
//     assert(worldVector.size() == 1);

//     std::vector <Word> theseVector = hashVector[theseIndex];

//     assert(theseVector[0].word == "These");
//     assert(theseVector.size() == 1);

//     std::vector <Word> wordsVector = hashVector[wordsIndex];

//     assert(wordsVector[0].word == "words");
//     assert(wordsVector.size() == 1);

//     std::vector <Word> areVector = hashVector[areIndex];

//     assert(areVector[0].word == "are");
//     assert(areVector.size() == 1);

//     std::vector <Word> inVector = hashVector[inIndex];

//     assert(inVector[0].word == "in");
//     assert(inVector.size() == 1);

//     std::vector <Word> fileVector = hashVector[fileIndex];

//     assert(fileVector[0].word == "file");
//     assert(fileVector.size() == 1);

//     std::vector <Word> twoVector = hashVector[twoIndex];

//     assert(twoVector[0].word == "2");
//     assert(twoVector.size() == 1);
// }