#pragma once

#include "Elements.h"
#include "CollisionHandling.h"

class Board;

class MovingElements : public Elements
{
public:
	MovingElements(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Move(Board&, sf::RenderWindow&) = 0;
	float getVelocity() const;
	void checkCollision(Elements& element, const float velocity, Board&);
	virtual void changeDirection(const Direction previousDir) = 0;
	Mode getMode() const;
	void changeSpeed(const float speed);
	void updateMode(const Mode newMode);
	virtual void resetPos();
	sf::Vector2f getDirection() const;
	virtual ~MovingElements() {};

protected:
	friend class Mario;
	float m_speed = 260;
	float m_velocity;
	sf::Clock m_movementClock;
	sf::Vector2f m_direction;
	Mode m_mode;
	//sf::Clock m_Clock;
	sf::Clock animClock;
	Direction enemyDir;
	float keyTime = 0;


};