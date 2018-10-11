#include "main.h"

/*
 * this is the main function of the program */
int main()
{   remove("log.txt"); // if there is a log file this delete it to write the new running of the shell
    while(1) {
        line = readInstruction();
        background = 0;
        arguments = get_arguments(line, &background);
        execute();
        free(line);
        free(arguments);
    }
}
/*
 * this function is response for executing the incomming command*/
void execute() {
    if (arguments == NULL) {
        printf("Try to enter the input again \n");
    } else if (strcmp(arguments[0], "exit") == 0) {
        exit(0);
    }
    int stat_loc;
    child_pid = fork();
    if (child_pid == 0) {
        /* Never returns if the call is successful */
        execvp(arguments[0], arguments);
        printf("This won't be printed if the command was right\n");
    } else if (background == 0){
        waitpid(child_pid, &stat_loc, WUNTRACED); //this man that the parent proccess wait its child to end its execution

    } else {
        signal(SIGCHLD,signalHandler); // active the signal of the process which is running in the background
    }

}

void signalHandler(int signum)
{
    //check if the process is runing in the background
    if (signum==SIGCHLD && background == 1) {
        //get the time which the inturrupt is happen
        time_t mytime = time(NULL);
        char *time_str = ctime(&mytime);
        time_str[strlen(time_str) - 1] = '\0';
        FILE *fp;
        fp = fopen("log.txt", "a");
        /* append lines of text into the file stream*/
        fprintf(fp, "Child process was terminated   %s \n", time_str);
        /* close the file*/
        fclose(fp);
    }
}

