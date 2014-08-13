#ifndef TILE_H
#define TILE_H

#include "SFML\Graphics.hpp"

class Tile
{
public:
	void Create(int radius, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
	void SetColor(sf::Color color);
	void SetColor(int R, int G, int B);
	
private:
	sf::CircleShape m_hexagon;
	const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
};

#endif