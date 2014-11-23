#ifndef LEVEL_H
#define LEVEL_H

#include <unordered_map>
#include <iostream>
#include <fstream>
#include <queue>

#include "SFML\Graphics.hpp"
#include "Tile.h"
#include "Cell.h"
#include "SetupUI.h"
#include "CellType.h"
#include "define_structs.h"
#include "tinyxml2.h"

using std::vector;
using std::priority_queue;
using std::cin;
using std::cout;
using std::ifstream;
using std::string;

using tinyxml2::XMLDocument;
using tinyxml2::XMLError;
using tinyxml2::XMLNode;
using tinyxml2::XMLElement;

class Level
{
public:
	Level(int windowSize);
	~Level();

	static const int MAP_SIDE_LENGTH = 4; //Number of tiles on side of map
	static const int MAP_DIAMETER = (2 * MAP_SIDE_LENGTH) - 1; //Diameter of map
	static const int TILE_COUNT = MAP_SIDE_LENGTH * (3 * MAP_SIDE_LENGTH - 1) - MAP_DIAMETER; //Total number of tiles
	
	void Draw(sf::RenderWindow&); //Draws tiles
	void Update(Changes changes); //Updates cells and tiles based on most recent changes
	
	bool CreateCell(CellType& celltype, sf::Vector3i location, int team); //Creates a new Cell

	const Tile& GetConstTile(sf::Vector3i coordinates) const; //Returns a tile from m_tiles
	
	bool ProcessMouseInput(int mouseX, int mouseY); //Processes Mouse X/Y during Setup, returns true if setup is complete;

	const bool IsOutOfBounds(sf::Vector3i coordinates) const;//Checks if position is out of bounds

	inline const vector<Cell*>& GetCellContainer() const; //Retrurns m_cells
	inline const vector<Tile*>& GetTileContainer() const; //Returns m_tiles
	inline vector<vector<int>> GetTileIDs() const; //Return m_tileIDs

	const vector<int> GetNeighborsByTeam(const Cell& cell) const; //Generates a size 6 vector of the neighbors of the cell based on the cells team
	int GetCellIndex(sf::Vector3i coordinates) const; //Returns cells index in m_cells
	const Cell& GetNextCell(); //Returns next cell on m_turnHeap
	inline const Cell& GetCell(int index) const; //Returns a cell from m_cells by index
	inline const Cell& GetCell(sf::Vector3i coordinates) const; //Returns a cell from m_cells using sf::Vector3i coordiantes

	inline sf::Vector2i GetIndexFromCoordinates(sf::Vector3i coordinates) const; //Converts coordinates from x,y,z to i,j for 
																	  //use with m_tileID's

private:
	Level(const Level&);
	Level& operator=(const Level&);

	SetupUI m_setupUI;

	sf::Vector3i RoundToNearestTile(sf::Vector3f);

	bool MoveCell(sf::Vector3i origin, sf::Vector3i destination); //Moves cell using x,y,z coordinates
	bool KillCell(sf::Vector3i targetCell); //Kills cell by setting m_alive to false
	Tile* GetTile(sf::Vector3i coordinates); //Uses x,y,z to retrieve a tile
	void InitializeCells(); //TEST CASE INITALIZER
	void LoadCellTypes(string file); //Reads cell types from file

	priority_queue<HeapNode, vector<HeapNode>, compareHeapNodes> m_turnHeap; //Heap for storing cell turns
	vector<Tile*> m_tiles; //Stores tiles
	vector<Cell*> m_cells; //Stores cells
	vector<CellType*> m_cellTypes; //Stores CellTypes
	vector<vector<int>> m_tileIDs; //Matrix that is used to keep track of which cell is where. Each ID is the index of the cell in m_cells
	Tile* m_currSetupTile;

	bool m_isBeingSetup;
	int cellCount = 0;
	XMLDocument m_cellTypeFile; //File containing CellTypes
};

#endif