//
// Created by kevin on 12/8/2017.
//
#include "lineTypeEnum.h"
#include <stdbool.h>

#ifndef PAINT_INPUTVALIDATION_H
#define PAINT_INPUTVALIDATION_H
bool isValidInput(const int numArgsNeeded, const int numArgsRead, const bool isLastElementOnLine);
char getValidChar(const bool isLastElementOnLine);
int * getValidInts(int * numArray, const bool isLastElementOnLine);
void getRowColNumber(int * row, int * col);
void validateCmdLine(int argc, char ** argv, int * rowPtr, int * colPtr);
bool validateWriteInput(int startRow, int startCol, int endRow, int endCol, int numRows, int numCols);
#endif //PAINT_INPUTVALIDATION_H
