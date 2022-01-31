#pragma once

#include "Elements.h"
#include "macros.h"

#include <iostream>
#include <typeinfo>


class Board;

struct UnknownCollision
{
	UnknownCollision(Elements& a, Elements& b) : first(a), second(b)
	{
		std::cout << "Unkown collision of " << typeid(a).name() << " and "
			<< typeid(b).name() << std::endl;
	}
	Elements& first;
	Elements& second;
};

void manageCollision(Elements& element1, Elements& element2, Board& board, const sf::FloatRect& interRect);
Direction intersectionType(const sf::FloatRect& first, const sf::FloatRect& second, const sf::FloatRect& intersectionRect);

