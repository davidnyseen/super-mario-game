#include "Mario.h"

#include "Board.h"


Mario::Mario(sf::Vector2f& location, sf::Texture& texture, int size, const sf::View& view, sf::IntRect& intrect)
	: MovingElements(location,texture, size, intrect), m_view(view)
{
	m_mode = OnGround;
	locView = m_view.getCenter();
	m_intrect.top = 0;
	m_intrect.left = 0;
	m_rectangle.setSize(sf::Vector2f(60, size));
	m_rectangle.setTextureRect(m_intrect);
}

void Mario::Draw(sf::RenderWindow& window)
{
	window.setView(m_view);
	window.draw(m_rectangle);
}

void Mario::Move(Board& board, sf::RenderWindow& window)
{
	m_direction = { 0,0 };
	m_velocity = fmin(float(m_movementClock.restart().asSeconds() * m_speed), 5.0f);

	keyTime += m_velocity;

	sf::Event event;

	handleMove(window, event);

	handleMode();

	m_rectangle.move(m_direction);
	m_view.move(m_direction);
	checkCollision(*this, m_velocity, board);

	if (m_direction.y > 0)  // mario should be going down
		m_mode = Falling;

	handleJump();//Handle jump anim

	handleRightMove();//Handle right anim

	handleLeftMove();//Handle left anim

	handleNoMove();//Handle stopmove anim

}

void Mario::handleMove(sf::RenderWindow& window, sf::Event& event)
{
	while (window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			handlePressedKey(event);
			break;

		case sf::Event::KeyReleased:
			handleReleasedKey(event);
			break;

		case sf::Event::Closed:
			exit(1);
			break;
		}
	}
}

void Mario::handlePressedKey(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		setRight();
		break;
	case sf::Keyboard::Left:
		setLeft();
		break;
	case sf::Keyboard::Space:  // jump
		setJump();
		break;
	case sf::Keyboard::Up:
		setJump();
		break;
	default:
		break;
	}
}

void Mario::setRight()
{
	if (!m_walkRight)
	{
		m_walkRight = true;
		m_turnRight = true;
		keyTime = 50;
	}
}

void Mario::setLeft()
{
	if (!m_walkLeft)
	{
		m_walkLeft = true;
		m_turnRight = false;
		keyTime = 50;
	}
}

void Mario::setJump()
{
	if (m_mode == OnGround && !m_jump)
	{
		m_marioSound.openFromFile("jump.wav");
		m_marioSound.play();
		m_jump = true;
		m_jumpClock.restart();
	}
}

void Mario::handleReleasedKey(sf::Event& event)
{
	switch (event.key.code)
	{
	case sf::Keyboard::Right:
		if (m_walkRight)
			m_walkRight = false;
		m_intrect.top = 0;
		break;
	case sf::Keyboard::Left:
		if (m_walkLeft)
			m_walkLeft = false;
		m_intrect.top = 95;
		break;
	default:
		break;
	}
}

void Mario::handleMode()
{
	if (m_jump)  //  mario is jumping
	{
		if (m_mode != Falling && m_jumpClock.getElapsedTime().asSeconds() < 0.46)
		{
			m_direction += {0, -m_velocity};
			m_mode = Jump;
		}
		else   // mario past the highest spot
		{
			m_jump = false;
			m_mode = Falling;
		}
	}

	if (!m_jump)
		m_direction += {0, m_velocity};

	if (m_walkRight)
		m_direction += {m_velocity, 0};

	if (m_walkLeft)
		m_direction += {-m_velocity, 0};
}

void Mario::handleJump()
{
	if (m_jump)
	{
		if (m_turnRight)
		{
			m_intrect.top = 0;
			m_intrect.left = 600;
		}
		else
		{
			m_intrect.top = 95;
			m_intrect.left = 600;
		}
		m_rectangle.setTextureRect(m_intrect);
		keyTime = 0;
		m_intrect.left = 0;
	}
}

void Mario::handleRightMove()
{
	if (m_walkRight && keyTime > 20 && m_mode == OnGround)
	{
		m_intrect.top = 0;
		m_intrect.left += 60;
		m_rectangle.setTextureRect(m_intrect);
		if (m_intrect.left == 540)
			m_intrect.left = 0;
		keyTime = 0;
		m_intrect.top = 0;
	}
}

void Mario::handleLeftMove()
{
	if (m_walkLeft && keyTime > 20 && m_mode == OnGround)
	{
		m_intrect.top = 95;
		m_intrect.left += 60;
		m_rectangle.setTextureRect(m_intrect);
		if (m_intrect.left == 540)
			m_intrect.left = 0;
		keyTime = 0;
		m_intrect.top = 95;
	}
}

void Mario::handleNoMove()
{
	if (m_direction.x == 0 && m_direction.y == 0)
	{
		//m_intrect.top = 0;
		m_intrect.left = 0;
		m_rectangle.setTextureRect(m_intrect);
	}
}

void Mario::changeDirection(const Direction previousDir)
{
	switch (previousDir)
	{
	case Right:
		m_rectangle.move({ -m_velocity, 0 });
		m_view.move({ -m_velocity, 0 });
		m_direction += {-m_velocity, 0};
		break;
	case Left:
		m_rectangle.move({ m_velocity, 0 });
		m_view.move({ m_velocity, 0 });
		m_direction += {  m_velocity, 0 };
		break;
	case Up:    // if the collition with static object accured on the way up
		m_mode = Falling;
		m_rectangle.move({ 0, m_velocity });
		m_view.move({ 0, m_velocity });
		m_direction += { 0, m_velocity };
		break;
	case Down:
		m_rectangle.move({ 0, -m_velocity });
		m_view.move({ 0, -m_velocity });
		m_direction += { 0, -m_velocity };
		break;
	default:
		break;
	}
}

sf::View Mario::getView() const
{
	return m_view;
}

void Mario::resetPos()
{
	MovingElements::resetPos();
	m_jumpClock.restart();
	m_mode = OnGround;
	m_turnRight = true;
	m_view.setCenter(locView);
	m_jump = m_walkRight = m_walkLeft = false;
}