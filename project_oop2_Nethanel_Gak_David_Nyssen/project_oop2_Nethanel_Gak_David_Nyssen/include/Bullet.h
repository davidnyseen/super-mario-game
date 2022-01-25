#pragma once

#include "Elements.h"
#include "MovingElements.h"
#include "Enemy.h"
#include "macros.h"

#include <chrono>
#include <thread>

class Bullet : public Enemy
{
public:
	Bullet(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Move(Board&, sf::RenderWindow&) override;
	void resetPos() override;
	void handleAnimation();
	~Bullet() {};




private:
	sf::Clock travelTime;
	sf::Clock waitTime;
	bool is_red = false;
	int keyTimeLimit;
};