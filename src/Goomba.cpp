#include "Goomba.h"

#include "Board.h"

Goomba::Goomba(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Enemy(location, texture, size, intrect)
{
	enemyDir = Right;
	intrect.top = 0;
	intrect.left = 0;
	m_rectangle.setSize(sf::Vector2f(55, 45));
	m_intrect_width = 58;
	m_intrect_height = 60;
	m_rectangle.setPosition(sf::Vector2f(location.x, location.y + 19));
	m_start_loc = m_rectangle.getPosition();
	m_rectangle.setTextureRect(m_intrect);
}

void Goomba::Draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
}