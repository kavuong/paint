//
// Created by kevin on 12/8/2017.
//
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include "inputValidation.h"
#include "lineTypeEnum.h"
bool isValidInput(const int numArgsNeeded, const int numArgsRead, const bool isLastElementOnLine) {

  char lastCharacterOnLine;

  // did we read everything we needed to read?
  bool correctFormat = (numArgsRead == numArgsNeeded);

  if (isLastElementOnLine) {  // if this is supposed to be the last thing on the line
    // check that it was by reading one more character
    // and seeing it it a newline (the end of the line)
    char inputStreamArray[100];
    fgets(inputStreamArray, 100, stdin);
    sscanf(inputStreamArray, "%c", &lastCharacterOnLine);
    correctFormat = correctFormat && lastCharacterOnLine == '\n';
  }
  return correctFormat;
}
char getValidChar(const bool isLastElementOnLine) {
  const int numArgsNeeded = 1;
  int numArgsRead;
  char theCharacter;

  printf("Enter your command: ");
  numArgsRead = scanf(" %c", &theCharacter);
  if (isValidInput(numArgsNeeded, numArgsRead, isLastElementOnLine)) {
    return theCharacter;
  } else {
    return '\0';
  }
}

int * getValidInts(int * numArray, const bool isLastElementOnLine) {
  int numArgsRead;
  int num1;
  int num2;
  int num3;
  int num4;
  char lastCharOnLine;
  char inputStreamArray[100];
  fgets(inputStreamArray, 100, stdin);
  numArgsRead = sscanf(inputStreamArray, " %d %d %d %d %c", &num1, &num2, &num3, &num4, &lastCharOnLine);
  //sscanf(inputStreamArray, " %c", &lastCharOnLine);

  if (numArgsRead == 4 || lastCharOnLine == '\n') {
    numArray[0] = num1;
    numArray[1] = num2;
    numArray[2] = num3;
    numArray[3] = num4;
    return numArray;
  } else {
    return '\0';

  }
}
void getRowColNumber(int * row, int * col){

  if (*row < 1) {
    *row = 10;
    *col = 10;
    printf("The number of rows is less than 1.\n");
    printf("Making default board of 10 X 10.\n");
  }

  if (*col < 1){
    *row = 10;
    *col = 10;
    printf("The number of columns is less than 1.\n");
    printf("Making default board of 10 X 10.\n");
  }
}
void validateCmdLine(int argc, char ** argv, int * rowPtr, int * colPtr){
  if (argc == 3){
    // making sure command line arguments are completely composed of integers
    for (int i = 0; i < strlen(argv[1]); ++i){
      if (argv[1][i] != '-') {
        if (!isdigit(argv[1][i])) {
          *rowPtr = 10;
          *colPtr = 10;
          printf("The number of rows is not an integer.\n");
          printf("Making default board of 10 X 10.\n");
          return;
        }
      }
    }
    for (int j = 0; j < strlen(argv[2]); ++j){
      // accounting for negative number char first '-'
      if (argv[2][j] != '-') {
        if (!isdigit(argv[2][j])) {
          *rowPtr = 10;
          *colPtr = 10;
          printf("The number of columns is not an integer.\n");
          printf("Making default board of 10 X 10.\n");
          return;
        }
      }
    }
    sscanf(argv[1], "%d", rowPtr);
    sscanf(argv[2], "%d", colPtr);
    getRowColNumber(rowPtr, colPtr);

  }
  else if (argc == 1) {
    *rowPtr = 10;
    *colPtr = 10;
  }
  else{
    printf("Wrong number of command line arguements entered.\n"
               "Usage: ./paint.out [num_rows num_cols]\n"
               "Making default board of 10 X 10.");
    *rowPtr = 10;
    *colPtr = 10;
  }
}

bool validateWriteInput(int startRow, int startCol, int endRow, int endCol, int numRows, int numCols){
  // validate that row and col inputs are within range
  if (startRow > numRows - 1 || startRow < 0 || startCol > numCols - 1 || startCol < 0)
    return false;
  if (endRow > numRows - 1 || endRow < 0 || endCol > numCols - 1 || endCol < 0)
    return false;
  return true;
}



