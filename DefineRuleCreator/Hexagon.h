#ifndef HEXAGON_H
#define HEXAGON_H

#include <Windows.h>
#include <math.h>
#include <string>
#include<tchar.h>

#include "Helper_Functions.h"


using std::string;

class Hexagon
{
public:
	static const enum  HexagonState
	{
		Empty = 0,
		Ally = 1,
		Enemy = 2,
	};

	Hexagon(POINT newOrigin, double newRadius); //Creates a new Hexagon and generates vertices

	const POINT GetOrigin() const; //Returns coordiantes of center
	const HexagonState GetState() const;
	void Draw(HDC& hdc) const;

	void CycleState();
	
private:
	static const LPCWSTR m_labels[3];

	POINT m_origin;
	double m_radius;
	POINT m_vertices[6];
	HexagonState m_state;
};

#endif