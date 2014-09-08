#ifndef CELLTYPE_H
#define CELLTYPE_H
#include "SFML\Graphics.hpp"

#include "define_structs.h"

using std::vector;

class CellType
{
public:
	CellType(int ID, CellRule rule, sf::Color color = sf::Color::Green);

	int GetID();
	sf::Color GetColor();
	int GetPriority();
	CellRule GetRule();

private:
	//static int m_gid;	// increasing global celltype id
	int m_id;			// specific celltype id
	sf::Color m_color;
	CellRule m_rule;
};

#endif