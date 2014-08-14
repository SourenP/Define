#include "Cell.h"

Cell::Cell(sf::Color color)
{
	static int m_gid = 0;
	m_id = m_gid++;
	m_color = color;
}

int Cell::GetID()
{
	return m_id;
}

sf::Color Cell::GetColor()
{
	return m_color;
}