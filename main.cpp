/*
 * main.cpp
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/9/23
 * Purpose: The overall program that main.cpp runs is gerp, which indexes all 
 * files in a given directory (including files in sub directories) using a Hash 
 * table. This program allows clients to call multiple commands with the two 
 * most complex being a sensitive search and an insensitive search for a given 
 * word. Calling these commands results in every line containing the word 
 * (no duplicates) being written to the current output file, along with the 
 * filepath and the line number. One other command is @f which results in a new 
 * output file being used for the earlier two commands to write to. The last 
 * command is @q or @quit which ends the program. main.cpp uses gerp, the class 
 * that contains the query loop, the word searcher, and other important 
 * functions. gerp uses the class Hash to make the Hash table which is used 
 * throughout all of gerp to hold the index.
 */

#include "gerp.h"
using namespace std;

#include <ostream>
#include <fstream>

#include <iostream>

int main(int argc, char *argv[]) {
    // check usage
    if (argc != 3) {
        cerr << "Usage: ./gerp inputDirectory outputFile\n";
        exit(EXIT_FAILURE);
    }
    gerp gerp(argv[1]);
    ofstream ofs;
    ofs.open(argv[2]);
    gerp.run(ofs);

    return 0;
}