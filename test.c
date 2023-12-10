#include <stdlib.h>
void f()
{
	system("leaks a.out");
}

int main()
{
	char *ptr = malloc(100);
	return 1;
}