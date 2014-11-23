#ifndef HEXAGON_GENERATOR_H
#define HEXAGON_GENERATOR_H

#include <Windows.h>
#include <vector>
#include <queue>
#include <iostream>

#include "Hexagon.h"
#include "Define\CellType.h"
#include "tinyxml2.h"

using std::cout;
using std::endl;
using std::vector;
using std::pair;
using std::queue;

static const int hexNeighbors[6][2] = { { 1, 0 }, { 1, -1 }, { 0, -1 }, { -1, 0 }, { -1, 1 }, { 0, 1 } };

class HexagonGenerator
{
public:
	HexagonGenerator() {};
	~HexagonGenerator();

	void GenerateHexagons(int screenWidth, int screenHeight, double radius = DEFAULT_RADIUS, unsigned int rings = DEFAULT_RINGS); //Creates hexigons, centered in the middle of the window. The number of rings of hexagons is based on the rings varaiable. 
	RECT& CycleClickedHexagon(const POINT& mouseCoordinates);

	void SaveRule(int direction, ActionType actionType); //Saves rule to CellType
	string SaveCellType(sf::Color color); //Save CellType
	void SaveToXML(); //Save CellTypes to XML
	void DrawHexagons(HDC& hdc) const; //Draws all hexagons

private:
	struct HexNode //Structure used to populate map, hold the coordinates, the indicies inside m_hexMap and the ring depth of a hexagon
	{
		HexNode();
		HexNode(POINT p, pair<int, int> i, int d)
		{
			coordinates = p;
			indicies = i;
			depth = d;
		}
		POINT coordinates;
		pair<int, int> indicies;
		int depth;
	};

	pair<int, int> RoundToNearestHexagon(double i, double j);
	bool IsOutOfMapBounds( pair<int, int> indicies);
	HexagonGenerator& operator=(HexagonGenerator& hexGen);
	HexagonGenerator(HexagonGenerator& hexGen);
	void CycleHexagon();
	void SeedHexagon(const HexNode& currentSeed);//Recursive method for populating map. Requires currentSeed and the queue vector

	static const unsigned int DEFAULT_RINGS = 1;
	static const double DEFAULT_RADIUS;
	int m_rings; //How many "rings" of neightbors to draw
	double m_hexagonRadius; //Hexagon radius
	double m_ringDistance; //Distance between rings
	vector<Hexagon*> m_hexagons; //Container for hexagons
	vector<vector<int>> m_hexMap; //Map denoting filled hexes
	queue<HexNode> seedQueue;
	POINT m_center;
	vector<CellType*> m_cellTypes; //Stores all created Cell Types. A Cell Type is created when the "Accept Cell Type" button is clicked
	vector<CellRule> m_storedRules; //Stores all the rules created. A CellRule is created when the "Accept Rule" button is clicked.
									//When the "Accept Cell Type" button is clicked all CellRules are aded to the new CellType and this vector is emptied
};

#endif