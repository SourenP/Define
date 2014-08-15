#include "Tile.h"

Tile::Tile(float radius, sf::Vector2f position)
{
	float height = radius * sqrt(3);
	m_hexagon.setFillColor(DEFAULT_COLOR);
	m_hexagon.setRadius(radius);
	m_hexagon.setPointCount(6);
	m_hexagon.setOrigin(radius / 2.0, height / 2.0);
	m_hexagon.setPosition(position);
	m_hexagon.setRotation(30);
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(m_hexagon);
}

void Tile::SetColor(sf::Color color)
{
	m_hexagon.setFillColor(color);
}

