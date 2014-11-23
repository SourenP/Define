#pragma once

#include <string>
#include <vector>

#include "CellType.h"
#include "SFML\Graphics.hpp"
#include "SFGUI\SFGUI.hpp"

using std::string;
using std::vector;

class SetupUI
{
public:
	SetupUI();

	void SetCellTypes(const vector<CellType*>& cellTypes);

	void Update(float seconds);
	void Draw(sf::RenderWindow& rederWindow);

	void ProcessMouseEvent();
	void CheckMouseClick();

	~SetupUI();
	
private:
	sf::IntRect m_PlayerInfo;
	string m_PlayerInfoTxt;

	vector<CellType*> m_AvailableCellTypes;
	static int clicks;
	sfg::SFGUI sfgui;
	sfg::Label::Ptr m_label;
	sfg::Desktop m_desktop;
};

