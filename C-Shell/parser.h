//
// Created by aya on 07/10/18.
//

#ifndef C_SHELL_PARSER_H
#define C_SHELL_PARSER_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char* readInstruction();
char** get_arguments(char* line, int* backgroud);
#endif //C_SHELL_PARSER_H
