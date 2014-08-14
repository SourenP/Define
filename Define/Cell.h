#include "SFML\Graphics.hpp"

class Cell
{
public:
	struct Move
	{
		int tileID;
		sf::Color targetColor; 
	};

	Cell(sf::Color color);

	int GetID();
	sf::Color GetColor();

private:
	static int m_gid;
	int m_id;
	sf::Color m_color;
};