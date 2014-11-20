#include "Game.h"
#include <iostream>
using namespace std;

Game::Game()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	m_mainWindow.create(sf::VideoMode(m_windowSize, m_windowSize, 32), "Game!", sf::Style::Default, settings);

	m_Level = new Level(m_windowSize);		
	m_gameState = SettingUp;

	while (m_gameState != Playing)
	{
		Setup();
	}
	//m_debug.Initialize();

	while (m_gameState != Exiting)
	{	
		GameLoop();
	}

	m_mainWindow.close();
}

void Game::Setup()
{
	sf::Event event;

	int frames;
	m_maxFrames = 5;
	m_time = m_gameClock.restart().asSeconds();

	m_remainingTime += m_time;
	frames = 0;

	while ((m_remainingTime > m_minTimestep) && (frames < m_maxFrames))
	{

	/*	if (m_Level->Setup())
		{
			m_gameState = Playing;
		};*/

		while (m_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_gameState = Exiting;
			}
		}
		m_setupUI.Update(m_remainingTime);
		Draw();
		m_remainingTime -= m_minTimestep;
		frames++;
	}
}

void Game::GameLoop()
{
	sf::Event event;

	int frames;
	m_maxFrames = 5;
	m_time = m_gameClock.restart().asSeconds();

	m_remainingTime += m_time;
	frames = 0;

	while ((m_remainingTime > m_minTimestep) && (frames < m_maxFrames))
	{

		Step();

		while (m_mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_gameState = Exiting;
			}
		}

		Draw();
		m_remainingTime -= m_minTimestep;
		frames++;
	}
}

void Game::Step()
{
	const Cell nextCell = m_Level->GetNextCell();
	const vector<int> nextCellNeighbors = m_Level->GetNeighborsByTeam(nextCell);
	m_Level->Update(Engine::GetInstance().PerformMove(nextCell, nextCellNeighbors));
}

void Game::Draw()
{
	m_mainWindow.clear(sf::Color::White);
	m_Level->Draw(m_mainWindow);
	m_setupUI.Draw(m_mainWindow);
	m_mainWindow.display();
}

Game::~Game()
{
	delete m_Level;
}

sf::Clock Game::m_gameClock;