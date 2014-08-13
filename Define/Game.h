#ifndef GAME_H
#define GAME_H

#include "Level.h"

class Game
{
public:
	bool Start();
	bool Destroy();
private:
	enum GameState { Uninitialized, Playing, ShowingMenu, Exiting };
	int m_windowSize = 800;
	Level *m_Level;
	GameState m_gameState = Uninitialized;
	sf::RenderWindow m_mainWindow;
	void GameLoop();

	//Debug m_debug;
	//static sf::Clock m_gameClock;
	//const float m_minTimestep = sf::seconds(1.f / 60.f).asSeconds();
	//int m_maxFrames = 5;
};

#endif