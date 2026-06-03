#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char input[] = "dir";
    char *args[10];

    int i = 0;
    char *token = strtok(input, " ");

    while (token != NULL) {
        args[i] = token;
        i++;
        token = strtok(NULL, " ");
    }
    args[i] = NULL;

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
        printf("Child finished. Shell Returning.....\n");
    }

    return 0;
}