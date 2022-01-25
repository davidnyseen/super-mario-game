#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"

class Ground : public StaticsElements
{
public:
	Ground(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~Ground() {};


};