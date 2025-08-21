#include "checknum.h"
#include <stdlib.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[])
{
    int mid = argc / 2;
    pid_t pid;
    pid = fork();
    if (pid == 0)// дочерний
    {

       //printf("Д %d\n", getpid());
        argsHandler(argc - mid, argc, argv);
    }
    else if (pid > 0)
    {
        //printf("Р %d\n", getpid());
        argsHandler(1, argc - mid, argv);
    }
    wait(NULL);
    return 0;
}
