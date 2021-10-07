#include<stdio.h>

float c_to_f(float c)
{
    return ((c*9)/5)+32;
}

int main()
{
    float c, f;

    printf("Celsius    Fahr\n");

    for (c = 0; c <=  300; c = c+40)
    {
        f = c_to_f(c);
        printf("%.0f    %.1f\n", c, f);
    }
}