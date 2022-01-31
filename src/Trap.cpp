#include "Trap.h"

Trap::Trap(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: StaticsElements(location, texture /*loadTexture(texture)*/, size, intrect)
{
	m_intrect.top = 360;
	m_intrect.left = 540;
	m_rectangle.setSize(sf::Vector2f(m_size, 35));
	m_rectangle.setPosition(sf::Vector2f(location.x, location.y + 29));
	m_rectangle.setTextureRect(m_intrect);
}
