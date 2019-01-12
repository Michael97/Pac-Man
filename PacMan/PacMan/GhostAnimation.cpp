#include "GhostAnimation.h"

GhostAnimation::GhostAnimation()
{
}


GhostAnimation::~GhostAnimation()
{
}

//Grabs and sets the sprits
void GhostAnimation::SetSprites(std::vector<int> a_viUpMovementSprites, std::vector<int> a_viDownMovementSprites, std::vector<int> a_viRightMovementSprites, std::vector<int> a_viLeftMovementSprites, std::vector<int> a_viFrightenedSprites, std::vector<int> a_viDeadSprites)
{
	viUpMovementSprites = a_viUpMovementSprites;
	viDownMovementSprites = a_viDownMovementSprites;
	viRightMovementSprites = a_viRightMovementSprites;
	viLeftMovementSprites = a_viLeftMovementSprites;
	viFrightenedSprites = a_viFrightenedSprites;
	viDeadSprites = a_viDeadSprites;
}

//updates the currentspites based on time.
int GhostAnimation::UpdateSpriteID()
{
	fDeltaTime -= UG::GetDeltaTime();
	//if the timer is done
	if (fDeltaTime <= 0.0f)
	{
		//run for each int in vector
		for (int i = 0; i < viCurrentSprites.size(); i++)
		{
			//if the ints are the same, we found it!
			if (currentSpriteID == viCurrentSprites[i])
			{
				//reset timer
				fDeltaTime = 0.1f;

				//if the next sprite is greater then the size of the vector, reset the currentspriteID
				//to the first sprite in the vector
				if (i + 1 >= viCurrentSprites.size())
				{
					currentSpriteID = viCurrentSprites[0];
					return currentSpriteID;
				}
				//else its ok to get the next sprite from the vector!
				currentSpriteID = viCurrentSprites[i + 1];
				return currentSpriteID;
			}
		}
	}

	return currentSpriteID;
}