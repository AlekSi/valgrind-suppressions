#include <stdlib.h>
#include <stdio.h>

void do_atexit()
{
}

int main()
{
	atexit(do_atexit);
	atoi("42");
	atof("42.42");
	printf("printf: %d %s\n", 42, "some string");
	return 0;
}
