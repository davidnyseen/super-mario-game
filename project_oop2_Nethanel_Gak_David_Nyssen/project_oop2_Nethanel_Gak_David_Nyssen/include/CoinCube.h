#pragma once

#include <SFML/Graphics.hpp>
#include "Elements.h"
#include "StaticsElements.h"
#include "Cube.h"

class CoinCube : public Cube
{
public:
	CoinCube(sf::Vector2f&, sf::Texture&, int, sf::IntRect& intrect);
	int getCoins() const;
	void reduceCoins();
	void setTexture();
	~CoinCube() {};

private:
	int m_coins_num;
	bool is_used = false;
};