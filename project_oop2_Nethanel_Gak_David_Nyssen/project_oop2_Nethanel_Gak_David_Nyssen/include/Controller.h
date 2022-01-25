#pragma once

#include <iostream>
#include <fstream>

#include <SFML/Graphics.hpp>

#include "macros.h"
#include "Board.h"
#include "Levels.h"
#include "Menu.h"

class Controller
{
public:
	Controller();
	void run();

private:
	sf::RenderWindow m_window;
	bool m_winner = false;
	bool m_loser = false;
};