#ifndef __PLAYERANIMATION_H__
#define __PLAYERANIMATION_H__

//\===========================================================================================================================================
//\ Filename: PlayerStatistics.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : A animation class that is taliored to the player animations
//\===========================================================================================================================================
#include "Animation.h"
#include "../PlayerStatistics.h"

class PlayerAnimation :
	public Animation
{
public:
	//Constructor
	PlayerAnimation();

	//Decontructor
	~PlayerAnimation();

	//Grabs the players sprite vectors
	void SetSprites(std::vector<int> a_viMovementSprites,
		std::vector<int> a_viDeadSprites);

	//virtual function to update the sprites
	virtual void UpdateSprites() = 0;
	
	//Returns the sprite ID
	int UpdateSpriteID();

	//Returns the aliveanimation frame
	int AliveAnimation();

	//Returns teh dead animation frame
	int DeadAnimation();

	//Gets the player stats and saves them ere
	void SetPlayerStatistics(PlayerStatistics* a_pPlayerStatistics);

protected:
	//Protected vectors and variables so that the player class can access them
	std::vector<int> viMovementSprites;
	std::vector<int> viDeadSprites;
	std::vector<int> viCurrentSprites;
	PlayerStatistics* pStats;
};

#endif // __PLAYERANIMATION_H__