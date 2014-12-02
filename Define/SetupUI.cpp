#include "SetupUI.h"

void SetupUI::Update(float seconds)
{
	m_window->Update(seconds);
}

void SetupUI::Draw(sf::RenderWindow& rw)
{
	sfgui.Display(rw);
}

void SetupUI::ResetUIStates()
{
	m_comboBoxClicked = false;
	m_cellTypeSelected = false;
	m_doneButtonClicked = false;
}

bool SetupUI::WasUIClicked()
{
	bool result = m_comboBoxClicked | m_cellTypeComboBox->IsPoppedUp() | m_cellTypeSelected | m_setupComplete;
	return result;
}

int SetupUI::GetComboBoxSelection()
{
	return m_cellTypeComboBox->GetSelectedItem();
}

void SetupUI::OnPlayerDone()
{
	m_doneButtonClicked = true;
	m_currPlayer++;
	if (m_currPlayer == 3)
	{
		m_setupComplete = true;
		CompleteSetup();
		return;
	}

	m_label->SetText("Current Player: " + std::to_string(m_currPlayer));
}

void SetupUI::OnComboSelect() 
{
	m_comboBoxClicked = true;
}

void SetupUI::OnCellTypeSelect()
{
	m_selectedCellType = m_cellTypeComboBox->GetSelectedItem();
	m_cellTypeSelected = true;
}

int SetupUI::GetPlayer()
{
	return m_currPlayer;
}

SetupUI::SetupUI()
{
	m_currPlayer = 1;

	m_window = sfg::Window::Create();
	m_window->SetTitle("Hello world!");

	sfg::Button::Ptr cbButton = sfg::Button::Create("Save Selection");
	cbButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&SetupUI::OnCellTypeSelect, this));

	// Create the label.
	m_label = sfg::Label::Create("Current Player: " + std::to_string(m_currPlayer));
	m_cellTypeComboBox = sfg::ComboBox::Create();
	m_cellTypeComboBox->GetSignal(sfg::ComboBox::OnSelect).Connect(std::bind(&SetupUI::OnComboSelect, this));

	auto hbox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	hbox->Pack(m_cellTypeComboBox);
	hbox->Pack(cbButton);

	sfg::Button::Ptr playerDoneButton = sfg::Button::Create("Done with Setup");
	playerDoneButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&SetupUI::OnPlayerDone, this));

	auto vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
	vbox->Pack(hbox, false);
	vbox->Pack(playerDoneButton, true);
	vbox->Pack(m_label, true);

	m_window->Add(vbox);

	//m_desktop.Add(window);
	                                   
}


SetupUI::~SetupUI()
{

}

int SetupUI::ProcessEvent(sf::Event event)
{
	m_window->HandleEvent(event);
	return 1;
}

int SetupUI::GetCellTypeSelection()
{
	if (m_cellTypeSelected == true)
		return m_selectedCellType;
	else
		return -1;
}

void SetupUI::SetCellTypes(const vector<CellType*>& cellType)
{
	m_availableCellTypes = cellType;

	for (unsigned int i = 0; i < m_availableCellTypes.size(); ++i)
	{
		m_cellTypeComboBox->AppendItem("CellType" + std::to_string(i));
	}

}


void SetupUI::CompleteSetup()
{
	m_availableCellTypes.clear();
}

bool SetupUI::SetupComplete()
{
	return m_setupComplete;
}
