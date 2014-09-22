#include "HexagonGenerator.h"

const double HexagonGenerator::DEFAULT_RADIUS = 25;

void HexagonGenerator::GenerateHexagons(int screenWidth, int screenHeight, 
					double radius, unsigned int rings)
{
	m_hexagonRadius = radius;
	m_rings = rings;
	POINT center = { screenWidth / 2 - radius, screenHeight / 2 - radius };
	int mapSize = 1 + 2 * rings;
	for (int i = 0; i < mapSize; ++i)
	{
		vector<int> temp;
		for (int j = 0; j < mapSize; ++j)
		{
			temp.push_back(0);
		}
		m_hexMap.push_back(temp);
	}
	m_ringDistance = 2 * (sin(toRadians(60))*radius);

	//Create primary seed
	m_toBeSeeded.push(HexNode(center, pair<int, int>(mapSize / 2, mapSize / 2), rings));

	//While there is a hexNode that has not been visited, continue seeding
	while (!m_toBeSeeded.empty())
	{
		HexNode next = m_toBeSeeded.front();
		m_toBeSeeded.pop();
		SeedHexagon(next);
	}
}

void HexagonGenerator::SeedHexagon(const HexNode& nextNode)
{
	POINT origin = nextNode.coordinates;
	pair<int, int> indicies = nextNode.indicies;
	int depth = nextNode.depth;

	//Each cell creates and marks itself in the m_hexMap
	Hexagon* primaryHexagon = new Hexagon(origin, m_hexagonRadius);
	m_hexagons.push_back(primaryHexagon);
	m_hexMap[indicies.first][indicies.second] = 1;

	//If we reach the outermost ring, terminate. Hexagon will be created but it wont be added to the queue
	if (depth == 0)
		return;
	depth--;

	int angle = 90; //Default angle. This is just based on hexNeighbors an can be rotated alone with the matrix to start counting from somewhere else
	int offSetI, offSetJ, currNeighborI, currNeighborJ;
	for (int i = 0; i < 6; ++i)
	{
		offSetI = hexNeighbors[i][0]; 
		offSetJ = hexNeighbors[i][1];
		currNeighborI = indicies.first + offSetI;
		currNeighborJ = indicies.second + offSetJ;
		//Check the position in m_hexNodes to see if that hex has been visited or not
		if (m_hexMap[currNeighborI][currNeighborJ] == 0)
		{
			//If it hasn't, pinpoint the new hexagons center, create a HexNode and place it in the queue
			POINT newOrigin = { origin.x + m_ringDistance*cos(toRadians(angle)), origin.y + m_ringDistance*sin(toRadians(angle)) };
			HexNode newNode(newOrigin, pair<int, int>(currNeighborI, currNeighborJ), depth);
			m_toBeSeeded.push(newNode);
		}
		angle += 60;
	}
}

void HexagonGenerator::DrawHexagons(HDC& hdc) const
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		m_hexagons[i]->Draw(hdc);
		//SetPixel(hdc, m_hexagons[i]->GetOrigin().x, m_hexagons[i]->GetOrigin().y, RGB(255, 55, 5));
	}
}

HexagonGenerator::~HexagonGenerator()
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		delete m_hexagons[i];
	}
}