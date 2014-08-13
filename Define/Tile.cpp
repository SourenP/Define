#include "Tile.h"

Tile::Tile(float radius, sf::Vector2f position)
{
	m_hexagon.setFillColor(DEFAULT_COLOR);
	m_hexagon.setRadius(radius);
	m_hexagon.setPointCount(6);
	m_hexagon.setOrigin(radius / 2, radius / 2);
	m_hexagon.setPosition(position);
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(m_hexagon);
}

void Tile::SetColor(sf::Color color)
{
	m_hexagon.setFillColor(color);
}

