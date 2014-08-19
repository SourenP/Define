#include "Level.h"
#include <unordered_map>
#include <iostream>
using namespace std;


Level::Level(int windowSize)
{
	// Set up neighborOffsets array to use in GetNeighbors
	int neighborNumbers[6][3] = { { +1, -1, 0 }, { +1, 0, -1 }, { 0, +1, -1 }, { -1, +1, 0 }, { -1, 0, +1 }, { 0, -1, +1 } };
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 3; j++)
			neighborOffsets[i][j] = neighborNumbers[i][j];

	m_tileTable = new unordered_map<string, Tile*>();
	float tileHeight = windowSize / MAP_DIAMETER;
	float tileRadius = tileHeight / sqrt(3);
	float tileDiameter = 2 * tileRadius;
	float xMapOffset = 0;
	float yMapOffset = 0;
	float xOffset = 0;
	float yOffset;
	int rowMin = 0;
	int rowMax = MAP_SIDE_LENGTH - 1;

	// c and r produce numbers matchin axial coordinates
	for (int c = 1-MAP_SIDE_LENGTH; c < MAP_SIDE_LENGTH; ++c)
	{
		xOffset += tileDiameter * 3.0 / 4.0;
		yOffset = tileHeight*((MAP_DIAMETER - abs(rowMax - rowMin)) / 2.0);
		for (int r = rowMin; r <= rowMax; ++r)
		{
			// Map key is based on cube coordinates x_z_y (Conversion from axial to cube: x = c  z = r  y = -x-z)
			(*m_tileTable)[to_string(c) + "_" + to_string(r) + "_" + to_string(-c - r)] =
				 new Tile(tileRadius, sf::Vector2f(xOffset + xMapOffset, yOffset + yMapOffset), sf::Vector3i(c, r, -c - r));
			yOffset += tileHeight;
		}
		c < 0 ? rowMin-- : rowMax--;
	}

	//testing
	(*m_tileTable)["0_0_0"]->SetColor(sf::Color::Red);
	vector<vector<int>> n = GetNeighbors(0, 0, 0);
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 3; j++)
			cout << n[i][j] << " ";
		cout << endl;
	}
}

void Level::Draw(sf::RenderWindow& rw)
{
	for (auto it = m_tileTable->begin(); it != m_tileTable->end(); ++it)
	{
		it->second->Draw(rw);
	}
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

Level::~Level()
{
	for (auto it = m_tileTable->begin(); it != m_tileTable->end();)
	{
		it = m_tileTable->erase(it);
	}
	delete m_tileTable;
}