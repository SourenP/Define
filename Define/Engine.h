#ifndef ENGINE
#define ENGINE

#include "define_structs.h"
#include "Cell.h"
#include "Tile.h"

static int neighborOffsets[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };

static const Changes getResult(const Cell& thisCell, const Level& level)
{
	vector<Tile*> tiles = level.GetTileContainer();
	vector<Cell*> cells = level.GetCellContainer();

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

static vector<int> getNeighborsByTeam(sf::Vector3i origin, const Level& level)
{
	vector<Tile*> tiles = level.GetTileContainer();
	vector<Cell*> cells = level.GetCellContainer();
	int** tileIDs = level.GetTileIDs();

	vector<int> neighbors;
	for (int i = 0; i < 6; i++)
	{
		sf::Vector3i currNCoordinates(origin.x + neighborOffsets[i][0], origin.y + neighborOffsets[i][1], origin.z + neighborOffsets[i][2]);
		int currCellIndex = (level.GetConstTile(currNCoordinates)->GetCellIndex());
		neighbors.push_back(currCellIndex == -1 ? 0 : cells[currCellIndex]->GetTeam());
	}
	return neighbors;
}

#endif 