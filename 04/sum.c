#include <stdio.h>
#include <stdlib.h>

int sum(int argc, char *argv[])
{
    int sum = 0;
    for (int i = 1; i < argc; i++)
    {
        sum += atoi(argv[i]);
    }
    return sum;
}

int main(int argc, char *argv[])
{
    printf("%d\n", sum(argc, argv));
    return 0;
}
