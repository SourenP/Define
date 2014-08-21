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
	vector<vector<int>>& GetNeighbors(int x, int y, int z);
	sf::Vector2i indexFromCoordinates(sf::Vector3i coordinates);
	Tile* GetTile(sf::Vector3i coordinates);
	~Level();

private:
	Level(const Level&);
	Level& operator=(const Level&);

	int neighborOffsets[6][3];
	static const int MAP_SIDE_LENGTH = 4;
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1;
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER;
	int m_tileIDs[MAP_DIAMETER][MAP_DIAMETER]; // on the stack?
	vector<Tile*>* m_tiles;
	
	//vector<Cell*> m_cellArray;
};

#endif