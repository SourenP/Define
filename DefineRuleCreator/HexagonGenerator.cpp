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
	//m_hexMap.resize(mapSize, vector<int>(mapSize, 0));

	/*
	Initialization for recursive fill
	We manually fill the first ring of neighbors after which we use SeedHexagon
	*/
	Hexagon* primaryHexagon = new Hexagon(center, radius); //Primary hexagon is the hexagon rules are being created for
	m_hexagons.push_back(primaryHexagon);
	m_hexMap[mapSize / 2][mapSize / 2] = 1;
	m_ringDistance = 2 * (sin(toRadians(60))*radius);
	SeedHexagon(center, pair<int, int>(mapSize / 2, mapSize / 2), rings);

//	double ringDistance = 2*(sin(toRadians(60))*radius); //Distance between origin of primaryHexagon and the hexagon above the primary in the current ring
//	double angle;
//	POINT origin;
//
//	angle = 90; //We start from the hexagon above primary and fill the rest counter-clockwise
//	for (int i = 0; i < 6; ++i)
//	{
//		origin = { center.x + ringDistance*cos(toRadians(angle)), center.y + ringDistance*sin(toRadians(angle)) };
//		Hexagon* newHexagon = new Hexagon(origin, radius);
//		HexNode newHexNode;
//		newHexNode.neighbors = vector<int>(6, 0);
//		int neightborIndex = (i + 2) % 6;
//		for (int j = 0; j < 3; ++j)
//		{
//			newHexNode.neighbors[neightborIndex] = 1;
//			neightborIndex = (neightborIndex + 1)%6;
//		}
//		m_hexNodes.push_back(newHexNode);
//		m_hexagons.push_back(newHexagon);
//		angle += 60;
//	}
//	/*
//	End of initialization
//	*/
//
//	for (int i = 1; i < rings; ++i)
//	{
//		for (int j = (i - 1)*6 + 1; i < 6 * pow(2,i - 1) + 1; ++j)
//		{
//
//			center = m_hexagons[j]->GetOrigin();
//			origin = { center.x + ringDistance*cos(toRadians(angle)), center.y + ringDistance*sin(toRadians(angle)) };
//			Hexagon* newHexagon = new Hexagon(origin, radius);
//			HexNode newHexNode;
//			newHexNode.neighbors = vector<int>(6, 0);
//			int neightborIndex = (i + 2) % 6;
//			for (int j = 0; j < 3; ++j)
//			{
//				newHexNode.neighbors[neightborIndex] = 1;
//				neightborIndex = (neightborIndex + 1) % 6;
//			}
//			m_hexNodes.push_back(newHexNode);
//			m_hexagons.push_back(newHexagon);
//			angle += 60;
//		}
//	}
}

void HexagonGenerator::SeedHexagon(const POINT& origin, pair<int, int> indicies, int depth)
{
	int angle = 90;
	depth--;
	for (int i = 0; i < 6; ++i)
	{
		int offSetX = hexNeighbors[i][0];
		int offSetY = hexNeighbors[i][1];
		int currNeighborX = indicies.first + offSetX;
		int currNeighborY = indicies.second + offSetY;
		POINT newOrigin = { origin.x + m_ringDistance*cos(toRadians(angle)), origin.y + m_ringDistance*sin(toRadians(angle)) };
		if (m_hexMap[currNeighborX][currNeighborY] == 0)
		{
			m_hexMap[currNeighborX][currNeighborY] = 1;
			Hexagon* newHexagon = new Hexagon(newOrigin, m_hexagonRadius);
			m_hexagons.push_back(newHexagon);
			if (depth != 1)
				SeedHexagon(newOrigin, pair<int, int>(currNeighborX, currNeighborY), depth);
		}
		angle += 60;
	}
}


void HexagonGenerator::DrawHexagons(HDC& hdc) const
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		m_hexagons[i]->Draw(hdc);
		SetPixel(hdc, m_hexagons[i]->GetOrigin().x, m_hexagons[i]->GetOrigin().y, RGB(255, 55, 5));
	}
}

HexagonGenerator::~HexagonGenerator()
{
	for (int i = 0; i < m_hexagons.size(); ++i)
	{
		delete m_hexagons[i];
	}
}