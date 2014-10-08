#include "CellType.h"

CellType::CellType(int ID, vector<CellRule> rule, sf::Color color)
{
	m_id = ID;
	m_rules = rule;
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

int CellType::GetNumberOfRules()
{
	return m_rules.size();
}

CellRule CellType::GetRule(int index)
{
	return m_rules[index];
}
