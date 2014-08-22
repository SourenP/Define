#include "Cell.h"
#include "CellType.h"

Cell::Cell(CellType *celltype, sf::Vector3i startLocation)
{
	m_type = celltype;
	m_location = startLocation;
	m_priority = m_type->GetPriority();
}

sf::Color Cell::GetColor()
{
	return m_type->GetColor();
}

bool Cell::setLocation(sf::Vector3i newLocation)
{
	m_location = newLocation;
	// if tileFree(newLocation)
	return 1; // should return success/failer based on destination being free/occupied
}

sf::Vector3i Cell::GetLocation()
{
	return m_location;
}

int Cell::ComparePriority(const Cell& cell) const
{
	if (m_priority < cell.m_priority) 
	{
		return -1;
	}
	else if (m_priority > cell.m_priority) 
	{
		return 1;
	}
	return 0;
}

int Cell::GetPriority()
{
	return m_priority;
}

int Cell::GetTypeID()
{
	return m_type->GetID();
}