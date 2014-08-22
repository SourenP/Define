#include "Level.h"
#include <unordered_map>
#include <iostream>
using namespace std;
#include "CellType.h"
#include "Cell.h"
#include "comparisons.h"
#include "SFML\Graphics.hpp"


Level::Level(int windowSize)
{
	// Set up neighborOffsets array to use in GetNeighbors & fill m_tileIDs with -1 
	int neighborNumbers[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			neighborOffsets[i][j] = neighborNumbers[i][j];
	for (int i = 0; i < MAP_DIAMETER; i++)
		for (int j = 0; j < MAP_DIAMETER; j++)
			m_tileIDs[i][j] = -1;

	float tileHeight = windowSize / MAP_DIAMETER;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xThickness = (MAP_DIAMETER - 1) * tileDiameter * 3.0 / 4.0 + tileDiameter;
	float xMapOffset = (windowSize - xThickness) / 2.0;
	float yMapOffset = 0;
	float xOffset = tileRadius;
	float yOffset;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;
	int tileID = 0;

	// c and r produce numbers matchin axial coordinates
	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		yOffset = tileHeight*((MAP_DIAMETER - abs(rowMax - rowMin)) / 2.0);
		for (int r = rowMin; r <= rowMax; ++r)
		{
			m_tiles.push_back(new Tile(tileRadius, sf::Vector2f(xOffset + xMapOffset, yOffset + yMapOffset), sf::Vector3i(c, r, -c - r)));
			//cout << "r: " << r + MAP_SIDE_LENGTH - 1 << "    c: " << c + MAP_SIDE_LENGTH - 1 << endl;
			m_tileIDs[r + MAP_SIDE_LENGTH - 1][c + MAP_SIDE_LENGTH - 1] = tileID;
			tileID++;
			yOffset += tileHeight;
		}
		xOffset += tileDiameter * 3.0 / 4.0;
		c < 0 ? rowMin-- : rowMax--;
	}

	//testing
	CellType red(10);
	CellType green(20);
	CellType blue(30);
	
	Cell test1(&red, sf::Vector3i(0,0,0));
	Cell test2(&green, sf::Vector3i(-1, 0, 1));
	Cell test3(&blue, sf::Vector3i(-2, 0 , 2));

	m_cells.push_back(&test1);
	m_cells.push_back(&test2);
	m_cells.push_back(&test3);

	/*for (size_t i = 0; i < m_cells.size(); i++)
	{
		cout << i << endl;
		sf::Vector3i currentLoc = m_cells[i]->GetLocation();
		Tile* currentTile = GetTile(currentLoc);
		currentTile->SetColor(m_cells[i]->GetColor());
	}*/
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (int i = 0; i < m_tiles.size(); i++)
		m_tiles[i]->Draw(rw);
}

// returnes by reference (might cause memory issues)
vector<vector<int>>& Level::GetNeighbors(int x, int y, int z)
{
	int coordinates[3] = { x, y, z };
	vector<vector<int>>* neighborCoordinates = new vector<vector<int>>(6, vector<int>(3));
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			(*neighborCoordinates)[i][j] = (coordinates[j] + neighborOffsets[i][j]);
		}
	}
	return *neighborCoordinates;
}

sf::Vector2i Level::indexFromCoordinates(sf::Vector3i coordinates)
{	
	return sf::Vector2i(coordinates.x + MAP_SIDE_LENGTH - 1, coordinates.z + MAP_SIDE_LENGTH - 1);
}

Tile* Level::GetTile(sf::Vector3i coordinates)
{
	sf::Vector2i indices = indexFromCoordinates(coordinates);
	int currID = m_tileIDs[indices.x][indices.y];
	return m_tiles[currID];
}

Level::~Level()
{
	for (std::vector<Tile*>::iterator it = m_tiles.begin(); it != m_tiles.end(); ++it) 
		delete *it;
	m_tiles.clear();
}