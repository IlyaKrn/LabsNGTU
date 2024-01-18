#include<stdio.h>

int fun(int x)
{
    return 2 * x * x + x + 41;
}

int main()
{
    printf("7: %d\n", fun(7));
    printf("14: %d\n", fun(14));
    printf("129: %d\n", fun(129));
    return 0;
}
