/*
 * Hash.h
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/4/23
 * Purpose: Hash is a class that represents a Hash table of Word objects from 
 * the directory given by the client. Overall, the Hash table is made up of 
 * buckets of Word objects, where the table is a vector of vectors of Word 
 * objects and the buckets are vectors of Word objects. This class is used to 
 * insert every word needed in the index and access parts of the table in gerp. 
 * Privately, Hash expands and rehashes when necessary (load factor greater 
 * than 0.75). In the overall program, the Hash table is used to carry out the 
 * search commands in gerp.
 */


#ifndef __HASH_H__
#define __HASH_H__

#include "Word.h"

#include <vector>
#include <list>

class Hash
{
    public:
        Hash();
        void insert(Word w);
        std::vector <Word> getBucket(std::string w);
        int getBucketIndex(std::string w);
        
        // temporary test functions
        // int getHashSize();
        // float getLoadFactor();
        // int getBucketsFilled();
        // std::vector <std::vector <Word>> getTable();

    private:
        // member functions
        void checkLoadFactor();
        void expandHash();
        void rehash(std::vector <std::vector <Word>> oldTable);

        // member variables
        std::vector <std::vector <Word>> hashTable;
        float loadFactor;
        int bucketsFilled;
};

#endif