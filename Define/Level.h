#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "Cell.h"
#include "CellType.h"
#include "define_structs.h"

using std::vector;
using std::priority_queue;
using std::cin;
using std::ifstream;

class Level
{
public:
	Level(int windowSize);
	~Level();

	static const int MAP_SIDE_LENGTH = 10; //Number of tiles on side of map
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1; //Diameter of map
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER; //Total number of tiles
	
	void Draw(sf::RenderWindow&); //Draws tiles
	void Update(Changes changes); //Updates cells and tiles based on most recent changes
	
	bool CreateCell(CellType& celltype, sf::Vector3i location, int team); //Creates a new Cell
	bool MoveCell(sf::Vector3i origin, sf::Vector3i destination); //Moves cell using x,y,z coordinates

	const Tile& GetConstTile(sf::Vector3i coordinates) const; //Returns a tile from m_tiles
	
	int GetCellIndex(sf::Vector3i coordinates) const; //Returns cells index in m_cells
	const Cell& GetNextCell(); //Returns next cell on m_turnHeap
	const Cell& GetCellByIndex(int index) const; //Returns a cell from m_cells by index

	const bool IsOutOfBounds(sf::Vector3i coordinates) const;//Checks if position is out of bounds

	const vector<Cell*>& GetCellContainer() const; //Retrurns m_cells
	const vector<Tile*>& GetTileContainer() const; //Returns m_tiles
	vector<vector<int>> GetTileIDs() const; //Return m_tileIDs
	
	sf::Vector2i IndexFromCoordinates(sf::Vector3i coordinates) const; //Converts coordinates from x,y,z to i,j for 
																	  //use with m_tileID's

private:

	Level(const Level&);
	Level& operator=(const Level&);

	void InitializeCells(); //TEST CASE INITALIZER
	void LoadCellTypes(ifstream& file); //Reads cell types from file

	priority_queue<HeapNode, vector<HeapNode>, compareHeapNodes> m_turnHeap; //Heap for storing cell turns
	vector<Tile*> m_tiles; //Stores tiles
	vector<Cell*> m_cells; //Stores cells
	vector<CellType*> m_cellTypes; //Stores CellTypes
	vector<vector<int>> m_tileIDs; //Matrix that is used to keep track of which cell is where. Each ID is the index of the cell in m_cells
	Tile* GetTile(sf::Vector3i coordinates); //Uses x,y,z to retrieve a tile

	int cellCount = 0;
	ifstream m_cellTypeFile; //File containing CellTypes
};

#endif