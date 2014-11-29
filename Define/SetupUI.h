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

	int ProcessEvent(sf::Event);

	int GetCellTypeSelection();
	int GetComboBoxSelection();
	void ResetUIStates();
	bool WasUIClicked();
	void CheckMouseClick();
	void OnComboSelect();
	void OnCellTypeSelect();
	void CompleteSetup();
	~SetupUI();
	
private:
	sf::IntRect m_PlayerInfo;
	string m_PlayerInfoTxt;
	
	bool m_comboBoxClicked;
	bool m_cellTypeSelected;

	vector<CellType*> m_availableCellTypes;
	int m_selectedCellType;
	static int clicks;
	sfg::SFGUI sfgui;
	sfg::Label::Ptr m_label;
	sfg::Desktop m_desktop;
	sfg::Window::Ptr m_window;
	sfg::ComboBox::Ptr m_cellTypeComboBox;
};

