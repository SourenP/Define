#pragma once

#include <string>

#include "SFML\Graphics.hpp"
#include "CellType.h"
#include "SFGUI\SFGUI.hpp"

using std::string;

class SetupUI
{
public:
	SetupUI();
	void Update(float seconds);
	void Draw(sf::RenderWindow& rederWindow);
	void ProcessMouseClick();
	void CheckMouseClick();

	~SetupUI();
	
private:
	sf::IntRect m_PlayerInfo;
	string m_PlayerInfoTxt;

	sfg::SFGUI sfgui;
	sfg::Label::Ptr m_label;
	sfg::Desktop m_desktop;
};

