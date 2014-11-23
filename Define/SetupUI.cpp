#include "SetupUI.h"

void SetupUI::Update(float seconds)
{
	m_desktop.Update(seconds);
}

void SetupUI::Draw(sf::RenderWindow& rw)
{
	sfgui.Display(rw);
}

SetupUI::SetupUI()
{
	// Create the label.
	m_label = sfg::Label::Create("Hello world!");

	// Create a simple button and connect the click signal.
	auto button = sfg::Button::Create("Greet SFGUI!");

	// Create a vertical box layouter with 5 pixels spacing and add the label
	// and button to it.
	auto box = sfg::Box::Create(sfg::Box::Orientation::VERTICAL, 5.0f);
	box->Pack(m_label);
	box->Pack(button, false);

	// Create a window and add the box layouter to it. Also set the window's title.
	auto window = sfg::Window::Create();
	window->SetTitle("Hello world!");
	window->Add(box);

	m_desktop.Add(window);

}


SetupUI::~SetupUI()
{

}

void SetupUI::ProcessMouseEvent()
{
	string derp = "cl" + std::to_string(clicks);
	clicks++;
	m_label->SetText(derp);
	
	clicks++;
}

int SetupUI::clicks = 0;