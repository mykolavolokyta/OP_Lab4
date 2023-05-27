#include "functions.h"
#include <string>

bool is_number(const char* string) {
	char* pEnd;
	int value = strtol(string, &pEnd, 10);
	if (*pEnd || value < 1) return false;
	return true;
}