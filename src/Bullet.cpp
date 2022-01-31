#include "Bullet.h"

#include "Board.h"

Bullet::Bullet(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Enemy(location, texture, size, intrect)
{
	enemyDir = Up;
	m_intrect.top = 360;
	m_intrect.left = 180;
	m_rectangle.setTextureRect(m_intrect);
	travelTime.restart();

	int nrand = rand() % 2;

	if (nrand == 0)
	{
		m_speed = 600;
		keyTimeLimit = 500;
	}
	else if (nrand == 1)
	{
		m_speed = 400;
		keyTimeLimit = 700;
	}
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
}

void Bullet::Move(Board& board, sf::RenderWindow& window)
{

	if (travelTime.getElapsedTime().asSeconds() > 2)
	{
		m_rectangle.setPosition(m_start_loc);
		travelTime.restart();
	}

	Enemy::Move(board, window);


	handleAnimation();

}

void Bullet::resetPos()
{
	MovingElements::resetPos();
	enemyDir = Up;
}

void Bullet::handleAnimation()
{
	if (enemyDir == Up && keyTime > keyTimeLimit)
	{
		if (!is_red)
		{
			m_intrect.top = 360;
			m_intrect.left = 360;
			is_red = true;
		}
		else
		{
			m_intrect.top = 360;
			m_intrect.left = 180;
			is_red = false;
		}
		m_rectangle.setTextureRect(m_intrect);
		keyTime = 0;
	}
}