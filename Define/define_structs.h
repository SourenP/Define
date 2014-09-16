#ifndef DEFINE_STRUCT_H
#define DEFINE_STRUCT_H

#include "SFML\Graphics.hpp"
#include <vector>

/*
Attack - destroy cell
Move - move towards goal
Retreat - move towards spawn
Used by Cell, Level and Engine
*/
enum ActionType { Attack = 1, Move = 2, Retreat = 3};

/*
Stores all changes that occured as a result of the last move
Used by Engine and Level
*/
struct Changes
{
	std::vector<std::vector<sf::Vector3i>> moves; // [[origin, dest], ... ]
	std::vector<sf::Vector3i> kills;
};

/*
Data type for turn-order heap
Used by Level
*/
struct HeapNode
{
	int priority;
	int cellIndex;
};

/*
code - binary form of the surrounding for specific rule. The binary code
uses 2 ranks for each cell, since each cell has 6 neighbors the total rank
of the code is 2^12. In the code 00 - empty, 01 - enemy, 10 - ally. Code is
generated clockwise from the top of the cell.
e.g. - 011001000110 = 1606
ActionType - what action to perform is rule is applicable.
Used by CellType, Level and Engine
*/
struct CellRule
{
	int code;
	int direction;
	ActionType actionType;
};

/*
Comperator function for the heap nodes based on the priority
Used by Level
*/
class compareHeapNodes
{
public:
	bool operator() (const HeapNode &a, const HeapNode &b) const
	{
		return a.priority < b.priority;
	}
};

#endif