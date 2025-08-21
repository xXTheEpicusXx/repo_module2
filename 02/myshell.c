#include "myshell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>

extern int errno;

void promt(char *username, char *hostname, char *curDir)
{
    printf("\033[32m%s@%s\033[0m:\033[34m%s\033[0m$ ", username, hostname, curDir);
}

void executeCommand(char **argv)
{
    pid_t pid = fork();
    if (pid == 0)
    {
        // Дочерний
        execvp(argv[0], argv);
        fprintf(stderr, "Error %s: %d\n", argv[0], errno);
        exit(EXIT_FAILURE);
    }
    else if (pid > 0)
    {
        // Родительский ждет завершения дочернего
        wait(NULL);
    }
}
