#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"

class DoorBorder : public StaticsElements
{
public:
	DoorBorder(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~DoorBorder() {};

private:



};