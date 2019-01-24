//
// Created by kevin on 12/8/2017.
//
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "board.h"
#include "commands.h"
#include "inputValidation.h"
#include "lineTypeEnum.h"

void help(){

  printf("Commands:\n");
  printf("Help: h\n");
  printf("Quit: q\n");
  printf("Draw line: w row_start col_start row_end col_end\n");
  printf("Resize: r num_rows num_cols\n");
  printf("Add row or column: a [r | c] pos\n");
  printf("Delete row or column: d [r | c] pos\n");
  printf("Erase: e row col\n");
  printf("Save: s file_name\n");
  printf("Load: l file_name\n");

}
void writeChar(char * boardCell, char sameDirChar, char intersectChar){
  if (*boardCell == '*' || *boardCell == sameDirChar)
    *boardCell = sameDirChar;
  else
    *boardCell = intersectChar;
}
void write(int startRow, int startCol, int endRow, int endCol, Board userBoard){
  lineType userLineType;
  if (validateWriteInput(startRow, startCol, endRow, endCol, userBoard.numRows, userBoard.numCols)){
    // check if horz line
    if (startRow == endRow){
      userLineType = HORZ;
    }
      // check if vert line
    else if (startCol == endCol){
      userLineType = VERT;
    }
      // check if diag line
    else if (abs(endRow - startRow) == abs(endCol - startCol)){
      userLineType = DIAG;
    }
    else {
      printf("Cannot draw the line as it is not straight.\n");
      return;
    }
    // handles horz lines
    if (userLineType == HORZ){
      if (startCol > endCol) {
        for (int i = startCol; i >= endCol; i--) {
          writeChar(&(userBoard.boardLayout[userBoard.numRows - startRow - 1][i]), '-', '+');
        }
      }
      else if (endCol > startCol) {
        for (int j = startCol; j <= endCol; j++) {
          writeChar(&(userBoard.boardLayout[userBoard.numRows - startRow - 1][j]), '-', '+');
        }
      }
      // one cell lines always horz - including else
      else
        writeChar(&(userBoard.boardLayout[userBoard.numRows - startRow - 1][startCol]), '-', '+');
    }
    //handles vert lines
    else if (userLineType == VERT){
      if (startRow > endRow){
        for (int k = startRow; k >= endRow; k--){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - k - 1][startCol]), '|', '+');
        }
      }
      else if (endRow > startRow){
        for (int l = startRow; l <= endRow; l++){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - l - 1][startCol]), '|', '+');
        }
      }
    }
    // handles diag lines
    else if (userLineType == DIAG){
      // cases of '/' lines
      if ((startRow < endRow && startCol < endCol)){
        int colIndex = startCol;
        for (int m = startRow; m <= endRow; m++){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - m - 1][colIndex]), '/', '+');
          colIndex++;
        }
      }
      else if (startRow > endRow && startCol > endCol){
        int colIndex = startCol;
        for (int m = startRow; m >= endRow; m--){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - m - 1][colIndex]), '/', '+');
          colIndex--;
        }
      }
      // cases of '\' lines
      else if ((startRow > endRow && startCol < endCol)){
        int colIndex = startCol;
        for (int m = startRow; m >= endRow; m--){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - m - 1][colIndex]), '\\', '+');
          colIndex++;
        }
      }

      else if (startRow < endRow && startCol > endCol){
        int colIndex = startCol;
        for (int m = startRow; m <= endRow; m++){
          writeChar(&(userBoard.boardLayout[userBoard.numRows - m - 1][colIndex]), '\\', '+');
          colIndex--;
        }
      }
    }

  }
  else
    printf("Improper draw command.\n");

}

void initNewRow(Board * userBoard){
  userBoard->boardLayout[userBoard->numRows - 1] = (char*)(malloc(userBoard->numCols * sizeof(char)));
  for (int i = 0; i < userBoard->numCols; ++i){
    userBoard->boardLayout[userBoard->numRows - 1][i] = '*';
  }
}

void add(Board * userBoard, rowColEnum rowOrCol, int rowColPos){
  if (rowOrCol == ROW){
    userBoard->boardLayout = (char**) realloc(userBoard->boardLayout, (userBoard->numRows + 1) * sizeof(char*));
    (userBoard->numRows)++;
    initNewRow(userBoard);
    int realRowPos = userBoard->numRows - rowColPos - 1;
    for (int i = userBoard->numRows - 1; i > realRowPos; --i){
      for (int j = 0; j < userBoard->numCols; ++j)
        userBoard->boardLayout[i][j] = userBoard->boardLayout[i - 1][j];
    }
    // clear row to be added into
    for (int a = 0; a < userBoard->numCols; ++a)
      userBoard->boardLayout[realRowPos][a] = '*';
  }

  else if (rowOrCol == COL){
    (userBoard->numCols)++;

    for (int i = 0; i < userBoard->numRows; ++i) {
      userBoard->boardLayout[i] = (char *) realloc((userBoard->boardLayout)[i], (userBoard->numCols) * sizeof(char));
    }
    for (int j = 0; j < userBoard->numRows; ++j) {
      for (int k = userBoard->numCols - 1; k > rowColPos; k--)
        userBoard->boardLayout[j][k] = userBoard->boardLayout[j][k - 1];
    }
    // clear col to be added into
    for (int a = 0; a < userBoard->numRows; ++a)
      userBoard->boardLayout[a][rowColPos] = '*';
  }
}

void delete(Board * userBoard, rowColEnum rowOrCol, int rowColPos){
  if (rowOrCol == ROW){
    char temp = ' ';
    int realRowPos = userBoard->numRows - rowColPos - 1;
    for (int i = realRowPos; i < userBoard->numRows - 1; ++i){
      for (int j = 0; j < userBoard->numCols; j++){
        temp = (userBoard->boardLayout)[i + 1][j];
        (userBoard->boardLayout)[i + 1][j] = (userBoard->boardLayout)[i][j];
        (userBoard->boardLayout)[i][j] = temp;
      }
    }

    free((userBoard->boardLayout)[userBoard->numRows - 1]);
    (userBoard->numRows)--;
    userBoard->boardLayout = (char**) realloc(userBoard->boardLayout, (userBoard->numRows) * sizeof(char*));
  }
  if (rowOrCol == COL){
    char temp = ' ';
    for (int i = 0; i < userBoard->numRows; ++i){
      for (int j = rowColPos; j < userBoard->numCols - 1; j++){
        temp = (userBoard->boardLayout)[i][j + 1];
        (userBoard->boardLayout)[i][j + 1] = (userBoard->boardLayout)[i][j];
        (userBoard->boardLayout)[i][j] = temp;
      }
    }
    (userBoard->numCols)--;

    for (int i = 0; i < userBoard->numRows; ++i)
      (userBoard->boardLayout)[i] = (char*) realloc((userBoard->boardLayout)[i], (userBoard->numCols) * sizeof(char));
  }
}

void erase(Board * userBoard, int rowPos, int colPos){
  userBoard->boardLayout[rowPos][colPos] = '*';
}

void resize(Board * userBoard, int rowNum, int colNum) {
  char temp = ' ';
  // cases where resizing -> bigger board
  if (rowNum > userBoard->numRows && colNum > userBoard->numCols) {
    // initializing "new" board

    userBoard->boardLayout = (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i)
      userBoard->boardLayout[i] = (char *) realloc((userBoard->boardLayout)[i], colNum * sizeof(char));

    for (int j = 0; j < rowNum; ++j) {
      for (int k = 0; k < colNum; ++k) {
        if (j < userBoard->numRows) {
          if (k >= userBoard->numCols)
            userBoard->boardLayout[j][k] = '*';
          else
            continue;
        } else {
          userBoard->boardLayout[j][k] = '*';
        }
      }
    }
    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  } else if (rowNum == userBoard->numRows && colNum > userBoard->numCols) {
    for (int i = 0; i < userBoard->numRows; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = userBoard->numCols; j < colNum; ++j)
        userBoard->boardLayout[i][j] = '*';
    }
    userBoard->numCols = colNum;
  } else if (rowNum > userBoard->numRows && colNum == userBoard->numCols) {
    userBoard->boardLayout = (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    for (int i = userBoard->numRows; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = 0; j < userBoard->numCols; ++j)
        userBoard->boardLayout[i][j] = '*';
    }

    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->numRows = rowNum;
  }
    // cases where resizing -> smaller board
  else if (rowNum < userBoard->numRows && colNum < userBoard->numCols) {
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }
    for (int i = userBoard->numRows; i < rowNum; ++i){
      free(userBoard->boardLayout[i]);
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;

    for (int i = 0; i < userBoard->numRows; ++i)
      userBoard->boardLayout[i] = realloc(userBoard->boardLayout[i], colNum * sizeof(char));
    userBoard->numCols = colNum;
  } else if (rowNum == userBoard->numRows && colNum < userBoard->numCols) {
    for (int i = 0; i < userBoard->numRows; ++i) {
      userBoard->boardLayout[i] = realloc(userBoard->boardLayout[i], colNum * sizeof(char));
    }
    userBoard->numCols = colNum;
  } else if (rowNum < userBoard->numRows && colNum == userBoard->numCols) {
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    for (int i = userBoard->numRows; i < rowNum; ++i){
      free(userBoard->boardLayout[i]);
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;

  }
  // cases where resizing can go either way
  else if (rowNum > userBoard->numRows && colNum < userBoard->numCols){
    userBoard->boardLayout = (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      if (i >= userBoard->numRows) {
        for (int j = 0; j < colNum; ++j)
          userBoard->boardLayout[i][j] = '*';
      }
    }

    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  }
  else if (rowNum < userBoard->numRows && colNum > userBoard->numCols){
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = userBoard->numCols; j < colNum; ++j){
        userBoard->boardLayout[i][j] = '*';
      }
    }
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  }
}

void save(Board * userBoard, char * fileName){
  FILE * outFile = NULL;
  outFile = fopen(fileName, "w");
  char putChar = ' ';
  if (outFile != NULL) {
    for (int i = 0; i < userBoard->numRows; ++i) {
      for (int j = 0; j < userBoard->numCols; ++j) {
        putChar = userBoard->boardLayout[i][j];
        fprintf(outFile, "%c", putChar);
      }
      fprintf(outFile, "!");
    }
    fclose(outFile);
  }
}

void load(Board * userBoard, char * fileName){
  FILE * inFile = NULL;
  inFile = fopen(fileName, "r");
  char * testChar = malloc(sizeof(char));
  char * putFileChar = malloc(sizeof(char));
  bool newRow = false;
  int rowCount = 0;
  int colCount = 0;
  if (inFile != NULL) {
    while (!feof(inFile)) {
      fscanf(inFile, "%c", testChar);
      if (*testChar != '!' && !newRow) {
        colCount++;
      }
      else if (*testChar == '!') {
        rowCount++;
        newRow = true;
      }
    }
    rowCount--;


    userBoard->numRows = rowCount;
    userBoard->numCols = colCount;
    userBoard->boardLayout = (char **) (malloc(userBoard->numRows * sizeof(char *)));
    fseek(inFile, 0, SEEK_SET);

    while (!feof(inFile)) {
      for (int row = 0; row < userBoard->numRows; ++row) {
        userBoard->boardLayout[row] = (char *) (malloc(userBoard->numCols * sizeof(char)));
        for (int col = 0; col < userBoard->numCols; ++col) {
          fscanf(inFile, "%c", putFileChar);
          if (*putFileChar == '!') {
            fscanf(inFile, "%c", putFileChar);
            userBoard->boardLayout[row][col] = *putFileChar;
          } else
            userBoard->boardLayout[row][col] = *putFileChar;
        }
      }
      // exclamation point at end of file - DON'T WANT PROGRAM TO DETECT THAT
      break;
    }
    fclose(inFile);

  }
  else{
    free(inFile);
    printf("Failed to open file: %s\n", fileName);
    }
  free(testChar);
  free(putFileChar);
}

void paintProgram(Board userBoard){

  //char strInput[] = "";
  createBoard(&userBoard);
  printBoard(&userBoard);
  while (true){
    char commandChar;
    // for write function
    int * numArray = malloc(4 * sizeof(int));
    // for add function
    char rowColumnChar;
    int rowColPos = 0;
    // for erase function
    int rowPos = 0;
    int colPos = 0;
    // for resize function
    int rowNum = 0;
    int colNum = 0;
    // for save function
    char * fileName = malloc(100 * sizeof(char));

    // IF TIME: code input validation further for getValidChar
    commandChar = getValidChar(false);
    if (commandChar == '\0') {
      printf("Unrecognized command. Type h for help.\n");
      continue;
    }
    // q: quit
    if (commandChar == 'q'){
      char anyChar;
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %c", &anyChar);
      if (numArgsRead == -1) {
        destroyBoard(&userBoard);
        free(numArray);
        free(fileName);
        exit(0);
      }
      else
        printf("Unrecognized command. Type h for help.\n");

    } else if (commandChar == 'h') {
      char anyChar;
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %c", &anyChar);
      if (numArgsRead == -1)
        help();
      else
        printf("Unrecognized command. Type h for help.\n");

    }
    else if (commandChar == 'w'){
      //int numArgsRead = 0;
      // possible memory leaks here...
      numArray = getValidInts(numArray, true);


      if (numArray == '\0')
        printf("Improper draw command.\n");
      else
        write(numArray[0], numArray[1], numArray[2], numArray[3], userBoard);
    }
    else if (commandChar == 'a'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %c %d", &rowColumnChar, &rowColPos);
      if (numArgsRead == 2 && (rowColumnChar == 'r' || rowColumnChar == 'c')){
        // may be userBoard.numRows - 1 : look at piazza
        if (rowColumnChar == 'r' && rowColPos >= 0 && rowColPos <= userBoard.numRows)
          add(&userBoard, ROW, rowColPos);
        else if (rowColumnChar == 'c' && rowColPos >= 0 && rowColPos <= userBoard.numCols)
          add(&userBoard, COL, rowColPos);
        else
          printf("Improper add command.\n");
      }
      else
        printf("Improper add command.\n");
    }
    else if (commandChar == 'd'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %c %d", &rowColumnChar, &rowColPos);
      if (numArgsRead == 2 && (rowColumnChar == 'r' || rowColumnChar == 'c')){
        if (rowColumnChar == 'r' && rowColPos >= 0 && rowColPos < userBoard.numRows)
          delete(&userBoard, ROW, rowColPos);
        else if (rowColumnChar == 'c' && rowColPos >= 0 && rowColPos < userBoard.numCols)
          delete(&userBoard, COL, rowColPos);
        else
          printf("Improper delete command.\n");
      }
      else
        printf("Improper delete command.\n");
    }
    else if (commandChar == 'e'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %d %d", &rowPos, &colPos);
      if (numArgsRead == 2 && rowPos >= 0 && rowPos < userBoard.numRows && colPos >= 0 && colPos < userBoard.numCols)
        erase(&userBoard, userBoard.numRows - rowPos - 1, colPos);
      else
        printf("Improper erase command.\n");
    }
    else if (commandChar == 'r'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, " %d %d", &rowNum, &colNum);
      if (numArgsRead == 2 && rowNum >= 1 && colNum >= 1)
        resize(&userBoard, rowNum, colNum);
      else
        printf("Improper resize command.\n");
    }
    else if (commandChar == 's'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      int numArgsRead = sscanf(inputStreamArray, "%s", fileName);
      if (numArgsRead == 1)
        save(&userBoard, fileName);
      else
        printf("Improper save command or file could not be created.\n");
    }
    else if (commandChar == 'l'){
      char inputStreamArray[100];
      fgets(inputStreamArray, 100, stdin);
      //puts("Still alive");

      int numArgsRead = sscanf(inputStreamArray, "%s", fileName);
      if (numArgsRead == 1)
        load(&userBoard, fileName);
      else
        printf("Improper load command.\n");
    }

    else{
      char inputStreamArray[200];
      fgets(inputStreamArray, 200, stdin);
      printf("Unrecognized command. Type h for help.\n");
    }

    printBoard(&userBoard);
    free(numArray);
    free(fileName);
  }
}

/*
 * void resize(Board * userBoard, int rowNum, int colNum) {
  char temp = ' ';
  // cases where resizing -> bigger board
  if (rowNum > userBoard->numRows && colNum > userBoard->numCols) {
    // initializing "new" board
    userBoard->boardLayout =  (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
    }
    for (int j = 0; j < rowNum; ++j) {
      for (int k = 0; k < colNum; ++k) {
        if (j < userBoard->numRows) {
          if (k >= userBoard->numCols)
            userBoard->boardLayout[j][k] = '*';
          else
            continue;
        } else {
          userBoard->boardLayout[j][k] = '*';
        }
      }
    }
    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  } else if (rowNum == userBoard->numRows && colNum > userBoard->numCols) {
    for (int i = 0; i < userBoard->numRows; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = userBoard->numCols; j < colNum; ++j)
        userBoard->boardLayout[i][j] = '*';
    }
    userBoard->numCols = colNum;
  } else if (rowNum > userBoard->numRows && colNum == userBoard->numCols) {
    userBoard->boardLayout = (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    for (int i = userBoard->numRows; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = 0; j < userBoard->numCols; ++j)
        userBoard->boardLayout[i][j] = '*';
    }

    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->numRows = rowNum;
  }
    // cases where resizing -> smaller board
  else if (rowNum < userBoard->numRows && colNum < userBoard->numCols) {
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;
    for (int i = 0; i < userBoard->numRows; ++i)
      userBoard->boardLayout[i] = realloc(userBoard->boardLayout[i], colNum * sizeof(char));
    userBoard->numCols = colNum;
  } else if (rowNum == userBoard->numRows && colNum < userBoard->numCols) {
    for (int i = 0; i < userBoard->numRows; ++i) {
      userBoard->boardLayout[i] = realloc(userBoard->boardLayout[i], colNum * sizeof(char));
    }
    userBoard->numCols = colNum;
  } else if (rowNum < userBoard->numRows && colNum == userBoard->numCols) {
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }
    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;

  }
  // cases where resizing can go either way
  else if (rowNum > userBoard->numRows && colNum < userBoard->numCols){
    userBoard->boardLayout = (char **) realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      if (i >= userBoard->numRows) {
        for (int j = 0; j < colNum; ++j)
          userBoard->boardLayout[i][j] = '*';
      }
    }

    for (int a = userBoard->numRows - 1; a >= 0; --a) {
      int iterTotCount = rowNum - userBoard->numRows;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; ++i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i + 1][j];
          userBoard->boardLayout[i + 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  }
  else if (rowNum < userBoard->numRows && colNum > userBoard->numCols){
    for (int a = userBoard->numRows - rowNum; a < userBoard->numRows; ++a) {
      int iterTotCount = userBoard->numRows - rowNum;
      int iterCount = 0;
      for (int i = a; iterCount < iterTotCount; --i) {
        for (int j = 0; j < userBoard->numCols; j++) {
          temp = userBoard->boardLayout[i - 1][j];
          userBoard->boardLayout[i - 1][j] = userBoard->boardLayout[i][j];
          userBoard->boardLayout[i][j] = temp;
        }
        ++iterCount;
      }
    }

    userBoard->boardLayout = realloc(userBoard->boardLayout, rowNum * sizeof(char *));

    for (int i = 0; i < rowNum; ++i) {
      userBoard->boardLayout[i] = (char *) realloc(userBoard->boardLayout[i], colNum * sizeof(char));
      for (int j = userBoard->numCols; j < colNum; ++j){
        userBoard->boardLayout[i][j] = '*';
      }
    }
    userBoard->numRows = rowNum;
    userBoard->numCols = colNum;
  }
}
 */