oop2 - PROJECT - README

Name:Nethanel Gak
Id: 1728152

Name: David Nyssen
Id: 207092511

WATCH GAMEPLAY ON YOUTUBE:

https://youtu.be/Fwq3oqkIOBg


-------------------------------------

Description:

This is the Super Mario game recreation.
In this project we used the SFML libray for the graphics and the sound.
Each level is read from a level'x'.txt (which x is the number of the level we want to load).

The game works with the keyboard. The player make mario move to the right/left with the 'right'/'left' arrows of the keyboard.
To jump, the player can press the space bar or the 'up' arrow.

The player needs to reach the end of the level without being killed.

The player has 3 lifes at the start of the game, when he dies, he loses a life, when the life's number reaches zero, it is a game over.

There are 5 differents cubes in the game who can interract with the player: the unbreakable cubes, the breakable cubes, the coin cubes, the door and the traps.
The unbreakable cube is not breakable, but can be used as a floor. Both player and enemies can't move through it.
The breakable cube is breaking after two jump bellow the cube. When the cube is broken, it disappears from the game until a new game from scratch.
The coin cube need to be punshed by the player to make a coin pop and gives the player 10 points. Each coin cube contains between 1 and 3 coins randomly.
The traps can kill the player, that is why he needs to dodge them as much as he can.
If the player gets killed by a trap, he loses 10 points, be carefull !

There are 3 diffents kind of enemies in the game: the bullets, the goombas, and the turtles.
The bullets are the simplest working enemies, their movement is from bottom to top (after a few time, it gets back to the original place and move up again).
A bullet can't be killed, the player needs to avoid them without being killed.
The goombas are one of the two kinds of killable ennemies, the player needs to jump one time on them too kill them.
The turtles are the most complex enemies. They are killable, but be aware that the player needs to jump twice on it to kill the turtle.
After the first jump, the turtle will start to move really fast, and we need to jump a second time to kill it.
A turtle kill brings a bonus of 5 points to the player.

If the player get killed, the enemies are reset and the bonus of the turtles kill is cancelled.

Little trick: if you want to dispay the game rules, press the '?' cube in the game menu. :D

-------------------------------------

Project structure:

The project work with 22 classes, here their names: Controller, Board, Elements, movingElements, staticElements, Mario, Enemy, Turtle, Goomba, Bullet, Coin, Trap, Ground, Cube, NotBreakableCube, BreakableCube, coinCube, DoorBorder, Door, Menu, HUD, CollisionHandling.

1- Controller: the controller of the game, initiates the "start game" or the menu actions.
2- Board: Manages all the display of the game if it started.
3- Elements: Base class of all the elements of the game.
4- MovingElements: Base class of all the moving elements of the game. Inherits from Elements class. This class has two pure virtual functions: move() and changeDirection() who are used in different way between mario and the other enemies.
5- StaticElements: Base class of all the statics elements of the game. Inherits from Elements class.
6- Mario: Manages the mario himself, inherits from MovingElements class.
7- Coin: Manages the coins when they appear, inherits from MovingElements class.
8- Enemy: Base class of the enemies of the game, inherits from MovingElements class.
9- Turtle: Manages the turtles, inherits from Enemy class.
10- Goomba: Manages the gommbas, inherits from Enemy class.
11- Bullet: Manages the bullets, inherits from Enemy class.
12- Ground: Manages the ground, inherits from StaticElements class.
13- Cube: Base class of the cubes who interract with the player, inherits from StaticElements class.
14- NotBreakableCube: Manages the cubes the player can't break, inherits from Cube class.
15- BreakableCube: Manages the cubes the player can break, inherits from Cube class.
16- CoinCube: Manages the cubes who make the coins appear, inherits from Cube class.
17- Trap: Manages the traps in the game, inherits from Cube class.
18- DoorBorder: Manages the ending door border, inherits from Cube class.
19- Door: Manages the ending door, inherits from Cube class.
20- Menu: Manages the menu.
21- HUD: Displays the "Head Up Display" where all the informations are appearing.
22- CollisionHandling: Manages all the collisions who can occur in the game.

------------------------------------

Data structures:
1- Vector of MovingElements.
2- Vector of StaticsElements.

------------------------------------

Specific algorithm:

No specific algorithm.

------------------------------------

Bugs:

Looks fine.

------------------------------------

