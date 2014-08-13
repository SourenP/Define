#include "Level.h"

Level::Level(int windowSize)
{
	float tileHeight = (windowSize / MAP_DIAMETER);
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;

	for (int i = 0; i < MAP_SIDE_LENGTH; ++i)
	{
		float mapOffset = tileHeight / 4.0;
		float tileOffsetAmt = (MAP_DIAMETER - MAP_SIDE_LENGTH - i) / 2.0;	// amount of tiles row is offset by 
		float tileOffset = tileOffsetAmt * tileHeight + mapOffset;  // tileOffsetAmt + tiles already place on row (in pixels)

		for (int j = 0; j < MAP_SIDE_LENGTH + i; ++j) 
		{
			m_tileArray.push_back(new Tile(tileRadius, sf::Vector2f(tileOffset, i * (tileRadius + tileRadius / 2.0) + tileRadius / 2.0)));
			tileOffset += tileHeight;
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

void Level::Update(Cell::Move move)
{
	m_tileArray[move.tileID]->SetColor(move.targetColor);
}

Level::~Level()
{
	for (int i = 0; i < m_tileArray.size(); ++i)
	{
		delete m_tileArray[i];
	}
	m_tileArray.clear();
}