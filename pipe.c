#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    char *cmd1[] = {"ls", NULL};
    char *cmd2[] = {"grep", ".c", NULL};
    
    int p[2];
    if (pipe(p) < 0) {
        exit(1);
    }
    pid_t pid1 = fork();

    // child 1:ls 
    if (pid1 == 0)
    {
        dup2(p[1], STDOUT_FILENO);

        close(p[0]);
        close(p[1]);

        execvp(cmd1[0], cmd1);
        
        exit(1);
    }

    pid_t pid2 = fork();

    // child 2: grep
    if (pid2 == 0)
    {
        dup2(p[0], STDIN_FILENO);

        close(p[0]);
        close(p[1]);

        execvp(cmd2[0], cmd2);

        exit(1);
    }

    //parent
    close(p[0]);
    close(p[1]);

    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);

    return 0;
}