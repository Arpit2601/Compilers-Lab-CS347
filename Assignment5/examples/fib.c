#include<stdio.h>
int fib (int n)
{
    int c;
    if (n <= 1)
    {
        c = 1;
    }
    else
    {c =  fib (n - 1) + fib (n - 2);}
    return c;
}

int main()
{
    put(fib(4));
}