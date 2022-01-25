#pragma once

#include "Elements.h"
#include "MovingElements.h"
#include "macros.h"
#include <SFML/Audio.hpp>


class Enemy : public MovingElements
{
public:
	Enemy(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Move(Board&, sf::RenderWindow&) override;
	virtual void changeDirection(const Direction prevDir) override;
	void handleRightAndLeft();
	void isDead(Board& board);
	void resetPos();
	~Enemy() {};


protected:
	sf::Clock deathClock;
	int m_intrect_width, m_intrect_height;

};