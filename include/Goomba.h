#pragma once

#include "Elements.h"
#include "MovingElements.h"
#include "Enemy.h"
#include "macros.h"

class Goomba : public Enemy
{
public:
	Goomba(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Draw(sf::RenderWindow& window) override;
	~Goomba() {};

private:
};