#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <iostream>
#include <queue>

#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "Cell.h"
#include "CellType.h"
#include "comparisons.h"
#include "define_structs.h"

using std::vector;
using std::priority_queue;

class Level
{
public:

	Level() {};
	bool Start(int windowSize);
	Level(int windowSize);
	//void Update(Cell::Move);
	void Draw(sf::RenderWindow&);
	sf::Vector2i indexFromCoordinates(sf::Vector3i coordinates);
	Tile* GetTile(sf::Vector3i coordinates);
	const Cell* GetNextCell();
	const vector<Cell*> GetCellContainer() const;
	const vector<Tile*> GetTileContainer() const;

	~Level();

private:

	Level(const Level&);
	Level& operator=(const Level&);

	static const int MAP_SIDE_LENGTH = 30;
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1;
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER;
	int m_tileIDs[MAP_DIAMETER][MAP_DIAMETER]; // on the stack?

	priority_queue<HeapNode, vector<HeapNode>, compareHeapNodes> m_priorityHeap;
	vector<Tile*> m_tiles;
	vector<Cell*> m_cells;
};

#endif