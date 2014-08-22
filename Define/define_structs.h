#ifndef DEFINE_STRUCT_H
#define DEFINE_STRUCT_H

#include "SFML\Graphics.hpp"
#include <vector>

struct Changes
{
	std::vector<std::vector<sf::Vector3i, sf::Vector3i>> moves; // [[target, dest], ... ]
};

struct HeapNode
{
	int priority;
	int cellIndex;

	class compareHeapNode
	{
		bool operator() (const HeapNode& a, const HeapNode& b)
		{
			return a.priority > b.priority;
		}
	};
};

#endif