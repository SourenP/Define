#include "Tile.h"
#include <iostream>

Tile::Tile(float radius, sf::Vector2f position, sf::Vector3i coordinates)
{
	float height = radius * sqrt(3);
	m_hexagon.setFillColor(DEFAULT_COLOR);
	m_hexagon.setOutlineThickness(-radius/10);
	m_hexagon.setOutlineColor(sf::Color(200,200,200));
	m_hexagon.setRadius(radius);
	m_hexagon.setPointCount(6);
	m_hexagon.setOrigin(radius, radius);
	m_hexagon.setRotation(30); 
	m_hexagon.setPosition(position);
	m_coordinates = coordinates;
	SetEmpty();
}

double Tile::GetRadius() const
{
	return m_hexagon.getRadius();
}

void Tile::MarkForSetup()
{
	m_hexagon.setOutlineColor(sf::Color::Red);
}

void Tile::Unmark()
{
	m_hexagon.setOutlineColor(sf::Color(200, 200, 200));
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(m_hexagon);
	sf::Text coords;
	sf::Font f;
	f.loadFromFile("arial.ttf");
	coords.setPosition(m_hexagon.getPosition());
	coords.setFont(f);
	coords.setCharacterSize(18);
	coords.setColor(sf::Color::Red);
	coords.setString(std::to_string(m_coordinates.x) + ", " + std::to_string(m_coordinates.y) + ", " + std::to_string(m_coordinates.z));
	coords.setPosition(m_hexagon.getPosition());
	window.draw(coords);
}

sf::Vector3i Tile::GetCoordinates()
{
	return m_coordinates;
}

// Sets the Tile's index and color to match the cell but does not change the Cell's location
void Tile::SetCell(const Cell& cell, int index)
{
	m_hexagon.setFillColor(cell.GetColor());
	m_cellIndex = index;
}

void Tile::SetEmpty()
{
	m_hexagon.setFillColor(DEFAULT_COLOR);
	m_cellIndex = -1;

}

int Tile::GetCellIndex() const
{
	return m_cellIndex;
}

