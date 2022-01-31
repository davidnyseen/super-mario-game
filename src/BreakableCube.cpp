#include "BreakableCube.h"

BreakableCube::BreakableCube(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Cube(location, texture, size, intrect)
{
	m_intrect.top = 0;
	m_intrect.left = 180;
	m_rectangle.setTextureRect(m_intrect);

}

void BreakableCube::isHit()
{
	m_hit++;
}

bool BreakableCube::isDestroyed()
{
	return(m_hit == 2 ? true : false);
}

void BreakableCube::setTexture(sf::Texture& text)
{
	//m_texture = text;
	m_intrect.top = 180;
	m_intrect.left = 0;

	m_rectangle.setTextureRect(m_intrect);
}