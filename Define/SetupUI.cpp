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
}

bool SetupUI::WasUIClicked()
{
	bool result = m_comboBoxClicked | m_cellTypeComboBox->IsPoppedUp() | m_cellTypeSelected;
	return result;
}

int SetupUI::GetComboBoxSelection()
{
	return m_cellTypeComboBox->GetSelectedItem();
}

void SetupUI::OnComboSelect() 
{
	std::stringstream sstr;
	m_comboBoxClicked = true;
	//m_cellTypeComboBox->
	sstr << "Item " << m_cellTypeComboBox->GetSelectedItem() << " selected with text \"" << static_cast<std::string>(m_cellTypeComboBox->GetSelectedText()) << "\"";
	m_label->SetText(sstr.str());
}

void SetupUI::OnCellTypeSelect()
{
	m_selectedCellType = m_cellTypeComboBox->GetSelectedItem();
	m_cellTypeSelected = true;
}

SetupUI::SetupUI()
{
	m_window = sfg::Window::Create();
	m_window->SetTitle("Hello world!");

	sfg::Button::Ptr cbButton = sfg::Button::Create("Save Selection");
	cbButton->GetSignal(sfg::Button::OnLeftClick).Connect(std::bind(&SetupUI::OnCellTypeSelect, this));

	// Create the label.
	m_label = sfg::Label::Create(L"Please select an item!");
	m_cellTypeComboBox = sfg::ComboBox::Create();
	m_cellTypeComboBox->GetSignal(sfg::ComboBox::OnSelect).Connect(std::bind(&SetupUI::OnComboSelect, this));

	auto hbox = sfg::Box::Create(sfg::Box::Orientation::HORIZONTAL, 5);
	hbox->Pack(m_cellTypeComboBox);
	hbox->Pack(cbButton);

	auto vbox = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5);
	vbox->Pack(hbox, false);
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

int SetupUI::clicks = 0;