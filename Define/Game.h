#ifndef GAME_H
#define GAME_H

#include "Level.h"
#include "Engine.h"



class Game
{
public:
	Game();
	~Game();
private:
	Game(const Game&);
	Game& operator=(const Game&);
	
	enum GameState { Uninitialized, SettingUp, Playing, ShowingMenu, Exiting };
	GameState m_gameState = Uninitialized;
	
	sf::RenderWindow m_mainWindow;
	int m_windowSize = 800;

	void GameLoop(); //Main game loop
	void Step();
	void Draw();
	void Setup(); //Used for setting up gameboard

	const float m_minTimestep = sf::seconds(1.f/60.f).asSeconds();
	int m_maxFrames = 5;
	float m_remainingTime;
	float m_time;
	static sf::Clock m_gameClock;
	Level *m_Level;
	SetupUI m_setupUI;
};

#endif