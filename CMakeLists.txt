cmake_minimum_required(VERSION 3.8)
project(paint)

set(CMAKE_C_STANDARD 11)
set(GCC_ENABLE_WARNINGS "-O1 -Wall -Werror -Wno-unused-result")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${GCC_ENABLE_WARNINGS}")

set(SOURCE_FILES main.c inputValidation.c inputValidation.h board.c board.h commands.c commands.h boardStruct.h lineTypeEnum.h)
add_executable(paint ${SOURCE_FILES})