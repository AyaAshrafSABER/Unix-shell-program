//
// Created by aya on 07/10/18.
//
#include "parser.h"
#define LSH_RL_BUFSIZE 1024 //the size of the line.
#define LSH_TOK_BUFSIZE 64 // Maximum size of arguments to be token.
#define LSH_TOK_DELIM " \t\r\n\a"
//This function handle if the & placed at the end of the first paramenter
char* remove_and_sign(char* s, int** background){
    int i =0;
    for(i = 0; s[i] != '\0'; ++i); // find the lenghth of the input string
    if(s[i-1] == '&') { // check if the last input = "&"
        int bufsize = LSH_TOK_BUFSIZE;
        char* newstring =malloc(sizeof(char) * bufsize);
        int j = 0;
        for (j = 0; j < i -1; ++j) {
            newstring[j] = s[j];  // copy the input string to new string without &
        }
        newstring[j] = '\0';  // add thr null caracter
        **background = 1; //make the command run in the back ground
        return  newstring;
    }
    return s;
}

//read instruction to be executed from the user which maximum size = 1024
char* readInstruction(void){
    int bufsize = LSH_RL_BUFSIZE;
    char *line = malloc(sizeof(char) * bufsize); // intialize new line in heap
    char ch;
    int i = 0;
    printf("Shell> ");
    while(ch != '\n')    // terminates if user hit enter
    {
        ch = getchar();
        line[i] = ch;
        i++;
    }
    line[i] = '\0';// inserting null character at end
    return line;
}
/*This funtion return argument which will be executed*/
char **get_arguments(char *line, int* background) {
    int bufsize = LSH_TOK_BUFSIZE, position = 0;
    char **tokens = malloc(bufsize * sizeof(char*));
    char *token;

    if (!tokens) {
        fprintf(stderr, "lsh: allocation error\n");
       return NULL;
    }
    int i = 0;
    for(i = 0; line[i] != '\0'; ++i); // find the lenghth of the input string
    if (i > 1) { //check if the user enter a word or not
        token = strtok(line, LSH_TOK_DELIM); /*Trim all spaces and tabes  from the line*/
        token = remove_and_sign(token, &background);
        while (token != NULL) {
            if (strcmp(token, "&") == 0) {
                *background = 1;
            } else {
                tokens[position] = token;
                position++;
            }
            if (position >= bufsize) { // check the size to reallocate the place of the arguments array
                bufsize += LSH_TOK_BUFSIZE;
                tokens = realloc(tokens, bufsize * sizeof(char *));
                if (!tokens) {
                    fprintf(stderr, "lsh: allocation error\n");
                    return NULL;
                }
            }
            token = strtok(NULL, LSH_TOK_DELIM);
        }
        tokens[position] = NULL;
        return tokens;
    } else {
        return NULL;
    }
}



