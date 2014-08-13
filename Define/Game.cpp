#include "Game.h"

Game::Game()
{
	m_mainWindow.create(sf::VideoMode(m_windowSize, m_windowSize, 32), "Game!");
	//GameLoop();

	m_Level = new Level(m_windowSize);
	//m_gameObjectManager = new GameObjectManager();

	m_gameState = ShowingMenu;
	//m_debug.Initialize();

	while (m_gameState != Exiting)
	{
		GameLoop();
	}

	//m_gameObjectManager->Destroy();
	m_mainWindow.close();

}

void Game::GameLoop()
{
	sf::Event event;

	m_mainWindow.clear();
	m_Level->Draw(m_mainWindow);
	m_mainWindow.display();


	while (m_mainWindow.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			m_gameState = Exiting;
		}
	}

}

Game::~Game()
{
	delete m_Level;

	/*
	if (m_gameObjectManager)
	{
		delete m_gameObjectManager;

	}

	if (m_gameObjectManager)
	{
		delete m_camera;

	}
	*/
}