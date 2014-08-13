#ifndef GAME_H
#define GAME_H

#include "Level.h"

class Game
{
public:
	Game();
	~Game();
private:
	Game(const Game&);
	Game& operator=(const Game&);

	enum GameState { Uninitialized, Playing, ShowingMenu, Exiting };
	int m_windowSize = 800;
	Level *m_Level;
	GameState m_gameState = Uninitialized;
	sf::RenderWindow m_mainWindow;
	void GameLoop();

	const float m_minTimestep = sf::seconds(1.f / 60.f).asSeconds();
	int m_maxFrames = 5;
	float m_remainingTime;
	float m_time;
	static sf::Clock m_gameClock;
};

#endif