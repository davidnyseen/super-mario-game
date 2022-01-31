#pragma once

#include <SFML/Graphics.hpp>
#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t


class Elements
{
public:
	Elements();
	Elements(sf::Vector2f&, sf::Texture&, int size, sf::IntRect&);
	virtual void Draw(sf::RenderWindow&);
	sf::FloatRect getRectangle();
	sf::Vector2f getPos() const;
	sf::IntRect getIntRect() const;
	virtual ~Elements() {};


protected:
	sf::Vector2f m_start_loc;
	sf::Texture m_texture;
	sf::RectangleShape m_rectangle;
	int m_size;
	bool is_visible = true;
	sf::IntRect m_intrect;
};