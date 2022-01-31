#include "Menu.h"

#include "Board.h"


Menu::Menu(int width, int height)
	: m_width(width), m_height(height)
{
	font.loadFromFile("SuperMario256.ttf");

	if(!m_menuTexture.loadFromFile("MarioMenu.png"))
		throw(std::ios_base::failure("cant load menu texture"));

	mainMenu.setTexture(&m_menuTexture);
	mainMenu.setSize(sf::Vector2f(m_width, m_height));
	mainMenu.setPosition(0, 0);

	if (!m_playTexture.loadFromFile("playButton.png"))
		throw(std::ios_base::failure("cant load play texture"));

	playButton.setTexture(&m_playTexture);
	playButton.setSize(sf::Vector2f(400, 125));
	playButton.setPosition(50, 855);

	if (!m_exitTexture.loadFromFile("ExitButton.png"))
		throw(std::ios_base::failure("cant load play texture"));

	exitButton.setTexture(&m_exitTexture);
	exitButton.setSize(sf::Vector2f(400, 125));
	exitButton.setPosition(550, 855);

	helpButton.setFillColor(sf::Color::Transparent);
	helpButton.setSize(sf::Vector2f(75, 75));
	helpButton.setPosition(375, 505);

	if (!m_helpTexture.loadFromFile("MarioRules.png"))
		throw(std::ios_base::failure("cant load play texture"));

	rulesScreen.setTexture(&m_helpTexture);
	rulesScreen.setSize(sf::Vector2f(1000, 1000));

	endRules.setSize(sf::Vector2f(150, 50));
	endRules.setTexture(&m_exitTexture);
	endRules.setPosition(sf::Vector2f(810, 50));

	if (!m_winTexture.loadFromFile("winnerScreen.png"))
		throw(std::ios_base::failure("cant load play texture"));

	winScreen.setTexture(&m_winTexture);
	winScreen.setSize(sf::Vector2f(1000, 1000));

	if (!m_endTexture.loadFromFile("endingScreen.png"))
		throw(std::ios_base::failure("cant load play texture"));

	endScreen.setTexture(&m_endTexture);
	endScreen.setSize(sf::Vector2f(1000, 1000));

	if (!m_loseTexture.loadFromFile("loseScreen.png"))
		throw(std::ios_base::failure("cant load play texture"));

	loseScreen.setTexture(&m_loseTexture);
	loseScreen.setSize(sf::Vector2f(1000, 1000));

	if (!menuMusic.openFromFile("menu.wav"))
		throw(std::ios_base::failure("cant load menu music"));

	menuMusic.setLoop(true);

	m_scoreText.setFont(font);
}

void Menu::draw(sf::RenderWindow& window)
{
	menuMusic.play();
	window.clear();
	window.draw(mainMenu);
	window.draw(playButton);
	window.draw(exitButton);
	window.draw(helpButton);
	window.display();
}

bool Menu::options(sf::Event& event, sf::RenderWindow& window)
{
	sf::Vector2i mouse = sf::Mouse::getPosition(window);

	sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (playButton.getGlobalBounds().contains(mouse_world))
			{
				menuMusic.stop();
				return true;
			}
			else if (exitButton.getGlobalBounds().contains(mouse_world))
			{
				window.close();
			}
			else if (helpButton.getGlobalBounds().contains(mouse_world))
			{
				exitButton.setSize(sf::Vector2f(0, 0));
				playButton.setSize(sf::Vector2f(0, 0));
				window.draw(rulesScreen);
				window.draw(endRules);
				window.display();

			}
			else if (endRules.getGlobalBounds().contains(mouse_world))
			{
				exitButton.setSize(sf::Vector2f(400, 125));
				playButton.setSize(sf::Vector2f(400, 125));
				draw(window);
			}
		}
	}
	return false;
}

void Menu::end(sf::RenderWindow& window)
{
	window.draw(endScreen);
	m_scoreText.setPosition(275, 600);
	m_ss.str(std::string());
	m_ss << Board::getScore();
	m_scoreText.setString(m_ss.str());
	window.draw(m_scoreText);
	window.display();
	Sleep(5000);
	draw(window);
}

void Menu::lose(sf::RenderWindow& window)
{
	window.draw(loseScreen);
	window.display();
	Sleep(5000);
	draw(window);
}