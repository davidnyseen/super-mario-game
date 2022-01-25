#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"

class Trap : public StaticsElements
{
public:
	Trap(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~Trap() {};


};