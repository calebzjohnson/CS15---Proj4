/*
 * stringProcessing.cpp
 * Authors: Caleb Johnson and Owen Short
 * Date: 11/28/23
 * Purpose: TODO
 */

#include "stringProcessing.h"

using namespace std;
#include <sstream>
#include <iostream>

/*
 * stripNonAlphaNum
 * Purpose: Takes a string and removes any non alphabetical or numerical
 * characters from the start and end of it
 * Arguments: String that could contain starting or trailing invalid characters
 * Return: String stripped of starting and trailing invalid characters
 * Effects: None
 */
// string stripNonAlphaNum (string input) {
//     int countStart = 0;
//     int countEnd = input.size();
//     bool firstChar = false;
//     bool lastChar = false;
//     int size = input.size();

//     while (not firstChar) {
//         if (countStart == size - 1 or size == 0) {
//             return "";
//         }
//         char currChar = input[countStart];
//         if (isValidChar(currChar)) {
//             firstChar = true;
//         } else {
//             countStart++;
//         }
//     }
//     while (not lastChar) {
//         char currChar = input[countEnd];
//         if (isValidChar(currChar)) {
//             lastChar = true;
//         }
//         else {
//             countEnd--;
//         }
//     }
    
//     return input.substr(countStart, countEnd - countStart + 1);
// }

string stripNonAlphaNum(string input) {
    int countStart = 0;
    int countEnd = input.size();
    bool firstChar = false;
    bool lastChar = false;
    int size = input.size();

    // if (input.size() == 1 and isValidChar(input[0])) {
    //     return input;
    // }
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
 * isValidChar
 * Purpose: Checks if a given character is alphabetical or numerical
 * Arguments: A character to be checked
 * Return: True if it is alphabetical or numerical and false otherwise
 * Effects: None
 */
bool isValidChar(char c) {
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