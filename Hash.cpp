/*
 * Hash.cpp
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/4/23
 * Purpose: This file contains an implementation of the Hash class.
 */

#include "Hash.h"

using namespace std;
#include <functional>

/*
 * Name: Hash
 * Purpose: Default constructor for the Hash class
 * Argument: None
 * Return: None
 * Effects: Initializes the hash vector to an empty vector of size 20000
 */
Hash::Hash() {
    loadFactor = 0;
    bucketsFilled = 0;
    vector <vector <Word>> table;
    // fill all buckets with empty vectors
    for (int i = 0; i < 20000; i++) {
        vector <Word> emptyBucket;
        table.push_back(emptyBucket);
    }
    hashTable = table;
}

/*
 * Name: insert
 * Purpose: Inserts a given Word object into the Hash table
 * Argument: A Word object
 * Return: None
 * Effects: Expands the hash vector if the load factor is too high
 */
void Hash::insert(Word w) {
    int bucketIndex = getBucketIndex(w.wordInsensitive);
    vector <Word> *bucket = &hashTable[bucketIndex];
    
    if (bucket->size() == 0) {
        bucketsFilled++;
    }
    bucket->push_back(w);

    checkLoadFactor();
}

/*
 * Name: checkLoadFactor
 * Purpose: Adjusts the load factor of the hash after the number of elements
 * changes and expands the hash vector if the load factor is too high
 * Argument: None
 * Return: None
 * Effects: Expands the hash vector if the load factor is too high
 */
void Hash::checkLoadFactor() {
    loadFactor = (float)bucketsFilled / (float)hashTable.size();
    
    if (loadFactor > 0.75) {
        expandHash();
    }
}

/*
 * Name: expandHash
 * Purpose: Expands the hash table to twice its previous size
 * Argument: None
 * Return: None
 * Effects: See purpose
 */
void Hash::expandHash() {
    vector <vector <Word>> newTable;
    vector <vector <Word>> oldTable = hashTable;

    int oldSize = hashTable.size();
    for (int i = 0; i < 2 * oldSize; i++) {
        vector <Word> emptyBucket;
        newTable.push_back(emptyBucket);
    }
    hashTable = newTable;

    rehash(oldTable);
}

/*
 * Name: rehash
 * Purpose: Rehashes all elements of the hash table to match the new expanded
 * table
 * Argument: The old table with all of the elements in their previous buckets
 * Return: None
 * Effects: Sets hashTable to be the new created vector after inserting all
 * elements into their new spots
 */
void Hash::rehash(vector <vector <Word>> oldTable) {
    bucketsFilled = 0;
    int oldSize = oldTable.size();
    // go through each bucket in the old table and insert all elements into the
    // new table
    for (int i = 0; i < oldSize; i++) {
        vector <Word> bucket = oldTable[i];
        int bucketSize = bucket.size();

        for (int j = 0; j < bucketSize; j++) {
            insert(bucket[j]);
        }
    }
}

/*
 * Name: getBucket
 * Purpose: Returns the vector of words that holds all of the words matching the
 * given word
 * Argument: A string with the word we're searching for
 * Return: A vector of words holding the words that we're searching for
 * Effects: None
 */
vector <Word> Hash::getBucket(string w) {
    int bucketIndex = getBucketIndex(w);
    return hashTable[bucketIndex];
}

/*
 * Name: getBucketIndex
 * Purpose: Gets the number of times you have to iterate through a bucket to get
 * to the list of the given word
 * Argument: The given word (Note: This word should not be case sensitive)
 * Return: The number of iterations
 * Effects: None
 */
int Hash::getBucketIndex(std::string w) {
    return hash<string>{}(w) % hashTable.size();
}


// TEMPORARY TESTERS
// int Hash::getHashSize() {
//     return hashTable.size();
// }

// float Hash::getLoadFactor() {
//     return loadFactor;
// }

// int Hash::getBucketsFilled() {
//     return bucketsFilled;
// }

// vector <vector <Word>> Hash::getTable() {
//     return hashTable;
// }