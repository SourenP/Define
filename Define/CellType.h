#ifndef CELLTYPE_H
#define CELLTYPE_H
#include "SFML\Graphics.hpp"
using namespace std;

class CellType
{
public:
	struct Move
	{
		int tileID;
		sf::Color targetColor; 
	};

	CellType();
	int GetID();
	sf::Color GetColor();

private:
	static int m_gid;	// increasing global cell id
	static vector < sf::Color > typeColors;
	int m_id;			// specific cell id
	sf::Color m_color;
};

#endif