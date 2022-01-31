#include "Elements.h"

Elements::Elements()
{

}

Elements::Elements(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: m_texture(texture), m_size(size), m_intrect(intrect)
{
	m_start_loc = location;
	m_rectangle.setPosition(m_start_loc);
	m_rectangle.setTexture(&m_texture);
	m_rectangle.setSize(sf::Vector2f(m_size, m_size));
}

void Elements::Draw(sf::RenderWindow& window)
{
	window.draw(m_rectangle);
}

sf::FloatRect Elements::getRectangle()
{
	return m_rectangle.getGlobalBounds();
}

sf::Vector2f Elements::getPos() const
{
	return m_rectangle.getPosition();
}

sf::IntRect Elements::getIntRect() const
{
	return m_intrect;
}