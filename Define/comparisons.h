#ifndef COMPARISONS
#define COMPARISONS
#include "Cell.h"

bool orderByPriority(const Cell &a, const Cell &b)
{
	return a.ComparePriority(b) < 0;
}

#endif