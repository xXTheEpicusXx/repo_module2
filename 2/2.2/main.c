#include "calc.h"
#include <stdio.h>

int main()
{
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
        switch (c)
        {
        case '+':
            printf("%lf\n", sum(arg1, arg2));
            break;
        case '-':
            printf("%lf\n", sub(arg1, arg2));
            break;
        case '*':
            printf("%lf\n", mul(arg1, arg2));
            break;
        case '/':
            div(&res, arg1, arg2);
            if (arg2 != 0)
            {
                printf("%lf\n", res);
            }
            else
            {
                printf("error\n");
            }
            break;
        default:
            printf("0 for exit\n");
            break;
        }
    }
}
