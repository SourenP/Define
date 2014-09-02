#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <iostream>
#include <queue>

#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "Cell.h"
#include "CellType.h"
#include "define_structs.h"

using std::vector;
using std::priority_queue;

class Level
{
public:
	Level(int windowSize);
	~Level();

	static const int MAP_SIDE_LENGTH = 30;
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1;
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER;
	
	void Draw(sf::RenderWindow&);
	void Update(Changes changes);
	
	bool CreateCell(CellType *celltype, sf::Vector3i location, int team);
	bool MoveCell(sf::Vector3i origin, sf::Vector3i destination);

	const Tile* GetConstTile(sf::Vector3i coordinates) const;
	int GetCellIndex(sf::Vector3i coordinates) const;
	const Cell* GetNextCell();

	const vector<Cell*>& GetCellContainer() const;
	const vector<Tile*>& GetTileContainer() const;
	int** GetTileIDs() const;
	
	sf::Vector2i indexFromCoordinates(sf::Vector3i coordinates) const;

private:

	Level(const Level&);
	Level& operator=(const Level&);

	void InitializeCells();

	priority_queue<HeapNode, vector<HeapNode>, compareHeapNodes> m_priorityHeap;
	vector<Tile*> m_tiles;
	vector<Cell*> m_cells;
	vector<CellType*> m_cellTypes;
	int **m_tileIDs;
	Tile* GetTile(sf::Vector3i coordinates);

	int cellCount = 0;
};

#endif