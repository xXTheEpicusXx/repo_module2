#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

typedef void (*func_name)(double *, double, double);
typedef struct
{
    const char *name;
    func_name func;

} operation;
int main()
{
    void *handle;
    func_name sum, sub, mul, div;
    handle = dlopen("./libcalc.so", RTLD_LAZY);
    if (!handle)
    {
        printf("Error lib\n");
        exit(1);
    }
    sum = (func_name)dlsym(handle, "sum");
    sub = (func_name)dlsym(handle, "sub");
    mul = (func_name)dlsym(handle, "mul");
    div = (func_name)dlsym(handle, "div");
    if (!sub || !sum || !mul || !div)
    {
        printf("Error funcs\n");
        dclose(handle);
        exit(1);
    }
    operation operations[] = {
        {"sum", sum}, {"sub", sub}, {"mul", mul}, {"div", div}};
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
        operations[c - '1'].func(&res, arg1, arg2);
        if (c - '1' == cnt - 1 && arg2 == 0)
        {
            printf("error\n");
        }
        else
        {
            printf("%lf\n", res);
        }
    }
    return 0;
}
