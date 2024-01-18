#include <stdio.h>

int fact(int a){
    return a == 1 ? 1 : a*fact(a-1);
}

int main(){
	int a;
	printf("Enter number\n");
	scanf("%d",&a);
	printf("%d! = %ld\n", a, fact(a));
	return 0;
}
