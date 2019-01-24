#include <stdio.h>
#include "inputValidation.h"
#include "board.h"
#include "commands.h"
#include "boardStruct.h"


int main(int argc, char * argv[]) {
  Board userBoard;
  validateCmdLine(argc, argv, &(userBoard.numRows), &(userBoard.numCols));
  paintProgram(userBoard);
  createBoard(&userBoard);
  printBoard(&userBoard);
  destroyBoard(&userBoard);



  return 0;
}