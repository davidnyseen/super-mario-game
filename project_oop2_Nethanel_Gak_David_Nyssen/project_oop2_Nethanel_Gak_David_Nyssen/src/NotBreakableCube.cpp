#include "NotBreakableCube.h"

NotBreakableCube::NotBreakableCube(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Cube(location, texture, size, intrect)
{
	m_intrect.top = 0;
	m_intrect.left = 540;
	m_rectangle.setTextureRect(m_intrect);
}

