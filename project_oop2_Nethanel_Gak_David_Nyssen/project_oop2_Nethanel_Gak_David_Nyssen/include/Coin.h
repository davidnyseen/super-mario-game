#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "MovingElements.h"

class Coin : public MovingElements
{
public:
	Coin(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Move(Board&, sf::RenderWindow&) override;
	virtual void changeDirection(const Direction previousDir) override {};
	~Coin() {};


private:

};