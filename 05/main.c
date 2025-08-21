#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>
#include <fcntl.h>

volatile sig_atomic_t counter = 0;
volatile sig_atomic_t interrupt_count = 0;
FILE *file = NULL;

void signalHandler(int sig)
{
    if (sig == SIGINT || sig == SIGQUIT)
    {
        interrupt_count++;
        fprintf(file, "Сигнал %s\n",
                sig == SIGINT ? "SIGINT" : "SIGQUIT");
        fflush(file);

        if (interrupt_count >= 3)
        {
            if (file)
            {
                fclose(file);
            }
            exit(0);
        }
    }
}

int main()
{
    file = fopen("counter.txt", "w");
    if (file == NULL)
    {
        printf("Нет файла\n");
        return 1;
    }

    signal(SIGINT, signalHandler);
    signal(SIGQUIT, signalHandler);

    while (1)
    {
        fprintf(file, "%d\n", ++counter);
        fflush(file);
        sleep(1);
    }
    fclose(file);
    return 0;
}
