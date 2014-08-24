#include "Tile.h"

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
}

void Tile::Draw(sf::RenderWindow& window)
{
	window.draw(m_hexagon);
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

int Tile::GetCellIndex()
{
	return m_cellIndex;
}

