#include "Cell.h"
#include "CellType.h"

Cell::Cell(CellType *celltype, sf::Vector3i startLocation)
{
	m_type = celltype;
	m_location = startLocation;

	SetIsAlive(true);
}

Cell::~Cell()
{
	delete m_type;
}

sf::Color Cell::GetColor() const
{
	return m_type->GetColor();
}

void Cell::SetIsAlive(bool status)
{
	m_alive = status;
}

bool Cell::IsAlive()
{
	return m_alive;
}

bool Cell::setLocation(sf::Vector3i newLocation)
{
	m_location = newLocation;
	// if tileFree(newLocation)
	return 1; // should return success/failer based on destination being free/occupied
}

sf::Vector3i Cell::GetLocation() const
{
	return m_location;
}
int Cell::GetPriority()
{
	return m_type->GetPriority();
}

int Cell::GetTypeID()
{
	return m_type->GetID();
}