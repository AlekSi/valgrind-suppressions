#include "exceptions.h"

#include <stdexcept>
using namespace std;

ValgrindSuppressionsForException::ValgrindSuppressionsForException()
{
	try
	{
		throw runtime_error("Some text.");
	} catch(...)
	{
	}
}
