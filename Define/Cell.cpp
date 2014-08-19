#include "Cell.h"
#include "CellType.h"

Cell::Cell(CellType celltype)
{
	type = celltype;
}

sf::Color Cell::GetColor()
{
	return type.GetColor();
}