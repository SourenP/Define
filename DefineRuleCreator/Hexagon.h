#ifndef HEXAGON_H
#define HEXAGON_H

#include <Windows.h>
#include <math.h>
#include "Helper_Functions.h"

class Hexagon
{
public:
	Hexagon(POINT newOrigin, double newRadius); //Creates a new Hexagon and generates vertices

	const POINT GetOrigin() const; //Returns coordiantes of center

	void Draw(HDC& hdc) const;

private:	
	POINT m_origin;
	double m_radius;
	POINT m_vertices[6];
};

#endif