#pragma once

#include <iostream>
#include <typeinfo>
#include <fstream>
#include <memory>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "macros.h"
#include "Levels.h"
#include "Elements.h"
#include "StaticsElements.h"
#include "Ground.h"
#include "Cube.h"
#include "BreakableCube.h"
#include "NotBreakableCube.h"
#include "CoinCube.h"
#include "MovingElements.h"
#include "Mario.h"
#include "Turtle.h"
#include "CoinCube.h"
#include "Coin.h"
#include "Bullet.h"
#include "CollisionHandling.h"
#include "HUD.H"
#include "Door.h"
#include "DoorBorder.h"
#include "Trap.h"
#include "Goomba.h"
#include "Menu.h"


class Board
{
public:
	Board(sf::RenderWindow&, sf::Event&, bool&, bool&);
	void loadBackgrounds();
	void startPlaying(sf::RenderWindow&);
	void runLevel(sf::RenderWindow&, int);
	void manage(sf::RenderWindow& window, HUD&);
	void handleStart(sf::RenderWindow&);
	void createLevelObjects(std::ifstream&,sf::RenderWindow&);
	void loadTileSheets(sf::Texture&, sf::Texture&, sf::Texture&, sf::Texture&);
	void create(std::ifstream&, std::string&);
	void createMario();
	void createTurtle();
	void createGoomba();
	void DrawObjects(sf::RenderWindow&);
	void MoveObjects(sf::RenderWindow& window);
	void deleteObject(const Elements& object, bool isActive);
	void popCoin(const sf::FloatRect& coinTileRect);
	void reduceLife();
	void goToNextLevel();
	void addTurtleScore();
	void updateScore(int diff);
	void loadWinElements();
	void playWin(sf::RenderWindow&);
	static int getScore();
	~Board() {};

private:
	friend class MovingElements;
	sf::RenderWindow& m_window;
	sf::RectangleShape m_background[3];
	sf::RectangleShape m_background2;
	int m_tile_size = 64;
	int m_size;
	int m_level_num = 1, m_life = 3;
	static int m_score;
	bool should_end = false;
	std::vector<std::unique_ptr<StaticsElements>> m_statics;
	std::vector<std::unique_ptr<MovingElements>> m_movings;
	sf::View gameView, HUDView;
	sf::Texture tileSheet;
	sf::Texture marioSheet;
	sf::Texture turtleSheet;
	sf::Texture goombaSheet;
	bool m_goToNextLevel = false;
	sf::Event m_event;
	int m_turtle_killed = 0;
	static sf::Vector2f loc;
	bool& m_winner;
	bool& m_loser;
	sf::Music winMus, gameMus;
	sf::Texture winTexture;
	sf::RectangleShape winnerScreen;
};