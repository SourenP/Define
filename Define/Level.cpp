#include "Level.h"
#include <unordered_map>
#include <iostream>
using namespace std;

Level::Level(int windowSize)
{
	tileTable = new unordered_map<string, Tile*>();
	float tileHeight = 20;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xOffset = tileRadius;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;

	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		for (int r = rowMin; r <= rowMax; ++r)
		{
			(*tileTable)[c + "_" + r] = new Tile(tileRadius, sf::Vector2f(xOffset, (c + MAP_SIDE_LENGTH-1)*tileHeight)); // wrong x & y
		}
		if (c < 0)
			rowMin--;
		else
			rowMax--;
		xOffset += tileDiameter;
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (auto it = tileTable->begin(); it != tileTable->end(); ++it)
	{
		it->second->Draw(rw);
		cout << "$" << endl;
	}
}

Level::~Level()
{
	for (auto it = tileTable->begin(); it != tileTable->end(); ++it)
	{	
		it = tileTable->erase(it);
	}
	delete tileTable;
}