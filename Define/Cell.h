#include "SFML\Graphics.hpp"

class Cell
{
public:
	struct Move
	{
		int tileID;
		sf::Color targetColor; 
	};

	Cell(int id, sf::Color color);

	int GetID();
	sf::Color GetColor();

private:
	int m_ID;
	sf::Color m_color;
};