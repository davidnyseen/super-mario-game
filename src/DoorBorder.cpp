#include "DoorBorder.h"

DoorBorder::DoorBorder(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: StaticsElements(location, texture, size, intrect)
{
	m_intrect.top = 360;
	m_intrect.left = 0;
	m_rectangle.setTextureRect(m_intrect);
}