#include "Engine.h"

const Changes Engine::PerformMove(const Cell& currentCell, const vector<int> neighbors)
{
	sf::Vector3i origin = currentCell.GetLocation();
	sf::Vector3i destination = origin;
	Changes changes;	
	CellType type = currentCell.GetCellType();
	vector<CellRule> rules = type.GetRules();
	
	int surroundings = GenerateBinaryFormOfNeighbors(neighbors, currentCell.GetTeam());
	CellRule currRule;
	for (unsigned int i = 0; i < rules.size(); ++i)
	{
		currRule = rules[i];
		if (surroundings == currRule.code)
		{
			destination.x += neighborOffsets[currRule.direction][0];
			destination.y += neighborOffsets[currRule.direction][1];
			destination.z += neighborOffsets[currRule.direction][2];
			if (currRule.actionType == ActionType::Attack)
			{
				sf::Vector3i kill = destination;
				changes.kills.push_back(kill);
			}	
			break;
		}

	}
	
	std::vector<std::vector<sf::Vector3i>> moves;
	std::vector<sf::Vector3i> move;
	move.push_back(origin);
	move.push_back(destination);
	moves.push_back(move);

	changes.moves = moves;
	return changes;
}

//vector<int> Engine::GetNeighborsByTeam(sf::Vector3i origin, const Level& level)
//{
//	vector<int> neighbors;
//	for (unsigned inti = 0; i < 6; i++)
//	{
//		sf::Vector3i currNeighborCoordinates(origin.x + neighborOffsets[i][0], origin.y + neighborOffsets[i][1],
//									origin.z + neighborOffsets[i][2]);
//		if (!level.IsOutOfBounds(currNeighborCoordinates))
//		{
//			int currCellIndex = (level.GetConstTile(currNeighborCoordinates).GetCellIndex());
//			neighbors.push_back(currCellIndex == -1 ? 0 : level.GetCell(currCellIndex).GetTeam());
//		}
//		else
//		{
//			neighbors.push_back(0);
//		}
//		
//	}
//	vector<int> testVec = { 1, 2, 0, 0, 1, 2 };
//	int test = GenerateBinaryFormOfNeighbors(testVec, 1);
//
//	return neighbors;
//}

int Engine::GenerateBinaryFormOfNeighbors(vector<int> neighbors, int team)
{
	int code = 0;
	int rank = 0;
	for (unsigned int i = 5; i > 0; --i)
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