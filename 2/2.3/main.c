#include "calc.h"
#include <stdio.h>

int main()
{
    void (*operations[4])(double *, double, double) = {sum, sub, mul, div};
    int cnt = sizeof(operations) / sizeof(operations[0]);
    char c = 0;
    while ((c = getchar()) != '0')
    {
        while (c == ' ' || c == '\n')
        {
            c = getchar();
        }
        if (c == '0')
        {
            break;
        }
        double arg1 = 0.0, arg2 = 0.0, res = 0.0;
        scanf("%lf %lf", &arg1, &arg2);
        operations[c - '1'](&res, arg1, arg2);
        if (c - '1' == cnt - 1 && arg2 == 0)
        {
            printf("error\n");
        }
        else
        {
            printf("%lf\n", res);
        }
    }
}
