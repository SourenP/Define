#include "CellType.h"

CellType::CellType(int priority)
{
	static int m_gid = 0;
	typeColors = { sf::Color::Red, sf::Color::Green, sf::Color::Blue, sf::Color::Magenta }; // limited to 4 cell types for now
	m_id = m_gid++;
	m_color = typeColors[m_id];
	m_priority = priority;
}

int CellType::GetID()
{
	return m_id;
}

sf::Color CellType::GetColor()
{
	return m_color;
}

int CellType::GetPriority()
{
	return m_priority;
}