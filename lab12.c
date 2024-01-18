#include <stdio.h>

int fact(int a){
	if (a==1)
		return 1;
	if (a>1){
		int b=1;
		for (int i = 1; i <= a; i++)
			b *= i;
		return b;
	}
}
int main(){
	int a;
	printf("Enter number\n");
	scanf("%d",&a);
	printf("%d! = %ld\n", a, fact(a));
	return 0;
}

