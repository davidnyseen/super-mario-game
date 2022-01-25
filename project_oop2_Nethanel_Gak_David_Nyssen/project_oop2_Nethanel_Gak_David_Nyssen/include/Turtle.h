#pragma once

#include "Elements.h"
#include "MovingElements.h"
#include "Enemy.h"
#include "macros.h"

class Turtle : public Enemy
{
public:
	Turtle(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Draw(sf::RenderWindow& window) override;
	sf::Clock getSmashClock() const;
	void isHit();
	bool getSmash() const;
	~Turtle() {};

private:
	sf::Clock smash_clock;
	bool m_smash = false;
};