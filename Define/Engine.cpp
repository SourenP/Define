#include "Engine.h"
#include "define_structs.h"
#include "Cell.h"

static const Changes getResult(Cell& thisCell)
{
	sf::Vector3i location = thisCell.GetLocation();
	sf::Vector3i destination;
	destination.y--;
	destination.z++;
	std::vector<std::vector<sf::Vector3i, sf::Vector3i>> moves = { { thisCell.GetLocation(), destination } };
	Changes changes = { moves };
	return changes;
}