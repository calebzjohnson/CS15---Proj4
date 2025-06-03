/*
 * Word.h
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/4/23
 * Purpose: Word is a struct that represents each word found when indexing the 
 * given directories in gerp. Each Word object contains the original string 
 * from the directory (stripped down first), index of its corresponding line 
 * object in the line vector, and the word string converted to its insensitive 
 * case. The Word objects make up the buckets for the Hash table created in 
 * gerp.
 */


#ifndef __WORD_H__
#define __WORD_H__

#include <iostream>
#include <string>

std::string makeInsensitive(std::string wo);

struct Word
{
    std::string word;
    int lineIndex;
    std::string wordInsensitive;
    Word() 
    {
        word = "";
        lineIndex = -1;
    }
    Word(std::string w, int l)
    {
        word = w;
        lineIndex = l;

        wordInsensitive = "";
        int stringSize = w.size();
        for (int i = 0; i < stringSize; i++) {
            char charToAdd = w[i];
            if (int(charToAdd) >= 65 and int(charToAdd) <= 90) {
                charToAdd = w[i] + 32;
            }
            wordInsensitive += charToAdd;
        }
    }
};

#endif
