#ifndef TILE_H
#define TILE_H

#include "SFML\Graphics.hpp"

class Tile
{
public:
	Tile(float radius, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
	void SetColor(sf::Color color);
	
private:
	Tile(const Tile&);
	Tile& operator=(const Tile&);

	sf::CircleShape m_hexagon;
	const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
};

#endif