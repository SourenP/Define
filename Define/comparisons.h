#ifndef COMPARISONS
#define COMPARISONS
#include "Cell.h"

bool orderByPriority(const Cell &a, const Cell &b)
{
	return a.ComparePriority(b) < 0;
}

class compareHeapNodes
{
	bool operator (const HeapNode &a, const HeapNode &b)
		return a.priority > b.priority;
}

#endif