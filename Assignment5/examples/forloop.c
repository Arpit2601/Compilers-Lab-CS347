#include <stdio.h>

int main()
{
    int i;
    for (i = 0; i < 5; i = i + 1)
    {
        int x = 10;
        put(x);
        // put(i);
    }
    return 0;
}