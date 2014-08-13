#ifndef TILE_H
#define TILE_H

#include "SFML\Graphics.hpp"

class Tile
{
public:
	Tile(int radius, sf::Vector2f position);
	void Initialize(int radius, sf::Vector2f position);
	void Draw(sf::RenderWindow& window);
	void SetColor(sf::Color color);
	void SetColor(int R, int G, int B);
	
private:
	Tile(const Tile&);
	Tile& operator=(const Tile&);

	sf::CircleShape m_hexagon;
	const sf::Color DEFAULT_COLOR = sf::Color::Cyan;
};

#endif