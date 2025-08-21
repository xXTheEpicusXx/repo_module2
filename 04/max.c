#include <stdio.h>
#include <stdlib.h>

int max(int argc, char *argv[])
{
    int max = atoi(argv[1]);
    for (int i = 1; i < argc; i++)
    {
        int cur = atoi(argv[i]);
        max = max >= cur ? max : cur;
    }
    return max;
}

int main(int argc, char *argv[])
{
    printf("%d\n", max(argc, argv));
    return 0;
}
