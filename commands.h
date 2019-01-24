//
// Created by kevin on 12/8/2017.
//
#include "lineTypeEnum.h"
#ifndef PAINT_COMMANDS_H
#define PAINT_COMMANDS_H
void help();
void writeChar(char * boardCell, char sameDirChar, char intersectChar);
void write(int startRow, int startCol, int endRow, int endCol, Board userBoard);
void initNewRow(Board * userBoard);
void add(Board * userBoard, rowColEnum rowOrCol, int rowColPos);
void delete(Board * userBoard, rowColEnum rowOrCol, int rowColPos);
void erase(Board * userBoard, int rowPos, int colPos);
void resize(Board * userBoard, int rowNum, int colNum);
void save(Board * userBoard, char * fileName);
void load(Board * userBoard, char * fileName);
void paintProgram(Board userBoard);
#endif //PAINT_COMMANDS_H
