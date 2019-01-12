#ifndef __GHOST_H__
#define __GHOST_H__

//\===========================================================================================================================================
//\ Filename: Ghost.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class generalized for all ghosts
//\===========================================================================================================================================

#include "../Vector2.h"
#include "../CoordTranslator.h"
#include "../Entity.h"
#include "../AStar.h"
#include "../Timer.h"

#include <stdlib.h>  
#include <time.h>

#include "../GhostState.h"
#include "../GhostAnimation.h"
#include "../PacManController.h"

//forward declarations
class Grid;
class Ghost : public GhostAnimation, public Entity
{
public:
	//Constructor
	Ghost();
	
	//A function that updates the object
	void update(int _spriteID);

	//finds and sets pacman
	void SetPacMan(PacMan* _pacman);

	Vector2<float> POI;
	Vector2<float> PreviousPOI;

	void SetTimer(Timer* pfTimer);

	void SetGhostState(GhostState _ghostState);
	GhostState GetGhostState();

	void SetIsEaten(bool _isEaten);

	void UpdateSprites();

	void flipDirection();

	void InHouse();
	Vector2<float> HousePOI();

private:
	//virtual void CalculatePOI() = 0;
	void checkForCollision();
	virtual void Scatter() = 0;
	virtual void Chase() = 0;
	void frightened();
	
	void IsMoving();

	bool isEaten;
	void MoveToPOI();
	bool canMoveToTargetTile(Vector2<float>);
	void MoveToHouse();

	void UpdatePath();


	bool CheckForBackTracking(Step* _step);
	

	Vector2<float> previousWorldPos;
	Vector2<float> empty = Vector2<float>(0, 0);
	Vector2<float> ScatterPOI;
	Vector2<float> housePOI = Vector2<float>(14, 17);
	Vector2<float> previousPacmanGridPosition = empty;

	GhostState ghostState;

protected:
	Timer* pfTimer;
	AStar AStarPath;
	PacMan* Pacman;
};

#endif // __GHOST_H__