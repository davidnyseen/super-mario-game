#include "MovingElements.h"
#include "Board.h"


MovingElements::MovingElements(sf::Vector2f& location, sf::Texture& texture, int size, sf::IntRect& intrect)
	: Elements(location, texture, size, intrect)
{

}

float MovingElements::getVelocity() const
{
	return m_velocity;
}

void MovingElements::checkCollision(Elements& element, const float velocity, Board& board)
{
	sf::FloatRect movingRect = element.getRectangle();
	sf::FloatRect intersectionRect;

	for (unsigned int i = 0; i < board.m_statics.size(); i++)
	{
		if (movingRect.intersects(board.m_statics[i]->getRectangle(), intersectionRect))
		{
			// to avoid jiterring 
			switch (intersectionType(movingRect, board.m_statics[i]->getRectangle(), intersectionRect))
			{
			case Up:
				movingRect.top += velocity;
				break;
			case Down:
				movingRect.top -= velocity;
				break;
			case Right:
				movingRect.left -= velocity;
				break;
			case Left:
				movingRect.left += velocity;
				break;
			}
			manageCollision(element, *board.m_statics[i], board, intersectionRect);
		}
	}

	for (unsigned int i = 0; i < board.m_movings.size(); ++i)  // collision of active with active
	{
		if (movingRect.intersects(board.m_movings[i]->getRectangle(), intersectionRect))
			manageCollision(element, *board.m_movings[i], board, intersectionRect);
	}
}

Mode MovingElements::getMode() const
{
	return m_mode;
}

void MovingElements::changeSpeed(const float speed)
{
	m_speed = speed;
}

void MovingElements::updateMode(const Mode newMode)  // update the mode - falling, on ground, etc.
{
	m_mode = newMode;
}

void MovingElements::resetPos()
{
	m_rectangle.setPosition(m_start_loc);
	m_movementClock.restart();
	keyTime = 0;
}

sf::Vector2f MovingElements::getDirection() const
{
	return m_direction;
}