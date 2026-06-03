#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    // hardcoded commands
    char *cmds[][10] = {
        {"ls", "-l", NULL},
        {"grep", ".c", NULL},
        {"wc", "-l", NULL}
    };

    int N = 3;

    // Need N-1 pipes
    int p[2 * (N - 1)];

    // Create all pipes
    for (int i = 0; i < N - 1; i++)
    {
        if (pipe(p + 2*i) < 0)
        {
            perror("pipe");
            exit(1);
        }
    }

    // Create N children
    for (int i = 0; i < N; i++)
    {
        pid_t pid = fork();

        if (pid < 0)
        {
            perror("fork");
            exit(1);
        }

        if (pid == 0)
        {
            // NOT FIRST COMMAND
            if (i > 0)
            {
                dup2(p[2*(i-1)], STDIN_FILENO);
            }

            // NOT LAST COMMAND
            if (i < N-1)
            {
                dup2(p[2*i + 1], STDOUT_FILENO);
            }

            // Close ALL pipe FDs
            for (int j = 0; j < 2*(N-1); j++)
            {
                close(p[j]);
            }

            // Execute command
            execvp(cmds[i][0], cmds[i]);

            perror("execvp");
            exit(1);
        }
    }

    // Parent closes everything
    for (int i = 0; i < 2*(N-1); i++)
    {
        close(p[i]);
    }

    // Wait for all children
    for (int i = 0; i < N; i++)
    {
        wait(NULL);
    }

    return 0;
}