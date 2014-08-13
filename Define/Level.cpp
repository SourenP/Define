#include "Level.h"

bool Level::Start(int windowSize)
{
	m_tileArray = new Tile[MAP_SIDE_LENGTH];
	double tileRadius = (windowSize / MAP_DIAMETER)/2.0;
	double tileDiameter = 2 * tileRadius;
	double tileHeight = sqrt(3) * tileRadius;
	int tileIndex = 0;

	for (int i = 0; i < MAP_SIDE_LENGTH; ++i)
	{
		double tileOffsetAmt = (MAP_DIAMETER - MAP_SIDE_LENGTH - i )/2.0;	// amount of tiles row is offset by 
		double tileOffset = tileOffsetAmt * tileHeight + tileHeight / 2.0;  // tileOffsetAmt + tiles already place on row (in pixels)
		m_tileArray[tileIndex] = new Tile(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2) + tileRadius/2));

		tileIndex++;
		for (int j = 1; j < MAP_SIDE_LENGTH + i; ++j) 
		{
			tileOffset += tileHeight;
			m_tileArray[tileIndex] = new Tile(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2) + tileRadius / 2));
			tileIndex++;
		}
	}


	return true;
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < TILE_COUNT; ++i)
	{
		m_tileArray[i].Draw(rw);
	}
}

bool Level::Destroy()
{
	return true;
}