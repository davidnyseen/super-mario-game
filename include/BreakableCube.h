#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"
#include "Cube.h"

class BreakableCube : public Cube
{
public:
	BreakableCube(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	void isHit();
	bool isDestroyed();
	void setTexture(sf::Texture&);
	~BreakableCube() {};

private:
	int m_hit = 0;

};