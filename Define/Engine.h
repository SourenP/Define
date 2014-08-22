#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"

static const Changes getResult(const Cell& thisCell, const std::vector<Cell*>, const std::vector<Tile*>)
{
	sf::Vector3i location = thisCell.GetLocation();
	sf::Vector3i destination;
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
vector<sf::Vector3i> getNeighbors(sf::Vector3i coordinates);

#endif