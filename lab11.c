#include<stdio.h>
#include<stdlib.h>
#include<math.h>

int fun(double a, double b, double c, double* x1, double* x2)
{
	double discr = b * b - 4 * a * c;
	if (a == 0 && b == 0 && c == 0) {
		return -1;
	}
	else if (a == 0 && b == 0) {
		return 0;
	}
	else if ((a == 0 || b == 0) && c == 0) {
        *x1 = 0;
        *x2 = 0;
        return 1;
	}
	else if (a == 0) {
        *x1 = b / c;
        *x2 = b / c;
        return 1;
	}
	else if (b == 0) {
		if (-c / a > 0) {
            *x1 = sqrt(-c / a);
            *x2 = +sqrt(-c / a);
            return 2;
		}
		else {
			return 0;
		}
	}
	else if (c == 0) {
        *x1 = 0;
        *x2 = -b / a;
        return 2;
	}
	else {
		if (discr == 0) {
            *x1 = -b / 2 * a;
            *x2 = -b / 2 * a;
            return 1;
		}
		else if (discr > 0) {
			*x1 = (-b + sqrt(discr)) / (2 * a);
			*x2 = (-b - sqrt(discr)) / (2 * a);
            return 2;
		}
		else if (discr < 0) {
			return 0;
		}
	}
}

int main()
{
    double a, b, c;
    printf("enter a\n");
    scanf("%lf", &a);
    printf("enter b\n");
    scanf("%lf", &b);
    printf("enter c\n");
    scanf("%lf", &c);

    double x1, x2;
    int count = fun(a, b, c, &x1, &x2);
    if (count == -1)
    {
    	printf("Infinitely many roots\n");
    }
    if (count == 0)
    {
    	printf("No roots\n");
    }
    if (count == 1)
    {
    	printf("x = %lf\n", x1);
    }
    if (count == 2)
    {
    	printf("x1 = %lf\nx2 = %lf\n", x1, x2);
    }
    return 0;
}
