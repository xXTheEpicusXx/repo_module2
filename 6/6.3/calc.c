#include "calc.h"

void sum(double *res, double arg1, double arg2)
{
    *res = arg1 + arg2;
}

// измененный sum для проверки
/*void sum(double *res, double arg1, double arg2)
{
    *res = arg1 + 2 * arg2;
}*/

void sub(double *res, double arg1, double arg2)
{
    *res = arg1 - arg2;
}

void mul(double *res, double arg1, double arg2)
{
    *res = arg1 * arg2;
}

void div(double *res, double arg1, double arg2)
{
    *res = arg1 / arg2;
}
