#include "CellType.h"

CellType::CellType()
{
	static int m_gid = 0;
	typeColors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta }; // limited to 4 cell types for now
	m_id = m_gid++;
	m_color = typeColors[m_id];
}

int CellType::GetID()
{
	return m_id;
}

sf::Color CellType::GetColor()
{
	return m_color;
}