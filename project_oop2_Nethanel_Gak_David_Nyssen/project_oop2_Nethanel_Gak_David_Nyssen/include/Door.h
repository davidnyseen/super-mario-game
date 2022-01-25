#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"

class Door : public StaticsElements
{
public:
	Door(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~Door() {};

private:



};