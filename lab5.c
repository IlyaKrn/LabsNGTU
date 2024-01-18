#include <stdio.h>
#include <math.h>
int main() {
	double a, b, c;
    printf("Enter a\n");
	scanf("%lf", &a);
    printf("Enter b\n");
	scanf("%lf", &b);
    printf("Enter c\n");
	scanf("%lf", &c);
	double discr = b * b - 4 * a * c;
	if (a == 0 && b == 0 && c == 0) {
		printf("Infinitely many roots\n");
	}
	else if (a == 0 && b == 0) {
		printf("No roots\n");
	}
	else if ((a == 0 || b == 0) && c == 0) {
		printf("x = 0\n");
	}
	else if (a == 0) {
		printf("x = %lf\n", b / c);
	}
	else if (b == 0) {
		if (-c / a > 0) {
			printf("x1=%lf\nx2=%lf\n", sqrt(-c / a), +sqrt(-c / a));
		}
		else {
			printf("No real roots\n");
		}
	}
	else if (c == 0) {
		printf("x1=0\nx2=%lf\n", -b / a);
	}
	else {
		if (discr == 0) {
			printf("x=%lf\n", -b / 2 * a);
		}
		else if (discr > 0) {
			double x1 = (-b + sqrt(discr)) / (2 * a);
			double x2 = (-b - sqrt(discr)) / (2 * a);
			printf("x1=%lf\nx2=%lf\n", x1, x2);
		}
		else if (discr < 0) {
			printf("No real roots\n");
		}
	}
	return 0;
}