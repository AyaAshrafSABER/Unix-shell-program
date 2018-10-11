//
// Created by aya on 07/10/18.
//

#ifndef C_SHELL_MAIN_H
#define C_SHELL_MAIN_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "parser.cpp"
#include <time.h>
char* line;
char** arguments;
pid_t  child_pid;
int background;
void signalHandler(int signum);
void execute();
#endif //C_SHELL_MAIN_H
