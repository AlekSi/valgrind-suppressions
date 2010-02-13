#include "destructor.h"

ValgrindSuppressionsForDestructor::ValgrindSuppressionsForDestructor()
	: i(new int)
{
}

ValgrindSuppressionsForDestructor::~ValgrindSuppressionsForDestructor()
{
	delete i;
}
