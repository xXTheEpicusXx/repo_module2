#include "calc.h"

double sum(double arg1, double arg2)
{
    return arg1 + arg2;
}

double sub(double arg1, double arg2)
{
    return arg1 - arg2;
}

double mul(double arg1, double arg2)
{
    return arg1 * arg2;
}

void div(double *res, double arg1, double arg2)
{
    *res = arg1 / arg2;
}
