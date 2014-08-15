#include "Level.h"
#include <unordered_map>
#include <iostream>
using namespace std;


Level::Level(int windowSize)
{
	tileTable = new	unordered_map<string, Tile*>();
	float tileHeight = windowSize / MAP_DIAMETER;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xMapOffset = 0;
	float yMapOffset = 0;
	float xOffset = 0;
	float yOffset;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;

	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		xOffset += tileDiameter * 3.0 / 4.0;
		yOffset = tileHeight*((MAP_DIAMETER - abs(rowMax - rowMin)) / 2.0);	
		for (int r = rowMin; r <= rowMax; ++r)
		{
			(*tileTable)[to_string(c) + "_" + to_string(r)] = new Tile(tileRadius, sf::Vector2f(xOffset + xMapOffset, yOffset + yMapOffset));
			yOffset += tileHeight;
		}
		if (c < 0)
			rowMin--;
		else
			rowMax--;
		cout << endl;
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (auto it = tileTable->begin(); it != tileTable->end(); ++it)
	{
		it->second->Draw(rw);
	}
}

Level::~Level()
{
	for (auto it = tileTable->begin(); it != tileTable->end();)
	{
		it = tileTable->erase(it);
	}
	delete tileTable;
}