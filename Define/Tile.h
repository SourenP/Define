#ifndef TILE_H
#define TILE_H

#include "SFML\Graphics.hpp"
#include "Cell.h"

#include <string>

using std::string;

class Tile
{
public:
	Tile(float radius, sf::Vector2f position, sf::Vector3i coordinates);
	void Draw(sf::RenderWindow& window);
	void SetCell(const Cell& cell, int index);
	void Tile::SetEmpty();
	void SetBorderColor(sf::Color);
	int GetCellIndex() const;
	double GetRadius() const;
	int Tile::GetCellTeam() const;
	sf::Vector3i GetCoordinates();
	const sf::Color DEFAULT_COLOR = sf::Color::White;
	void SetText(string);
	void Unmark();
	void MarkForSetup();
private:
	Tile(const Tile&);
	Tile& operator=(const Tile&);
	sf::Text m_text;
	sf::Font m_font;
	sf::Vector3i m_coordinates;
	sf::CircleShape m_hexagon;
	int m_cellIndex;
};

#endif