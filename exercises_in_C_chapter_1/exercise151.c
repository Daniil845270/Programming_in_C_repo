#include <stdio.h>

int main(void)
{
	int a, b = 0, c = 0;
	a = b-- + --c;
	printf("%i %i %i\n", a, b, c);
}
