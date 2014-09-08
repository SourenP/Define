#include "CellType.h"

CellType::CellType(int ID, CellRule rule, sf::Color color)
{
	m_id = ID;
	m_rule = rule;
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

CellRule CellType::GetRule()
{
	return m_rule;
}