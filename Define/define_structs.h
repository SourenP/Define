#ifndef DEFINE_STRUCT_H
#define DEFINE_STRUCT_H

#include "SFML\Graphics.hpp"
#include <vector>

struct Changes
{
	std::vector<std::vector<sf::Vector3i>> moves; // [[origin, dest], ... ]
};

struct HeapNode
{
	int priority;
	int cellIndex;
};

class compareHeapNodes
{
public:
	bool operator() (const HeapNode &a, const HeapNode &b) const
	{
		return a.priority < b.priority;
	}
};

#endif