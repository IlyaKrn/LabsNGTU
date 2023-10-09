#include <stdio.h>
#include <math.h>


float u(float x, float a){
    float u1 = tan(a/x);
    float u2 = x * sin(a*a);
    return u1 < u2 ? u1 : u2;
}
float z(float x, float a){
    float z1 = a * sqrt(u(x, a));
    float z2 = sin(a)/x;
    return z1 < z2 ? z1 : z2;
}
int main()
{
    for (float x = 1; x <= 3; x += 1.3f )
    {
        for (float a = 2; a <= 4; a += 1.3f )
        {
            printf("x = %f, a = %f, f(x, a) = %f\n", x, a, z(x, a));
        }
    }
}