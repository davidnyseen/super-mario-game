#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"
#include "Cube.h"

class NotBreakableCube : public Cube
{
public:
	NotBreakableCube(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	~NotBreakableCube() {};

private:

};