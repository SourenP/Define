#ifndef COMPARISONS_H
#define COMPARISONS__H
#include "Cell.h"
#include "define_structs.h"

//bool orderByPriority(const Cell &a, const Cell &b)
//{
//	return a.ComparePriority(b) < 0;
//}

class compareHeapNodes
{
public:
	bool operator() (const HeapNode &a, const HeapNode &b) const
	{
		return a.priority > b.priority;
	}
};

#endif