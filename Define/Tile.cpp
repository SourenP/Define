#include "Tile.h"

Tile::Tile(float radius, sf::Vector2f position, sf::Vector3i coordinates)
{
	float height = radius * sqrt(3);
	m_hexagon.setFillColor(DEFAULT_COLOR);
	m_hexagon.setOutlineThickness(-radius/10);
	m_hexagon.setOutlineColor(sf::Color::White);
	m_hexagon.setRadius(radius);
	m_hexagon.setPointCount(6);
	m_hexagon.setOrigin(radius / 2.0, height / 2.0);
	m_hexagon.setPosition(position);
	m_hexagon.setRotation(30);
	m_coordinates.x = coordinates.x;
	m_coordinates.y = coordinates.y;
	m_coordinates.z = coordinates.z;
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(m_hexagon);
}

void Tile::SetColor(sf::Color color)
{
	m_hexagon.setFillColor(color);
}

sf::Vector3i Tile::GetCoordinates()
{
	return m_coordinates;
}


