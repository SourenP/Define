#include "SFML\Graphics.hpp"

class CellType
{
public:
	struct Move
	{
		int tileID;
		sf::Color targetColor; 
	};

	CellType(sf::Color color);
	int GetID();
	sf::Color GetColor();

private:
	static int m_gid;
	int m_id;
	sf::Color m_color;
};