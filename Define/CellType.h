#ifndef CELLTYPE_H
#define CELLTYPE_H
#include "SFML\Graphics.hpp"
using namespace std;

class CellType
{
public:
	CellType();
	int GetID();
	sf::Color GetColor();
	int GetPriority();

private:
	static int m_gid;	// increasing global celltype id
	vector <sf::Color> typeColors; // can we make this static???
	int m_id;			// specific celltype id
	sf::Color m_color;
};

#endif