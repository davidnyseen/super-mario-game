#include "CoinCube.h"

CoinCube::CoinCube(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Cube(location, texture, size, intrect)
{
	m_coins_num = rand() % 3 + 1;
	m_intrect.top = 0;
	m_intrect.left = 360;
	m_rectangle.setTextureRect(m_intrect);
}


int CoinCube::getCoins() const
{
	return m_coins_num;
}

void CoinCube::reduceCoins()
{
	m_coins_num--;
}

void CoinCube::setTexture()
{
	if (!is_used)
	{
		m_intrect.top += 180;
		m_intrect.left -= 180;

		m_rectangle.setTextureRect(m_intrect);

		is_used = true;
	}
}