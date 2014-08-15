#ifndef LEVEL_H
#define LEVEL_H

#include "SFML\Graphics.hpp"
#include "Tile.h"
//#include "Cell.h"
#include <vector>
#include <unordered_map>
using namespace std;

using std::vector;

class Level
{
public:

	Level() {};
	bool Start(int windowSize);
	Level(int windowSize);
	//void Update(Cell::Move);
	void Draw(sf::RenderWindow&);
	~Level();

private:
	Level(const Level&);
	Level& operator=(const Level&);

	static const int MAP_SIDE_LENGTH = 4;
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1;
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER;
	unordered_map<string, Tile*>* tileTable;
	int m_cellMap[MAP_SIDE_LENGTH][MAP_SIDE_LENGTH];
	
	vector<Tile*> m_tileArray;
	//vector<Cell*> m_cellArray;
};

#endif