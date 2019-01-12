#ifndef __PACMANCONTROLLER_H__
#define __PACMANCONTROLLER_H__

//\===========================================================================================================================================
//\ Filename: PacManController.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class designed for pacman and his unique functions
//\===========================================================================================================================================
#include "../Vector2.h"
#include "../CoordTranslator.h"
#include "../Entity.h"
#include "../Timer.h"
#include "../PlayerAnimation.h"
#include "../Tile.h"
#include "../PlayerStatistics.h"

//Forward Declaration
class Grid;
class PacMan : public PlayerAnimation, public Entity
{
public:
	//Constructor
	PacMan();

	//update function that updates pacman
	void update(int _spriteID);

	//updates the sprite to be rendered
	void UpdateSprites();

	//grabs and sets tthe timer as a pointer
	void SetTimer(Timer* a_fTimer);



private:
	//function that checks for collisions based on grid location
	void checkForCollision();

	//unused
	void frightened();
	void flipDirection();
	void noPath();

	//Changes the sprites rotation
	void setRotation();

	//Checks to see if it can move to the next tile
	bool canMoveToTargetTile(Vector2<float> a_viTargetGridPosition);

private:
	Timer* pfTimer;
};

#endif // __PACMANCONTROLLER_H__
