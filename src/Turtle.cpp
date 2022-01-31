#include "Turtle.h"

#include "Board.h"

Turtle::Turtle(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Enemy(location, texture, size, intrect)
{
	enemyDir = Right;
	intrect.top = 0;
	intrect.left = 0;
	m_rectangle.setSize(sf::Vector2f(45, 35));
	m_intrect_width = 46;
	m_intrect_height = 70;
	m_rectangle.setPosition(sf::Vector2f(location.x, location.y + 29));
	m_start_loc = m_rectangle.getPosition();
	m_rectangle.setTextureRect(m_intrect);
}

void Turtle::Draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
}

sf::Clock Turtle::getSmashClock() const
{
	return smash_clock;
}

void Turtle::isHit()
{
	smash_clock.restart();
	m_smash = true;
	m_intrect.left = 510;
	m_intrect.top = 0;
	m_rectangle.setTextureRect(m_intrect);
}

bool Turtle::getSmash() const
{
	return m_smash;
}