#pragma once
#include <SFML\Graphics.hpp>
#include <sstream>
//============================================================================

class Mario;

class HUD
{
public:
	HUD(sf::View&);
	void draw(sf::RenderWindow&, sf::Event&, int, int, int);
	~HUD() {};

private:
	sf::Font m_font;
	sf::Text m_text;
	sf::Texture m_HUD_text, m_exit_text;
	static sf::RectangleShape m_rect;
	sf::RectangleShape m_menu, m_exit;
	std::stringstream m_ss;

};