#ifndef CELL_H
#define CELL_H
#include "SFML\Graphics.hpp"
#include "CellType.h"

class Cell
{
public:
	Cell(CellType celltype);
	sf::Color GetColor();

private:
	CellType type;
};

#endif