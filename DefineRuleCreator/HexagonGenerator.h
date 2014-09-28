#ifndef HEXAGON_GENERATOR_H
#define HEXAGON_GENERATOR_H

#include <Windows.h>
#include <vector>
#include <queue>
#include <iostream>
#include "Hexagon.h"

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
	string GetRule();
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

	HexagonGenerator& operator=(HexagonGenerator& hexGen);
	HexagonGenerator(HexagonGenerator& hexGen);
	void CycleHexagon();
	void SeedHexagon(const HexNode& currentSeed);//, queue<HexNode>& seedQueue); //Recursive method for populating map. Requires currentSeed and the queue vector

	static const unsigned int DEFAULT_RINGS = 1;
	static const double DEFAULT_RADIUS;
	int m_rings; //How many "rings" of neightbors to draw
	double m_hexagonRadius; //Hexagon radius
	double m_ringDistance; //Distance between rings
	vector<Hexagon*> m_hexagons; //Container for hexagons
	vector<vector<int>> m_hexMap; //Map denoting filled hexes
	queue<HexNode> seedQueue;
};

#endif