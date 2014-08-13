#include "Level.h"

Level::Level(int windowSize)
{
	float tileHeight = (windowSize / MAP_DIAMETER);
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float topTileY;

	for (int i = 0; i < MAP_SIDE_LENGTH; ++i)
	{
		float mapOffset = tileHeight / 4.0;
		float tileOffsetAmt = (MAP_DIAMETER - MAP_SIDE_LENGTH - i) / 2.0;	// amount of tiles row is offset by 
		float tileOffset = tileOffsetAmt * tileHeight + mapOffset;  // tileOffsetAmt + tiles already place on row (in pixels)

		topTileY = i * (tileRadius + tileRadius / 2.0) + tileRadius / 2.0;
		for (int j = 0; j < MAP_SIDE_LENGTH + i; ++j) 
		{
			m_tileArray.push_back(new Tile(tileRadius, sf::Vector2f(tileOffset, topTileY)));
			tileOffset += tileHeight;
		}
	}
	topTileY -= tileRadius + tileRadius/2;
	//Bottom Half
	for (int i = MAP_SIDE_LENGTH - 2; i >= 0; --i)
	{
		float mapOffset = tileHeight / 4.0;
		float tileOffsetAmt = (MAP_DIAMETER - MAP_SIDE_LENGTH - i) / 2.0;	// amount of tiles row is offset by 
		float tileOffset = tileOffsetAmt * tileHeight + mapOffset;  // tileOffsetAmt + tiles already place on row (in pixels)

		float botTileY = topTileY + (MAP_SIDE_LENGTH - i) * (tileRadius + tileRadius / 2.0);
		for (int j = 0; j < MAP_SIDE_LENGTH + i; ++j)
		{
			
			m_tileArray.push_back(new Tile(tileRadius, sf::Vector2f(tileOffset, botTileY)));
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