#include "Board.h"

#include <iostream>
#include <map>
#include <string>

#include <SFML/Audio.hpp>

static sf::IntRect rectSource(0, 0, 180, 180);
sf::Vector2f Board::loc(0, 0);
int Board::m_score = 0;

Board::Board(sf::RenderWindow& window, sf::Event& event, bool& winner, bool& loser)
	: m_event(event), m_winner(winner), m_window(window), m_loser(loser)
{
	loadWinElements();
	gameView.setSize(sf::Vector2f(900,900));
	gameView = window.getDefaultView();
	HUDView = window.getDefaultView();
	loadBackgrounds();
	startPlaying(window);
}

void Board::loadBackgrounds()
{

	m_background2.setSize(sf::Vector2f(20000, 2020));
	m_background2.setFillColor(sf::Color::Color(102, 178, 255));
	m_background2.setPosition(sf::Vector2f(-1000, -1000));
}

void Board::startPlaying(sf::RenderWindow& window)
{
	m_score = 0;
	m_level_num = 1;
	should_end = false;

	while (m_level_num < 4)
	{
		if (m_loser)
			return;

		runLevel(window, m_level_num);
	}

	if (m_level_num == 4)
	{
		m_winner = true;
		return;
	}
	//runLevel(window, m_level_num);

}

void Board::runLevel(sf::RenderWindow& window, int levelNumber)
{

	HUD hud(HUDView);

	handleStart(window);

	gameMus.setLoop(true);
	gameMus.setVolume(50);
	gameMus.play();

	while (window.isOpen() && !m_goToNextLevel && !should_end)
	{
		manage(window, hud);
	}
	if (m_goToNextLevel)
	{
		playWin(window);
		m_level_num++;
	}
	m_goToNextLevel = false;
}

void Board::manage(sf::RenderWindow& window, HUD& hud)
{
	window.clear();
	window.draw(m_background2);
	window.setView(gameView);
	DrawObjects(window);
	MoveObjects(window);
	gameView = window.getView();
	window.setView(HUDView);
	hud.draw(window, m_event, m_level_num, m_score, m_life);
	window.display();
}

void Board::handleStart(sf::RenderWindow& window)
{
	std::ifstream levelLoader;

	switch (m_level_num)
	{
	case 1:
	{
		levelLoader.open("Level1.txt", std::ios::in);
		break;
	}
	case 2:
		levelLoader.open("Level2.txt", std::ios::in);
		break;
	case 3:
		levelLoader.open("Level3.txt", std::ios::in);
		break;
	}

	if (!levelLoader.is_open())
	{
		throw(std::ios_base::failure("cant load tmx file"));
	}

	createLevelObjects(levelLoader, window);

}

void Board::createLevelObjects(std::ifstream& levelLoader, sf::RenderWindow& window)
{
	std::string line, str;
	getline(levelLoader, line);

	std::istringstream iss;
	iss.str(line);

	int size;
	iss >> size;
	m_size = size;

	m_statics.clear();
	m_movings.clear();

	loadTileSheets(marioSheet, tileSheet, turtleSheet, goombaSheet);

	create(levelLoader, str);

}

void Board::loadTileSheets(sf::Texture& marioSheet, sf::Texture& tileSheet, sf::Texture& turtleSheet, sf::Texture& goombaSheet)
{

	if (!marioSheet.loadFromFile("MarioSheetnew4.png"))
		throw(std::ios_base::failure("cant load play texture"));

	if (!tileSheet.loadFromFile("tileSheet3.png"))
		throw(std::ios_base::failure("cant load play texture"));

	if (!turtleSheet.loadFromFile("TurtleSheetnew.png"))
		throw(std::ios_base::failure("cant load play texture"));

	if (!goombaSheet.loadFromFile("GoombaSheet.png"))
		throw(std::ios_base::failure("cant load play texture"));
}

void Board::create(std::ifstream& levelLoader, std::string& str)
{
	while (!levelLoader.eof())
	{
		getline(levelLoader, str);
		int e = levelLoader.peek();
		for (int i = 0; i <= m_size; i++)
		{
			switch (str[i])
			{
			case '0':
			{
				break;
			}
			case '1':
			{
				m_statics.push_back(std::make_unique<BreakableCube>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '2':
			{
				m_statics.push_back(std::make_unique<CoinCube>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '3':
			{
				m_statics.push_back(std::make_unique<Ground>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '4':
			{
				createMario();
				break;
			}
			case '5':
			{
				createTurtle();
				break;
			}
			case '6':
			{
				m_statics.push_back(std::make_unique<NotBreakableCube>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '7':
			{
				m_movings.push_back(std::make_unique<Bullet>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '8':
			{
				m_statics.push_back(std::make_unique<Door>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case '9':
			{
				m_statics.push_back(std::make_unique<DoorBorder>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case 'T':
			{
				m_statics.push_back(std::make_unique<Trap>(loc, tileSheet, m_tile_size, rectSource));
				break;
			}
			case 'G':
			{
				createGoomba();
				break;
			}
			default:
				break;
			}
			loc.x += m_tile_size;
		}
		loc.x = 0;
		loc.y += m_tile_size;
	}
	loc.x = 0;
	loc.y = 0;
}

void Board::createMario()
{
	sf::IntRect rectSource2(0, 0, 60, 95);
	sf::Vector2f loctemp(loc.x + m_tile_size / 2, loc.y + m_tile_size / 2);
	gameView.setCenter(loctemp);
	m_movings.push_back(std::make_unique<Mario>(loc, marioSheet, m_tile_size, gameView, rectSource2));
}

void Board::createTurtle()
{
	sf::IntRect rectSource3(0, 0, 46, 70);
	m_movings.push_back(std::make_unique<Turtle>(loc, turtleSheet, m_tile_size, rectSource3));
}

void Board::createGoomba()
{
	sf::IntRect rectSource4(0, 0, 58, 60);
	m_movings.push_back(std::make_unique<Goomba>(loc, goombaSheet, m_tile_size, rectSource4));
}

void Board::DrawObjects(sf::RenderWindow& window)
{

	std::for_each(m_statics.begin(), m_statics.end(), [&window](const auto& dr) { dr->Draw(window); });
	std::for_each(m_movings.begin(), m_movings.end(), [&window](const auto& dr) { dr->Draw(window); });

}

void Board::MoveObjects(sf::RenderWindow& window)
{
	for (size_t i = 0; i < m_movings.size(); i++)
		m_movings[i]->Move(*this, window);

	//std::for_each(m_movings.begin(), m_movings.end(), [this, &window](auto& dr) { dr->Move(*this, window); }); //PROBLEM WITH DELETE
}

void Board::deleteObject(const Elements& object, bool isActive)
{

	for (unsigned int i = 0; i < m_movings.size(); ++i)
	{
		if (m_movings[i]->getPos() == object.getPos())
		{
			m_movings.erase(m_movings.begin() + i);
			return;
		}
	}

	for (unsigned int i = 0; i < m_statics.size(); ++i)
	{
		if (m_statics[i]->getPos() == object.getPos())
		{
			m_statics.erase(m_statics.begin() + i);
			break;
		}
	}
}

void Board::popCoin(const sf::FloatRect& coinTileRect)
{
	sf::Vector2f loc;

	loc.x = coinTileRect.left;
	loc.y = coinTileRect.top;

	m_movings.push_back(std::make_unique<Coin>(loc, tileSheet, m_tile_size, rectSource));

	updateScore(10);
}

void Board::reduceLife()
{
	m_life--;

	if (m_life == 0)
	{
		m_loser = true;
		should_end = true;
		return;
	}

	for (auto& x : m_movings)
	{
		x->resetPos();
		x->updateMode(Falling);
	}

	m_score -= 5 * m_turtle_killed;

	m_turtle_killed = 0;
}

void Board::goToNextLevel()
{
	updateScore(100);
	m_goToNextLevel = true;
}

void Board::addTurtleScore()
{
	m_turtle_killed++;
	updateScore(5);
}

void Board::updateScore(int diff)
{
	if (m_score <= 10 && diff < 0 && abs(diff) > m_score)
	{
		m_score = 0;
		return;
	}
	m_score += diff;
}

void Board::loadWinElements()
{
	if (!gameMus.openFromFile("Mariomusic.wav"))
	{
		throw(std::ios_base::failure("cant load sound file"));
	}
	if (!winMus.openFromFile("winner.wav"))
	{
		throw(std::ios_base::failure("cant load sound file"));
	}
	if (!winTexture.loadFromFile("winnerScreen.png"))
	{
		throw(std::ios_base::failure("cant load winScreen file"));
	}
	winMus.setVolume(50);
}

void Board::playWin(sf::RenderWindow& window)
{
	gameMus.stop();
	winnerScreen.setSize(sf::Vector2f(1000, 1000));
	winnerScreen.setTexture(&winTexture);
	window.draw(winnerScreen);
	window.display();
	winMus.play();
	sf::sleep(sf::seconds(7));
	winMus.stop();
}

int Board::getScore()
{
	return m_score;
}