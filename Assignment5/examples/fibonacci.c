#include <stdio.h>

int fib(int x)
{
	int b, p, q;
	if (x == 1)
	{
		b = 1;
	}
	else
	{
		if (x == 0)
		{
			b = 1;
		}
		else
		{
			int temp = x - 1;
			p = fib(temp);
			temp = temp - 1;
			q = fib(temp);
			b = p + q;
		}
	}
	return b;
}
int main()
{
	int y, r;
	y = 5;
	r = fib(y);
}