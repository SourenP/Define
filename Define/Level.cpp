#include "Level.h"

bool Level::Start(int windowSize)
{
	double tileRadius = (windowSize / MAP_DIAMETER)/2.0;
	double tileDiameter = 2 * tileRadius;
	double tileHeight = sqrt(3) * tileRadius;
	int k = 0;

	for (int i = 0; i < MAP_SIDE_LENGTH; ++i)
	{
		double mapOffset = (MAP_DIAMETER - MAP_SIDE_LENGTH - i )/2.0;
		double tileOffset = mapOffset * tileHeight + tileHeight / 2.0;
		m_tileArray[k].Create(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius/2) + tileRadius));

		k++;
		for (int j = 1; j < MAP_SIDE_LENGTH + i; ++j)
		{
			tileOffset += tileHeight;
			m_tileArray[k].Create(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2) + tileRadius));
			k++;
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