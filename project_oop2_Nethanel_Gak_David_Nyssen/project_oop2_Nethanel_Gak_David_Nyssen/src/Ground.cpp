#include "Ground.h"

Ground::Ground(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: StaticsElements(location, texture /*loadTexture(texture)*/, size, intrect)
{
	m_intrect.top = 0;
	m_intrect.left = 0;
	m_rectangle.setTextureRect(m_intrect);
}
