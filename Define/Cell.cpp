#include "Cell.h"

Cell::Cell(int id, sf::Color color)
{
	m_ID = id;
	m_color = color;
}

int Cell::GetID()
{
	return m_ID;
}

sf::Color Cell::GetColor()
{
	return m_color;
}