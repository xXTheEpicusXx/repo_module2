#include "myshell.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pwd.h>
#include <string.h>

int main()
{
    char *username = getenv("USER");
    char hostname[MAX_LEN];
    gethostname(hostname, sizeof(hostname));
    char curDir[MAX_LEN];
    getcwd(curDir, MAX_LEN);

    char *argv[MAX_SIZE];
    int argc;
    char *token;

    char input[MAX_LEN];
    while (1)
    {
        promt(username, hostname, curDir);
        fgets(input, MAX_LEN, stdin);
        input[strcspn(input, "\n")] = '\0';
        argc = 0;
        token = strtok(input, " ");
        while (token != NULL)
        {
            argv[argc++] = token;
            token = strtok(NULL, " ");
        }
        argv[argc] = NULL;
        // executeCommand(argv);
        char *commands[MAX_SIZE][MAX_SIZE];
        int commandsCnt;
        argvToConveyor(argc, argv, commands, &commandsCnt);
        executeCommands(commands, commandsCnt);
    }
    return 0;
}
