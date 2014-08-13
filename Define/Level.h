#ifndef LEVEL_H
#define LEVEL_H

#include "SFML\Graphics.hpp"
#include "Tile.h"

class Level
{
public:
	bool Start(int windowSize);
	void Draw(sf::RenderWindow&);
	bool Destroy();
private:
	static const int MAP_SIDE_LENGTH = 5;
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1;
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER;
	int m_cellMap[MAP_SIDE_LENGTH][MAP_SIDE_LENGTH];
	Tile m_tileArray[TILE_COUNT];
};

#endif