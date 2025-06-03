/*
 * Line.h
 * Author: Caleb Johnson (cjohns34) and Owen Short (oshort1)
 * Date: 12/4/23
 * Purpose: Line is a struct that represents each line found when indexing the 
 * given directories in gerp. Each Line object contains the string of that 
 * line, theindex of its corresponding file for the filepath vector, and the 
 * line number of that line in its file. The Line objects make up the line 
 * vector used in gerp for writing to the output file.
 */


#ifndef __LINE_H__
#define __LINE_H__

#include <iostream>
#include <string>

struct Line
{
    std::string lineString;
    int fileNum;
    int lineNum;

    Line() 
    {
        lineString = "";
        fileNum = -1;
        lineNum = -1;
    }
    Line(std::string ls, int f, int ln)
    {
        lineString = ls;
        fileNum = f;
        lineNum = ln;
    }
};

#endif