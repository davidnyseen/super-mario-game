#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"

class Cube : public StaticsElements
{
public:
	Cube(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~Cube() {};

private:
	friend class CollisionHandling;
};