#include "Engine.h"
#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"

int neighborOffsets[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };

static const Changes getResult(const Cell& thisCell, const std::vector<Cell*>&, const std::vector<Tile*>&)
{
	sf::Vector3i location = thisCell.GetLocation();
	sf::Vector3i destination;
	destination.y--;
	destination.z++;
	std::vector<std::vector<sf::Vector3i, sf::Vector3i>> moves = { { thisCell.GetLocation(), destination } };
	Changes changes = { moves };
	return changes;
}

vector<sf::Vector3i>& getNeighbors(sf::Vector3i coordinates)
{
	vector<sf::Vector3i>* neighborCoordinates = new vector<sf::Vector3i>(6);
	for (int i = 0; i < 6; i++)
	{
		(*neighborCoordinates)[i].x = coordinates.x + neighborOffsets[i][0];
		(*neighborCoordinates)[i].y = coordinates.y + neighborOffsets[i][1];
		(*neighborCoordinates)[i].z = coordinates.z + neighborOffsets[i][2];
	}
	return *neighborCoordinates;
}