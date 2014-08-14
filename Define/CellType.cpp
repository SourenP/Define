#include "CellType.h"

CellType::CellType(sf::Color color)
{
	static int m_gid = 0;
	m_id = m_gid++;
	m_color = color;
}

int CellType::GetID()
{
	return m_id;
}

sf::Color CellType::GetColor()
{
	return m_color;
}