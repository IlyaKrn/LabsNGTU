#include<stdio.h>

int getScore(int a, int b)
{
    return a + b == 69 ? 100 : 1;
}

int main()
{
    int a, b;
    printf("Enter first number\n");
    scanf("%d", &a);
    printf("Enter second number\n");
    scanf("%d", &b);
    printf("you score: %d\n", getScore(a, b));
    return 0;
}
