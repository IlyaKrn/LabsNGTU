#include<stdio.h>
#include<stdlib.h>

int fun(int a, int b, int c, int x)
{
    return a * x * x + b * x + c;
}

int* get100Values(int a, int b, int c)
{
    int* arr = malloc(101 * sizeof(int));
    arr[0] = fun(a, b, c, 0);
    arr[1] = fun(a, b, c, 1);
    arr[2] = fun(a, b, c, 2);
    int d10 = arr[1] - arr[0];
    int d21 = arr[2] - arr[1];
    int deltaTwo = d21 - d10;
    int deltaLast = d21;
    for(int i = 3; i <= 100; i++)
    {
        int di = deltaLast + deltaTwo;
        arr[i] = arr[i - 1] + di;
        deltaLast = di;
    }
    return arr;
}

int main()
{
    int a, b, c;
    printf("enter a\n");
    scanf("%d", &a);
    printf("enter b\n");
    scanf("%d", &b);
    printf("enter c\n");
    scanf("%d", &c);

    int* arr = get100Values(a, b, c);
    for (int i = 0; i <= 100; i++)
    {
        printf("by delta: %d; simple: %d\n", arr[i], fun(a, b, c, i));
    }
    return 0;
}