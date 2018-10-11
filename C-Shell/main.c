#include "main.h"

int main()
{   remove("log.txt");
    while(1) {
        line = readInstruction();
        background = 0;
        arguments = get_arguments(line, &background);
        execute();
        free(line);
        free(arguments);
    }
}

void execute() {
    if (arguments == NULL) {
        printf("Try to enter the input again");
    } else if (strcmp(arguments[0], "exit") == 0) {
        exit(0);
    }
    int stat_loc;
    child_pid = fork();
    if (child_pid == 0) {
        /* Never returns if the call is successful */
        execvp(arguments[0], arguments);
        printf("This won't be printed if execvp is successul\n");
    } else if (background == 0){
        waitpid(child_pid, &stat_loc, WUNTRACED);

    } else {
        signal(SIGCHLD,signalHandler);
    }

}

void signalHandler(int signum)
{
    if (signum==SIGCHLD && background == 1) {
        time_t mytime = time(NULL);
        char *time_str = ctime(&mytime);
        time_str[strlen(time_str) - 1] = '\0';
        FILE *fp;
        fp = fopen("log.txt", "a");
        /* write 10 lines of text into the file stream*/
        fprintf(fp, "Child process was terminated   %s \n", time_str);
        /* close the file*/
        fclose(fp);
    }
}

