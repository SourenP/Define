#ifndef TILE_H
#define TILE_H

#include "SFML\Graphics.hpp"

class Tile
{
public:
	Tile(float radius, sf::Vector2f position, sf::Vector3i coordinates);
	void Draw(sf::RenderWindow& window);
	void SetColor(sf::Color color);
	sf::Vector3i GetCoordinates();
	
private:
	Tile(const Tile&);
	Tile& operator=(const Tile&);	

	sf::Vector3i m_coordinates;
	sf::CircleShape m_hexagon;
	const sf::Color DEFAULT_COLOR = sf::Color::White;
};

#endif