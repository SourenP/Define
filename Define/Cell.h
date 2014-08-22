#ifndef CELL_H
#define CELL_H
#include "SFML\Graphics.hpp"
#include "CellType.h"

class Cell
{
public:
	Cell(CellType *celltype, sf::Vector3i startLocation);
	~Cell();

	sf::Color GetColor() const;
	bool setLocation(sf::Vector3i newLocation);
<<<<<<< HEAD
	sf::Vector3i GetLocation();
=======
	sf::Vector3i GetLocation() const;
	int ComparePriority(const Cell& cell) const;
>>>>>>> origin/master
	int GetPriority();
	int GetTypeID();
	bool IsAlive();
	void SetIsAlive(bool status);

private:
	CellType *m_type;
	bool m_alive;
	sf::Vector3i m_location;
};

#endif