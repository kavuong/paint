//
// Created by kevin on 12/8/2017.
//

#include <stdio.h>
#include <stdlib.h>
#include "board.h"
#include "boardStruct.h"


void createBoard(Board * board){
  board->boardLayout = (char**)(malloc(board->numRows * sizeof(char*)));
  /*
   * blank space (*)
   * player one (X)
   * player two (O)
   */
  for (int row = 0; row < board->numRows; ++row){
    board->boardLayout[row] = (char*)(malloc(board->numCols * sizeof(char)));
    for (int col = 0; col < board->numCols; ++col){
      board->boardLayout[row][col] = '*';
    }
  }
}

void printBoard(Board * userBoard){
  for (int row = 0; row < userBoard->numRows; ++row){
    if ((userBoard->numRows - row - 1) < 10) {
      printf(" %d ", userBoard->numRows - row - 1);
    }
    else{
      printf("%d ", userBoard->numRows - row - 1);
    }

    for (int col = 0; col < userBoard->numCols; ++col){
      printf("%c ", userBoard->boardLayout[row][col]);
    }
    printf("\n");

  }
  printf("   ");

  for (int col = 0; col < userBoard->numCols; ++col){
    printf("%d ", col);
  }
  printf("\n");
}

void destroyBoard(Board * userBoard){
  //char *** boardLayout = &(userBoard->boardLayout);
  for (int row = 0; row < userBoard->numRows; ++row){
    free((userBoard->boardLayout)[row]);
  }
  free(userBoard->boardLayout);
  userBoard->boardLayout = NULL;
}