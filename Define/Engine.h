#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"

static int neighborOffsets[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };

static const Changes getResult(const Cell& thisCell, const std::vector<Cell*>, const std::vector<Tile*>)
{
	sf::Vector3i location = thisCell.GetLocation();
	sf::Vector3i destination = location;
	destination.y--;
	destination.z++;
	std::vector<std::vector<sf::Vector3i>> moves;
	std::vector<sf::Vector3i> move;
	move.push_back(thisCell.GetLocation());
	move.push_back(destination);
	moves.push_back(move);
	Changes changes;
	changes.moves = moves;
	return changes;
}

static vector<sf::Vector3i> getNeighbors(sf::Vector3i coordinates)
{
	vector<sf::Vector3i> neighborCoordinates;
	for (int i = 0; i < 6; i++)
	{
		sf::Vector3i currentV = { coordinates.x + neighborOffsets[i][0], coordinates.y + neighborOffsets[i][1], coordinates.z + neighborOffsets[i][2] };
		neighborCoordinates.push_back(currentV);
	}
	return neighborCoordinates;
}
#endif