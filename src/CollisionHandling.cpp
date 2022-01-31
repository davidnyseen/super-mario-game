#include "CollisionHandling.h"
#include "Ground.h"
#include "Mario.h"
#include "NotBreakableCube.h"
#include "BreakableCube.h"
#include "CoinCube.h"
#include "Bullet.h"
#include "Board.h"

#include <iostream>
#include <map>
#include <string>
#include <typeinfo>
#include <typeindex>

namespace
{
	void nothing(Elements& element1, Elements& element2, Board& board, const sf::FloatRect& interRect)
	{

	}

	void marioWithSolid(Elements& mario, Elements& solid, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);

		Direction intersectDir = intersectionType(mario.getRectangle(), solid.getRectangle(), interRect);

		if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.changeDirection(intersectDir);

	}

	void marioWithGround(Elements& mario, Elements& ground, Board& board, const sf::FloatRect& interRect)
	{
		marioWithSolid(mario, ground, board, interRect);
	}

	void groundWithMario(Elements& ground, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithSolid(mario, ground, board, interRect);
	}

	void turtleWithSolid(Elements& turtle, Elements& solid, Board& board, const sf::FloatRect& interRect)
	{
		Turtle& turtleRef = static_cast<Turtle&>(turtle);

		if (turtleRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(turtle.getRectangle(), solid.getRectangle(), interRect);

		turtleRef.changeDirection(intersectDir);
	}

	void solidWithTurtle(Elements& solid, Elements& turtle, Board& board, const sf::FloatRect& interRect)
	{
		turtleWithSolid(turtle, solid, board, interRect);
	}

	void marioWithTurtle(Elements& mario, Elements& turtle, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);
		Turtle& turtleRef = static_cast<Turtle&>(turtle);

		if (turtleRef.getSmashClock().getElapsedTime().asSeconds() < 0.7)
			return;

		Direction intersectDir = intersectionType(mario.getRectangle(), turtle.getRectangle(), interRect);

		if (turtleRef.getMode() != Smash && turtleRef.getMode() != Dead && intersectDir == Down)
		{
			turtleRef.changeSpeed(500);
			turtleRef.isHit();
			turtleRef.updateMode(Smash);
		}

		if (turtleRef.getMode() == Smash)
		{
			// if it's the second jump on the turtle
			if (intersectDir == Down && turtleRef.getSmashClock().getElapsedTime().asSeconds() > 0.5)
			{
				turtleRef.changeSpeed(300);
				turtleRef.isDead(board);
				board.addTurtleScore();
			}
		}

		if (intersectDir != Down && marioRef.getMode() != Dead && turtleRef.getMode() != Dead)
		{
			marioRef.updateMode(Dead);
			turtleRef.changeSpeed(260);
			board.reduceLife();
		}
	}

	void turtleWithMario(Elements& turtle, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithTurtle(mario, turtle, board, interRect);
	}

	void marioWithGoomba(Elements& mario, Elements& goomba, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);
		Goomba& goombaRef = static_cast<Goomba&>(goomba);

		Direction intersectDir = intersectionType(mario.getRectangle(), goomba.getRectangle(), interRect);

		if (intersectDir == Down)
		{
			goombaRef.changeSpeed(700);
			goombaRef.isDead(board);
		}

		if (intersectDir != Down && marioRef.getMode() != Dead && goombaRef.getMode() != Dead)
		{
			marioRef.updateMode(Dead);
			board.reduceLife();
		}
	}

	void goombaWithMario(Elements& goomba, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithGoomba(mario, goomba, board, interRect);
	}

	void marioWithBreakableCube(Elements& mario, Elements& breakable, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);

		BreakableCube& breakableRef = static_cast<BreakableCube&>(breakable);

		if (marioRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(mario.getRectangle(), breakable.getRectangle(), interRect);

		if (intersectDir == Up)
		{
			if (marioRef.getMode() != Falling)
			{
				sf::Texture text;
				text.loadFromFile("BreakingCube.png");
				breakableRef.setTexture(text);
				breakableRef.isHit();
			}
		}
		else if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.changeDirection(intersectDir);

		if(breakableRef.isDestroyed())
			board.deleteObject(breakableRef, false);
	}

	void breakableCubeWithMario(Elements& breakable, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithBreakableCube(mario, breakable, board, interRect);
	}

	void marioWithCoinCube(Elements& mario, Elements& coinCube, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		CoinCube& coinCubeRef = static_cast<CoinCube&>(coinCube);
		Direction intersectDir = intersectionType(mario.getRectangle(), coinCube.getRectangle(), interRect);

		if (intersectDir == Up)
		{
			if (coinCubeRef.getCoins() && marioRef.getMode() != Falling)
			{
				board.popCoin(coinCube.getRectangle());
				coinCubeRef.reduceCoins();
				if(coinCubeRef.getCoins() == 0) coinCubeRef.setTexture();
			}
		}
		else if (intersectDir == Down)
			marioRef.updateMode(OnGround);

		marioRef.changeDirection(intersectDir);
	}

	void coinCubeWithMario(Elements& coinCube, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithCoinCube(mario, coinCube, board, interRect);
	}

	void marioWithBullet(Elements& mario, Elements& bullet, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead) return;

		marioRef.updateMode(Dead);

		board.reduceLife();
	}

	void bulletWithMario(Elements& bullet, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithBullet(mario, bullet, board, interRect);
	}

	void marioWithDoor(Elements& mario, Elements& door, Board& board, const sf::FloatRect& interRect)
	{
		Mario& marioRef = static_cast<Mario&>(mario);

		if (marioRef.getMode() == Dead)
			return;

		board.goToNextLevel();
	}

	void doorWithMario(Elements& door, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithDoor(mario, door, board, interRect);
	}

	void marioWithTrap(Elements& mario, Elements& trap, Board& board, const sf::FloatRect& interRect)
	{
		marioWithBullet(mario, trap, board, interRect);

		board.updateScore(-10);
	}

	void trapWithMario(Elements& trap, Elements& mario, Board& board, const sf::FloatRect& interRect)
	{
		marioWithTrap(mario, trap, board, interRect);
	}

	void goombaWithSolid(Elements& goomba, Elements& solid, Board& board, const sf::FloatRect& interRect)
	{
		Goomba& goombaRef = static_cast<Goomba&>(goomba);

		if (goombaRef.getMode() == Dead)
			return;

		Direction intersectDir = intersectionType(goomba.getRectangle(), solid.getRectangle(), interRect);

		goombaRef.changeDirection(intersectDir);
	}

	void solidWithGoomba(Elements& solid, Elements& goomba, Board& board, const sf::FloatRect& interRect)
	{
		goombaWithSolid(goomba, solid, board, interRect);
	}


	using HitFunctionPtr = void(*)(Elements&, Elements&, Board&, const sf::FloatRect&);
	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;

		//Mario with statics
		phm[Key(typeid(Mario), typeid(NotBreakableCube))] = &marioWithSolid;
		phm[Key(typeid(NotBreakableCube), typeid(Mario))] = &marioWithSolid;
		phm[Key(typeid(Mario), typeid(Ground))] = &marioWithGround;
		phm[Key(typeid(Ground), typeid(Mario))] = &groundWithMario;
		phm[Key(typeid(Mario), typeid(BreakableCube))] = &marioWithBreakableCube;
		phm[Key(typeid(BreakableCube), typeid(Mario))] = &breakableCubeWithMario;
		phm[Key(typeid(Mario), typeid(CoinCube))] = &marioWithCoinCube;
		phm[Key(typeid(CoinCube), typeid(Mario))] = &coinCubeWithMario;
		phm[Key(typeid(Mario), typeid(DoorBorder))] = &nothing;
		phm[Key(typeid(DoorBorder), typeid(Mario))] = &nothing;
		phm[Key(typeid(Mario), typeid(Door))] = &marioWithDoor;
		phm[Key(typeid(Door), typeid(Mario))] = &doorWithMario;
		phm[Key(typeid(Mario), typeid(Trap))] = &marioWithTrap;
		phm[Key(typeid(Trap), typeid(Mario))] = &trapWithMario;


		//Turtle with statics
		phm[Key(typeid(Turtle), typeid(NotBreakableCube))] = &turtleWithSolid;
		phm[Key(typeid(NotBreakableCube), typeid(Turtle))] = &turtleWithSolid;
		phm[Key(typeid(Turtle), typeid(Ground))] = &turtleWithSolid;
		phm[Key(typeid(Ground), typeid(Turtle))] = &turtleWithSolid;
		phm[Key(typeid(Turtle), typeid(BreakableCube))] = &turtleWithSolid;
		phm[Key(typeid(BreakableCube), typeid(Turtle))] = &solidWithTurtle;
		phm[Key(typeid(Turtle), typeid(CoinCube))] = &turtleWithSolid;
		phm[Key(typeid(CoinCube), typeid(Turtle))] = &solidWithTurtle;
		phm[Key(typeid(Turtle), typeid(DoorBorder))] = &turtleWithSolid;
		phm[Key(typeid(DoorBorder), typeid(Turtle))] = &solidWithTurtle;
		phm[Key(typeid(Turtle), typeid(Door))] = &turtleWithSolid;
		phm[Key(typeid(Door), typeid(Turtle))] = &solidWithTurtle;
		phm[Key(typeid(Turtle), typeid(Trap))] = &turtleWithSolid;
		phm[Key(typeid(Trap), typeid(Turtle))] = &solidWithTurtle;

		//Coin with statics
		phm[Key(typeid(Coin), typeid(Ground))] = &nothing;
		phm[Key(typeid(Ground), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(BreakableCube))] = &nothing;
		phm[Key(typeid(BreakableCube), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(NotBreakableCube))] = &nothing;
		phm[Key(typeid(NotBreakableCube), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(CoinCube))] = &nothing;
		phm[Key(typeid(CoinCube), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Trap))] = &nothing;
		phm[Key(typeid(Trap), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(DoorBorder))] = &nothing;
		phm[Key(typeid(DoorBorder), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Door))] = &nothing;
		phm[Key(typeid(Door), typeid(Coin))] = &nothing;


		//Bullet with statics
		phm[Key(typeid(Bullet), typeid(BreakableCube))] = &nothing;
		phm[Key(typeid(Bullet), typeid(NotBreakableCube))] = &nothing;
		phm[Key(typeid(Bullet), typeid(CoinCube))] = &nothing;
		phm[Key(typeid(Bullet), typeid(Ground))] = &nothing;
		phm[Key(typeid(Bullet), typeid(Trap))] = &nothing;
		phm[Key(typeid(BreakableCube), typeid(Bullet))] = &nothing;
		phm[Key(typeid(NotBreakableCube), typeid(Bullet))] = &nothing;
		phm[Key(typeid(Ground), typeid(Bullet))] = &nothing;
		phm[Key(typeid(Trap), typeid(Bullet))] = &nothing;
		phm[Key(typeid(CoinCube), typeid(Bullet))] = &nothing;


		//Goomba with statics
		phm[Key(typeid(Goomba), typeid(NotBreakableCube))] = &goombaWithSolid;
		phm[Key(typeid(NotBreakableCube), typeid(Goomba))] = &solidWithGoomba;
		phm[Key(typeid(Goomba), typeid(Ground))] = &nothing;
		phm[Key(typeid(Ground), typeid(Goomba))] = &nothing;
		phm[Key(typeid(Goomba), typeid(BreakableCube))] = &goombaWithSolid;
		phm[Key(typeid(BreakableCube), typeid(Goomba))] = &solidWithGoomba;
		phm[Key(typeid(Goomba), typeid(CoinCube))] = &goombaWithSolid;
		phm[Key(typeid(CoinCube), typeid(Goomba))] = &solidWithGoomba;
		phm[Key(typeid(Goomba), typeid(DoorBorder))] = &goombaWithSolid;
		phm[Key(typeid(DoorBorder), typeid(Goomba))] = &solidWithGoomba;
		phm[Key(typeid(Goomba), typeid(Door))] = &goombaWithSolid;
		phm[Key(typeid(Door), typeid(Goomba))] = &solidWithGoomba;
		phm[Key(typeid(Goomba), typeid(Trap))] = &goombaWithSolid;
		phm[Key(typeid(Trap), typeid(Goomba))] = &solidWithGoomba;


		//---------------------------Active collisions-----------------------------------

		//Mario active collisions
		phm[Key(typeid(Mario), typeid(Mario))] = &nothing;
		phm[Key(typeid(Mario), typeid(Turtle))] = &marioWithTurtle;
		phm[Key(typeid(Turtle), typeid(Mario))] = &turtleWithMario;
		phm[Key(typeid(Mario), typeid(Bullet))] = &marioWithBullet;
		phm[Key(typeid(Bullet), typeid(Mario))] = &bulletWithMario;
		phm[Key(typeid(Mario), typeid(Goomba))] = &marioWithGoomba;
		phm[Key(typeid(Goomba), typeid(Mario))] = &goombaWithMario;
		phm[Key(typeid(Mario), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Mario))] = &nothing;



		//Turtle active collisions
		phm[Key(typeid(Turtle), typeid(Turtle))] = &nothing;
		phm[Key(typeid(Turtle), typeid(Bullet))] = &nothing;
		phm[Key(typeid(Bullet), typeid(Turtle))] = &nothing;
		phm[Key(typeid(Turtle), typeid(Goomba))] = &nothing;
		phm[Key(typeid(Goomba), typeid(Turtle))] = &nothing;
		phm[Key(typeid(Turtle), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Turtle))] = &nothing;

		//Goomba active collisions
		phm[Key(typeid(Goomba), typeid(Goomba))] = &nothing;
		phm[Key(typeid(Goomba), typeid(Bullet))] = &nothing;
		phm[Key(typeid(Bullet), typeid(Goomba))] = &nothing;
		phm[Key(typeid(Goomba), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Goomba))] = &nothing;

		//Bullet active collisions
		phm[Key(typeid(Bullet), typeid(Bullet))] = &nothing;
		phm[Key(typeid(Bullet), typeid(Coin))] = &nothing;
		phm[Key(typeid(Coin), typeid(Bullet))] = &nothing;


		//Coin active collisions
		phm[Key(typeid(Coin), typeid(Coin))] = &nothing;


		return phm;
	}

	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}
}

void manageCollision(Elements& element1, Elements& element2, Board& board, const sf::FloatRect& interRect)
{
	auto phf = lookup(typeid(element1), typeid(element2)); //FROM MULTIMETHOD CLASS
	if (!phf)
	{
		throw UnknownCollision(element1, element2);
	}
	phf(element1, element2, board, interRect);
}

Direction intersectionType(const sf::FloatRect& first, const sf::FloatRect& second, const sf::FloatRect& intersectionRect)
{
	if (intersectionRect.width + 2 > intersectionRect.height)
		return (first.top < second.top ? Down : Up);

	return (first.left < second.left ? Right : Left);
}