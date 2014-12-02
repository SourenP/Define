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
	int GetPlayer();

	bool SetupComplete();

	void ResetUIStates();
	bool WasUIClicked();
	void CheckMouseClick();

	void CompleteSetup();
	~SetupUI();
	
private:

	void OnComboSelect();
	void OnCellTypeSelect();
	void OnPlayerDone();

	sf::IntRect m_PlayerInfo;
	string m_PlayerInfoTxt;
	
	bool m_comboBoxClicked;
	bool m_doneButtonClicked;
	bool m_cellTypeSelected;
	bool m_setupComplete;

	vector<CellType*> m_availableCellTypes;
	int m_selectedCellType;
	int m_currPlayer;

	sfg::SFGUI sfgui;
	sfg::Label::Ptr m_label;
	sfg::Desktop m_desktop;
	sfg::Window::Ptr m_window;
	sfg::ComboBox::Ptr m_cellTypeComboBox;
};

