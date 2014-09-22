#include "Hexagon.h"

Hexagon::Hexagon(POINT origin, double radius)
{
	m_origin = origin;
	m_radius = radius;
	int angle = 0;

	for (int i = 0; i < 6; ++i)
	{
		m_vertices[i] = { m_origin.x + (m_radius* cos(toRadians(angle))), m_origin.y + (m_radius * sin(toRadians(angle)))};
		angle += 60;
	}
}

const POINT Hexagon::GetOrigin() const
{
	return m_origin;
}

void Hexagon::Draw(HDC& hdc) const
{
	Polygon(hdc, m_vertices, 6);
}