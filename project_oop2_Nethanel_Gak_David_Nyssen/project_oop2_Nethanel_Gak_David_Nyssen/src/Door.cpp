#include "Door.h"

Door::Door(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: StaticsElements(location, texture, size, intrect)
{
	m_intrect.top = 180;
	m_intrect.left = 540;
	m_rectangle.setTextureRect(m_intrect);
}
