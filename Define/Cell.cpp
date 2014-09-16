#include "Cell.h"
#include "CellType.h"

Cell::Cell(CellType& celltype, sf::Vector3i startLocation, int team) : m_type(celltype)
{
	m_location = startLocation;
	SetIsAlive(true);
	m_currentPriority = 4;
	m_team = team;
}

//Cell::~Cell()
//{
//}

sf::Color Cell::GetColor() const
{
	return m_type.GetColor();
}

void Cell::SetIsAlive(bool status)
{
	m_alive = status;
}

bool Cell::IsAlive() const
{
	return m_alive;
}

bool Cell::SetLocation(sf::Vector3i newLocation)
{
	m_location = newLocation;
	// if tileFree(newLocation)
	return 1; // should return success/failer based on destination being free/occupied
}

sf::Vector3i Cell::GetLocation() const
{
	return m_location;
}

int Cell::GetPriority() const
{
	return m_currentPriority;
}

int Cell::GetTypeID() const
{
	return m_type.GetID();
}

const CellType& Cell::GetCellType() const
{
	return m_type;
}

int Cell::GetTeam() const
{
	return m_team;
}