#include "Coin.h"

#include "Board.h"

Coin::Coin(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: MovingElements(location, texture, size, intrect)
{
	m_intrect.top = 180;
	m_intrect.left = 360;
	m_rectangle.setTextureRect(m_intrect);
	animClock.restart();
}

void Coin::Move(Board& board, sf::RenderWindow& window)
{

	m_velocity = std::fmin(float(m_movementClock.restart().asSeconds() * m_speed), 5.f);

	m_rectangle.move((animClock.getElapsedTime().asSeconds() < 0.35 ? sf::Vector2f{ 0, -m_velocity } : sf::Vector2f{ 0, m_velocity }));

	checkCollision(*this, m_velocity, board);

	if (animClock.getElapsedTime().asSeconds() > 1)
		board.deleteObject(*this, true);
}