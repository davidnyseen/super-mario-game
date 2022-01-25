#include "Enemy.h"


Enemy::Enemy(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: MovingElements(location, texture, size, intrect)
{

}

void Enemy::Move(Board& board, sf::RenderWindow& window)
{
	m_direction = { 0, 0 };
	m_velocity = fmin(float(m_movementClock.restart().asSeconds() * (m_speed - 100.f)), 5.0f);

	//static float keyTime2 = 0;
	keyTime += 3.0f;

	switch (enemyDir)
	{
	case Right:
		m_direction = { m_velocity , 0 };
		break;
	case Left:
		m_direction = { -m_velocity , 0 };
		break;
	case Up:
		m_direction = { 0 , -m_velocity };
		break;
	case Down:
		m_direction = { 0 , m_velocity };
		break;
	default:
		break;
	}


	m_rectangle.move(m_direction);
	checkCollision(*this, m_velocity, board);

	handleRightAndLeft();

}

void Enemy::changeDirection(const Direction prevDir)
{
	if (prevDir == enemyDir)
	{
		switch (enemyDir)
		{
		case Right:
			enemyDir = Left;
			keyTime = 1000;
			m_intrect.left = 0;
			break;
		case Left:
			enemyDir = Right;
			keyTime = 1000;
			m_intrect.left = 0;
			break;

		default:
			break;
		}
	}
}

void Enemy::handleRightAndLeft()
{
	if (enemyDir == Right && keyTime > 500 && m_mode != Smash)
	{
		m_intrect.top = 0;
		m_intrect.left += m_intrect_width;
		m_rectangle.setTextureRect(m_intrect);
		if (m_intrect.left >= 450)
			m_intrect.left = 0;
		keyTime = 0;
		m_intrect.top = 0;
	}

	if (enemyDir == Left && keyTime > 500 && m_mode != Smash)
	{
		m_intrect.top = m_intrect_height;
		m_intrect.left += m_intrect_width;
		m_rectangle.setTextureRect(m_intrect);
		if (m_intrect.left >= 450)
			m_intrect.left = 0;
		keyTime = 0;
		m_intrect.top = m_intrect_height;
	}
}

void Enemy::isDead(Board& board)
{
	if (m_mode != Dead)
	{
		updateMode(Dead);
		enemyDir = Down;
	}
}

void Enemy::resetPos()
{
	MovingElements::resetPos();

	enemyDir = Right;
	m_speed = 260;
	m_intrect.top = 0;
	m_intrect.left = 0;
	m_rectangle.setTextureRect(m_intrect);
}