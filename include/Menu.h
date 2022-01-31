#pragma once
#include "Board.h"
#include <Windows.h>
#include <cstdlib>

class Board;

class Menu
{
public:
	Menu(int, int);
	void draw(sf::RenderWindow& window);
	bool options(sf::Event& event, sf::RenderWindow& window);
	void end(sf::RenderWindow& window);
	void lose(sf::RenderWindow& window);
	~Menu() {};


private:
	int m_width, m_height;
	sf::Font font;
	sf::Text m_scoreText;
	std::stringstream m_ss;
	sf::Texture m_menuTexture, m_playTexture, m_exitTexture, m_helpTexture, m_winTexture, m_endTexture, m_loseTexture;
	sf::RectangleShape mainMenu;
	sf::RectangleShape playButton;
	sf::RectangleShape exitButton;
	sf::RectangleShape helpButton;
	sf::RectangleShape rulesScreen;
	sf::RectangleShape endRules;
	sf::RectangleShape winScreen;
	sf::RectangleShape endScreen;
	sf::RectangleShape loseScreen;
	sf::Music menuMusic;


};