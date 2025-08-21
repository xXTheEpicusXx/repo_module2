#include "myshell.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>

extern int errno;

void promt(char *username, char *hostname, char *curDir)
{
    printf("\033[32m%s@%s\033[0m:\033[34m%s\033[0m$ ", username, hostname, curDir);
}

void argvToConveyor(int argc, char **argv, char *commands[MAX_SIZE][MAX_SIZE], int *commandsCnt)
{
    int curCmdInd = 0;
    int curArgInd = 0;
    for (int i = 0; i < argc; i++)
    {
        if (strcmp(argv[i], "|") == 0)
        {
            commands[curCmdInd][curArgInd] = NULL;
            curCmdInd++;
            curArgInd = 0;
        }
        else
        {
            commands[curCmdInd][curArgInd++] = argv[i];
        }
    }
    *commandsCnt = curCmdInd + 1;
}

void redirect_IO(char *command[], int *input_fd, int *output_fd)
{
    int i = 0, j = 0;
    while (command[i] != NULL && command[i][0] != 0)
    {
        if (strcmp(command[i], "<") == 0)
        {
            *input_fd = open(command[i + 1], O_RDONLY);
            if (*input_fd == -1)
            {
                fprintf(stderr, "File Error %s: %d\n", command[0], errno);
                exit(EXIT_FAILURE);
            }
            i += 2;
        }
        else if (strcmp(command[i], ">") == 0)
        {
            *output_fd = open(command[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
            if (*output_fd == -1)
            {
                fprintf(stderr, "File Error %s: %d\n", command[0], errno);
                exit(EXIT_FAILURE);
            }
            i += 2;
        }
        else if (strcmp(command[i], ">>") == 0)
        {
            *output_fd = open(command[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
            if (*output_fd == -1)
            {
                fprintf(stderr, "File Error %s: %d\n", command[0], errno);
                exit(EXIT_FAILURE);
            }
            i += 2;
        }
        else
        {
            if (j != i)
            {
                command[j] = command[i];
            }
            j++;
            i++;
        }
    }
    command[j] = NULL;
}

void executeCommands(char *commands[MAX_SIZE][MAX_SIZE], int commandsCnt)
{
    pid_t pids[MAX_SIZE];
    int pipes[MAX_SIZE - 1][2];
    for (int i = 0; i < commandsCnt; i++)
    {
        for (int j = 0; commands[i][j] != NULL; j++)
        {
            if (commands[i][j] != NULL)
            {
                int l = strlen(commands[i][j]);
                printf("| %s chr: %d len: %d| ", commands[i][j], commands[i][j][0], l);
            }
            else
            {
                printf("| NULL | ");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < commandsCnt - 1; i++)
    {

        if (pipe(pipes[i]) == -1)
        {
            fprintf(stderr, "Error %s: %d\n", commands[i][0], errno);
            exit(EXIT_FAILURE);
        }
    }
    for (int i = 0; i < commandsCnt; i++)
    {

        pids[i] = fork();
        if (pids[i] == -1)
        {
            fprintf(stderr, "Error %s: %d\n", commands[i][0], errno);
            exit(EXIT_FAILURE);
        }
        else if (pids[i] == 0)
        {
            int input_fd = -1, output_fd = -1;
            if (i == commandsCnt - 1)
            {
                redirect_IO(commands[i], &input_fd, &output_fd);
            }
            if (i > 0)
            {
                dup2(pipes[i - 1][0], STDIN_FILENO);
            }
            else if (input_fd != -1)
            {

                dup2(input_fd, STDIN_FILENO);
            }
            if (i < commandsCnt - 1)
            {
                dup2(pipes[i][1], STDOUT_FILENO);
            }
            else if (output_fd != -1)
            {

                dup2(output_fd, STDOUT_FILENO);
            }
            for (int j = 0; j < commandsCnt - 1; j++)
            {
                close(pipes[j][0]);
                close(pipes[j][1]);
            }
            if (input_fd != -1)
                close(input_fd);
            if (output_fd != -1)
                close(output_fd);

            execvp(commands[i][0], commands[i]);
        }
    }
    for (int i = 0; i < commandsCnt - 1; i++)
    {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    for (int i = 0; i < commandsCnt; i++)
    {
        waitpid(pids[i], NULL, 0);
    }
}
