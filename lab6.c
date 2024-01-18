#include<stdio.h>

int main()
{
    int a;
    printf("enter a\n");
    scanf("%d", &a);
    printf("%d is %s\n", a, a % 2 == 0 ? "even" : "not even");
    
    return 0;
}
