#define MAX_LEN 255
#define MAX_SIZE 100

void promt(char *username, char *hostname, char *curDir);
// void executeCommand(char **argv);
void argvToConveyor(int argc, char **argv, char *commands[MAX_SIZE][MAX_SIZE], int *commandsCnt);
void redirect_IO(char *command[], int *input_fd, int *output_fd);
void executeCommands(char *commands[MAX_SIZE][MAX_SIZE], int commandsCnt);
