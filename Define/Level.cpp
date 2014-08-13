#include "Level.h"

Level::Level(int windowSize)
{
	double tileRadius = (windowSize / MAP_DIAMETER)/2.0;
	double tileDiameter = 2 * tileRadius;
	double tileHeight = sqrt(3) * tileRadius;
	int tileIndex = 0;

	for (int i = 0; i < MAP_SIDE_LENGTH; ++i)
	{
		double tileOffsetAmt = (MAP_DIAMETER - MAP_SIDE_LENGTH - i )/2.0;	// amount of tiles row is offset by 
		double tileOffset = tileOffsetAmt * tileHeight + tileHeight / 2.0;  // tileOffsetAmt + tiles already place on row (in pixels)
		m_tileArray.push_back(new Tile(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2) + tileRadius/2)));

		for (int j = 1; j < MAP_SIDE_LENGTH + i; ++j) 
		{
			tileOffset += tileHeight;
			m_tileArray.push_back(new Tile(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2) + tileRadius / 2)));
		}
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < m_tileArray.size(); ++i)
	{
		m_tileArray[i]->Draw(rw);
	}
}

Level::~Level()
{
	for (int i = 0; i < m_tileArray.size(); ++i)
	{
		delete m_tileArray[i];
	}
	m_tileArray.clear();
}