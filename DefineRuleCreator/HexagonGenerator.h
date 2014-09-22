#ifndef HEXAGON_GENERATOR_H
#define HEXAGON_GENERATOR_H

#include <Windows.h>
#include <vector>

#include "Hexagon.h"

using std::vector;
using std::pair;

static const int hexNeighbors[6][2] = { { 0, -1 }, { 1, -1 }, { 1, 0 }, { 0, 1 }, { -1, 1 }, { -1, 0 } };

class HexagonGenerator
{
public:
	HexagonGenerator() {};
	~HexagonGenerator();
	void GenerateHexagons(int screenWidth, int screenHeight, double radius = DEFAULT_RADIUS, unsigned int rings = DEFAULT_RINGS); //Creates hexigons, centered in the middle of the window. The number of rings of hexagons is based on the rings varaiable. 

	void DrawHexagons(HDC& hdc) const; //Draws all hexagons
private:
	

	HexagonGenerator& operator=(HexagonGenerator& hexGen);
	HexagonGenerator(HexagonGenerator& hexGen);
	void SeedHexagon(const POINT& origin, pair<int, int> indicies, int depth);

	static const unsigned int DEFAULT_RINGS = 1;
	static const double DEFAULT_RADIUS;
	int m_rings; //How many "rings" of neightbors to draw
	double m_hexagonRadius;
	double m_ringDistance;
	vector<Hexagon*> m_hexagons;
	vector<vector<int>> m_hexMap; //Map denoting filled hexes
};

#endif