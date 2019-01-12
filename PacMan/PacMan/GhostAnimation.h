#ifndef __GHOSTANIMATION_H__
#define __GHOSTANIMATION_H__

//\===========================================================================================================================================
//\ Filename: Grid.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A class to create and store info for a grid.
//\===========================================================================================================================================

#include "Animation.h"
#include "../GhostState.h"

class GhostAnimation :
	public Animation
{
public:
	//Constructor
	GhostAnimation();
	//Deconstructor
	~GhostAnimation();

	//Virtual ovooid to update the sprites
	virtual void UpdateSprites() = 0;

	//Grabs and sets the vectors of sprites
	void SetSprites(std::vector<int> a_viUpMovementSprites, 
		std::vector<int> a_viDownMovementSprites,
		std::vector<int> a_viRightMovementSprites,
		std::vector<int> a_viLeftMovementSprites,
		std::vector<int> a_viFrightenedSprites, 
		std::vector<int> a_viDeadSprites );

	//Updates the current sprite ID
	int UpdateSpriteID();

protected:
	//protected vectors for the ghost class to access and use
	std::vector<int> viUpMovementSprites;
	std::vector<int> viDownMovementSprites;
	std::vector<int> viRightMovementSprites;
	std::vector<int> viLeftMovementSprites;
	std::vector<int> viFrightenedSprites;
	std::vector<int> viDeadSprites;
	std::vector<int> viCurrentSprites;
};

#endif // __GHOSTANIMATION_H__