#include "Hexagon.h"

Hexagon::Hexagon(POINT origin, double radius)
{
	m_origin = origin;
	m_radius = radius;
	m_state = Ally;
	int angle = 0;

	for (unsigned inti = 0; i < 6; ++i)
	{
		m_vertices[i] = { m_origin.x + (m_radius* cos(toRadians(angle))), m_origin.y + (m_radius * sin(toRadians(angle)))};
		angle += 60;
	}
}

const POINT Hexagon::GetOrigin() const
{
	return m_origin;
}

const Hexagon::HexagonState Hexagon::GetState() const
{
	return m_state;
}

void Hexagon::Draw(HDC& hdc) const
{
	Polygon(hdc, m_vertices, 6);

/*	std::wstring mywstring(m_labels[m_state]);
	std::wstring myString = std::to_wstring(m_origin.x) + L", " + std::to_wstring(m_origin.y);
	std::wstring concatted_stdstr =myString;
	LPCWSTR text  = concatted_stdstr.c_str();
	HFONT hFont, hTmp;
	hFont = CreateFont(12, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, 0, 0, 2, 0, L"SYSTEM_FIXED_FONT");
	hTmp = (HFONT)SelectObject(hdc, hFont);*/
	LPCWSTR text = m_labels[m_state] ;
	TextOut(hdc, m_origin.x - 5, m_origin.y - 8, text, 1);
}

void Hexagon::CycleState()
{
	m_state = HexagonState((m_state + 1) % 3);
}

const LPCWSTR Hexagon::m_labels[3] = { L"", L"A", L"E" };