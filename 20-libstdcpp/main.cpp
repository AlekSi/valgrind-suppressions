#include "strings.h"
#include "streams.h"
#include "exceptions.h"

int main()
{
	ValgrindSuppressionsForString();
	ValgrindSuppressionsForStream();
	ValgrindSuppressionsForException();
	return 0;
}
