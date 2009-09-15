#include "strings.h"

#include <string>
using namespace std;

ValgrindSuppressionsForString::ValgrindSuppressionsForString()
{
	string str1("looks nice!");
	string str2 = str1;
	str2.insert(4, str1);
}
