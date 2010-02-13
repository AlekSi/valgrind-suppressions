#include "strings.h"
#include "streams.h"
#include "exceptions.h"
#include "destructor.h"

static ValgrindSuppressionsForDestructor d1 = ValgrindSuppressionsForDestructor();

int main()
{
	ValgrindSuppressionsForString();
	ValgrindSuppressionsForStream();
	ValgrindSuppressionsForException();
	static ValgrindSuppressionsForDestructor d2 = ValgrindSuppressionsForDestructor();
	ValgrindSuppressionsForDestructor();
	return 0;
}
