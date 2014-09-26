#include "Hexagon.h"

Hexagon::Hexagon(POINT origin, double radius)
{
	m_origin = origin;
	m_radius = radius;
	m_state = Ally;
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
	if (m_state == Enemy)
	{
		LPCWSTR text2 = L"Hi";
	}
	LPCWSTR text = m_labels[m_state];
	TextOut(hdc, m_origin.x - 20, m_origin.y - 10, text, _tclen(text));
}

void Hexagon::CycleState()
{
	m_state = HexagonState((m_state + 1) % 3);
}

const LPCWSTR Hexagon::m_labels[3] = { L"", L"A", L"E" };