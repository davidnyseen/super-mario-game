#pragma once

#include "Elements.h"

class StaticsElements : public Elements
{
public:
	StaticsElements(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual ~StaticsElements() {};


protected:

};