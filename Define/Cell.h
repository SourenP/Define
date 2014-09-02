#ifndef CELL_H
#define CELL_H
#include "SFML\Graphics.hpp"
#include "CellType.h"

class Cell
{
public:
	Cell(CellType *celltype, sf::Vector3i startLocation, int team);
	//~Cell();

	int ComparePriority(const Cell& cell) const;

	sf::Vector3i GetLocation() const;
	sf::Color GetColor() const;
	int GetPriority() const;
	int GetTypeID() const;
	int GetTeam() const;
	bool IsAlive() const;

	void SetIsAlive(bool status);
	bool setLocation(sf::Vector3i newLocation);

private:
	CellType *m_type;
	bool m_alive;
	sf::Vector3i m_location;
	int m_currentPriority;
	int m_team;
};

#endif