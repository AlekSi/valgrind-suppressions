#include <stdlib.h>
#include <stdio.h>

int* mem;

void do_atexit()
{
	free(mem);
}

int main()
{
	atexit(do_atexit);
	mem = malloc(8);

	atoi("42");
	atof("42.42");
	printf("printf: %d %s\n", 42, "some string");
	return 0;
}
