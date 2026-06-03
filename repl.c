#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    while(1) {
        char input[1024];
        printf("abyss-shell> ");
        fgets(input, 1024, stdin);

        char *args[10];

        int i = 0;
        char *token = strtok(input, " \n");
        while(token != NULL) {
            args[i] = token;
            i++;
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;
        if (args[0] == NULL) {
            continue;
        }
        //handle exit
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
        //handle cd command
        if (strcmp(args[0], "cd") == 0)
        {
            chdir(args[1]);
            continue;
        }
        if (strcmp(args[0], "ping") == 0)
        {
            printf("PONG\n");
            continue;
        }
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork failed!!");
            exit(EXIT_FAILURE);
        }
        else if (pid == 0) 
        {
            execvp(args[0], args);
            printf("Command not found!!\n");
            exit(1);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}