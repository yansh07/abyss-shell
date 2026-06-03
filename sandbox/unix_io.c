#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>

int main() {
    while(1) {
        char input[1024];
        printf("abyss-shell> ");
        fgets(input, 1024, stdin);

        char *args[10];
        char *outfile = NULL;

        int i = 0;
        char *token = strtok(input, " \n");
        while (token != NULL) {
            if (strcmp(token, ">") == 0) {
                token = strtok(NULL, " \n");
                if (token != NULL) {
                    outfile = token;
                }
                break;
            }
            args[i] = token;
            i++;
            token = strtok(NULL, " \n");
        }

        args[i] = NULL;
        if (args[0] == NULL) {
            continue;
        }
        
        if (strcmp(args[0], "exit") == 0)
        {
            break;
        }
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
            if (outfile) {
                int fd = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
                if (fd < 0) {
                    perror("open");
                    exit(1);
                }
                if (dup2(fd, STDOUT_FILENO) < 0) {
                    perror("dup2");
                    close(fd);
                    exit(1);
                }
                close(fd);
            }
            execvp(args[0], args);
            perror("execvp failed");
            exit(1);
        }
        else {
            wait(NULL);
        }
    }

    return 0;
}