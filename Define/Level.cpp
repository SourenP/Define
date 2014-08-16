#include "Level.h"
#include <unordered_map>
#include <iostream>
using namespace std;


Level::Level(int windowSize)
{
	m_tileTable = new	unordered_map<string, Tile*>();
	float tileHeight = windowSize / MAP_DIAMETER;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xMapOffset = 0;
	float yMapOffset = 0;
	float xOffset = 0;
	float yOffset;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;

	// c and r produce numbers matchin axial coordinates
	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		xOffset += tileDiameter * 3.0 / 4.0;
		yOffset = tileHeight*((MAP_DIAMETER - abs(rowMax - rowMin)) / 2.0);	
		for (int r = rowMin; r <= rowMax; ++r)
		{
			// Map key is based on cube coordinates x_z_y (Conversion from axial to cube: x = c  z = r  y = -x-z)
			(*m_tileTable)[to_string(c) + "_" + to_string(r) + "_" + to_string(-c - r)] =
				 new Tile(tileRadius, sf::Vector2f(xOffset + xMapOffset, yOffset + yMapOffset), sf::Vector3i(c, r, -c - r));
			yOffset += tileHeight;
		}
		c < 0 ? rowMin-- : rowMax--;
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (auto it = m_tileTable->begin(); it != m_tileTable->end(); ++it)
	{
		it->second->Draw(rw);
	}
}

Level::~Level()
{
	for (auto it = m_tileTable->begin(); it != m_tileTable->end();)
	{
		it = m_tileTable->erase(it);
	}
	delete m_tileTable;
}