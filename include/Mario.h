#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "Elements.h"
#include "MovingElements.h"
#include "macros.h"
#include "HUD.h"

class Mario : public MovingElements
{
public:
	Mario(sf::Vector2f&, sf::Texture&, int, const sf::View&, sf::IntRect&);
	virtual void Draw(sf::RenderWindow& window) override;
	virtual void Move(Board&, sf::RenderWindow&) override;
	void handleMove(sf::RenderWindow&, sf::Event&);
	void handlePressedKey(sf::Event&);
	void setRight();
	void setLeft();
	void setJump();
	void handleReleasedKey(sf::Event&);
	void handleMode();
	void handleJump();
	void handleRightMove();
	void handleLeftMove();
	void handleNoMove();
	sf::View getView() const;
	virtual void changeDirection(const Direction previousDir) override;
	virtual void resetPos();
	~Mario() {};


private:
	friend class HUD;
	sf::View m_view;
	bool m_jump = false;
	bool m_walkRight = false;
	bool m_walkLeft = false;
	bool m_turnRight = true;
	float jumpHeight;
	sf::Music m_marioSound;
	sf::Clock m_jumpClock;
	sf::Vector2f locView;
};