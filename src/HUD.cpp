#include "HUD.h"
#include <iostream>
#include "Mario.h"

sf::RectangleShape HUD::m_rect;


HUD::HUD(sf::View& view)
{
	if(!m_font.loadFromFile("SuperMario256.ttf"))
		throw(std::ios_base::failure("cant load Font"));

	if (!m_HUD_text.loadFromFile("MarioHUD.jpg"))
		throw(std::ios_base::failure("cant load HUD texture"));

	m_rect.setSize(sf::Vector2f(1000, 350));
	m_rect.setTexture(&m_HUD_text);
	//m_rect.setFillColor(sf::Color::Red);
	m_rect.setOutlineThickness(5);
	m_rect.setOutlineColor(sf::Color::White);
	m_rect.setPosition(sf::Vector2f(0, 650));

	m_text.setFont(m_font);
	m_text.setCharacterSize(40);
	m_text.setFillColor(sf::Color::White);

	if (!m_exit_text.loadFromFile("ExitButton.png"))
		throw(std::ios_base::failure("cant load HUD texture"));

	m_exit.setSize(sf::Vector2f(300, 125));
	m_exit.setTexture(&m_exit_text);
	m_exit.setPosition(sf::Vector2f(600, 670));
}

void HUD::draw(sf::RenderWindow& window, sf::Event& event, int level, int score, int life)
{

	window.draw(m_rect);

	m_text.setPosition(150, 700);
	m_ss.str(std::string());
	m_ss << "Level: " << level;
	m_text.setString(m_ss.str());
	window.draw(m_text);

	m_text.setPosition(150, 800);
	m_ss.str(std::string());
	m_ss << "Score: " << score;
	m_text.setString(m_ss.str());
	window.draw(m_text);

	m_text.setPosition(150, 900);
	m_ss.str(std::string());
	m_ss << "Lifes: " << life;
	m_text.setString(m_ss.str());
	window.draw(m_text);

	//window.draw(m_exit);

	/*sf::Vector2i mouse = sf::Mouse::getPosition(window);

	sf::Vector2f mouse_world = window.mapPixelToCoords(mouse);

	if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (m_exit.getGlobalBounds().contains(mouse_world))
			{
				window.close();
			}
		}
	}*/

}