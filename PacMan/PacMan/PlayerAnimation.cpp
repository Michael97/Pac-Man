#include "PlayerAnimation.h"

PlayerAnimation::PlayerAnimation()
{
}


PlayerAnimation::~PlayerAnimation()
{
}


//This function does stuff
void PlayerAnimation::SetSprites(std::vector<int> a_viMovementSprites, std::vector<int> a_viDeadSprites)
{
	viMovementSprites = a_viMovementSprites;
	viDeadSprites = a_viDeadSprites;
}

int PlayerAnimation::UpdateSpriteID()
{
	if (viCurrentSprites == viMovementSprites)
		return AliveAnimation();
	else
		return DeadAnimation();
}

int PlayerAnimation::AliveAnimation()
{
	fDeltaTime -= UG::GetDeltaTime();

	if (fDeltaTime <= 0.0f)
	{
		for (int i = 0; i < viCurrentSprites.size(); i++)
		{
			if (currentSpriteID == viCurrentSprites[i])
			{
				fDeltaTime = 0.05f;

				if (i + 1 >= viCurrentSprites.size())
				{
					std::reverse(viMovementSprites.begin(), viMovementSprites.end());
					currentSpriteID = viCurrentSprites[1];
					return currentSpriteID;
				}

				currentSpriteID = viCurrentSprites[i + 1];
				return currentSpriteID;
			}
		}
	}

	return currentSpriteID;
}

int PlayerAnimation::DeadAnimation()
{

	fDeltaTime -= UG::GetDeltaTime();

	if (fDeltaTime <= 0.0f)
	{
		for (int i = 0; i < viCurrentSprites.size(); i++)
		{
			if (currentSpriteID == viCurrentSprites[i])
			{
				fDeltaTime = 0.1f;

				if (i + 1 >= viCurrentSprites.size())
				{
					pStats->SubtractLives(1);
					return currentSpriteID;
				}

				currentSpriteID = viCurrentSprites[i + 1];
				return currentSpriteID;
			}
		}
	}

	return currentSpriteID;
}

void PlayerAnimation::SetPlayerStatistics(PlayerStatistics * a_pPlayerStatistics)
{
	pStats = a_pPlayerStatistics;
}


