#ifndef CELLTYPE_H
#define CELLTYPE_H

#include "SFML\Graphics.hpp"

#include "define_structs.h"

using std::vector;

class CellType
{
public:
	CellType(int ID, vector<CellRule> rule, sf::Color color = sf::Color::Green);
	int GetID();
	sf::Color GetColor();
	int GetPriority();
	int GetNumberOfRules();
	vector<CellRule> GetRules(); //Get the rule by index. Engine should loop over all of the cells rules

private:
	//static int m_gid;	// increasing global celltype id
	int m_id;			// specific celltype id
	sf::Color m_color;
	vector<CellRule> m_rules;
};

#endif