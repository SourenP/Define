#include "Engine.h"

const Changes Engine::GetResult(const Cell& thisCell, const Level& level)
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

vector<int> Engine::GetNeighborsByTeam(sf::Vector3i origin, const Level& level)
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
	vector<int> testVec = { 1, 2, 0, 0, 1, 2 };
	int test = GenerateBinaryFormOfNeighbors(testVec, 1);

	return neighbors;
}

int Engine::GenerateBinaryFormOfNeighbors(vector<int> neighbors, int team)
{
	int code = 0;
	int rank = 0;
	for (int i = 5; i >= 0; --i)
	{
		if (neighbors[i] == team)
		{
			code += pow(2, rank + 1);
		}
		else if (neighbors[i] != 0)
		{
			code += pow(2, rank);
		}
		rank += 2;
	}

	return code;
}