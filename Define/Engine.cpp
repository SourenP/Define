#include "Engine.h"


int neighborOffsets[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };



vector<sf::Vector3i> getNeighbors(sf::Vector3i coordinates)
{
	vector<sf::Vector3i> neighborCoordinates;
	for (int i = 0; i < 6; i++)
	{
		sf::Vector3i currentV = { coordinates.x + neighborOffsets[i][0], coordinates.y + neighborOffsets[i][1], coordinates.z + neighborOffsets[i][2] };
		neighborCoordinates.push_back(currentV);
	}
	return neighborCoordinates;
}