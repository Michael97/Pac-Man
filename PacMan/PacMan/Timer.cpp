#include "Timer.h"
#include "../Ghost.h"

Timer::Timer()
{
	bChaseMode = true;
	fChaseTime = 20.0f;
	fScatterTime = 7.0f;
	fFrightenedTime = 12.0f;
	iGhostScore = 100;
}

void Timer::update()
{
	startTimers();
}

void Timer::SetGhosts(std::vector<Ghost*> _ghosts)
{
	vpGhosts = _ghosts;
}

void Timer::SetFrightenedMode()
{
	bFrightenedMode = true;
}

void Timer::startTimers()
{
	if (!bFrightenedMode)
	{
		for each (Ghost* ghost in vpGhosts)
		{
			ghost->SetIsEaten(false);
		}
		chaseTimer();
		scatterTimer();
	}
	else
		frightenedTimer();

}

void Timer::chaseTimer()
{
	if (bChaseMode != NULL)
	{
		if (bChaseMode)
		{
			fChaseTime -= UG::GetDeltaTime();
			if (fChaseTime <= 0.f)
			{
				
				bChaseMode = false;
				bScatterMode = true;
				i++;

				if (i <= 3 && pPlayerStats->GetLevel() == 1)
					fChaseTime = 20.0f;
				else
					fChaseTime = (float)std::numeric_limits<int>::max();

				for each (Ghost* ghost in vpGhosts)
				{
					ghost->SetGhostState(SCATTER);
					ghost->flipDirection();
				}
			}
		}
	}
}

void Timer::scatterTimer()
{
	if (bScatterMode != NULL)
		if (bScatterMode)
		{
			fScatterTime -= UG::GetDeltaTime();
			if (fScatterTime <= 0.f)
			{
				bScatterMode = false;
				bChaseMode = true;

				if (i <= 3 && pPlayerStats->GetLevel() == 1)
					fScatterTime = 7.0f;
				else if (pPlayerStats->GetLevel() >= 2)
					fScatterTime = (float) (1 / 60);

				for each (Ghost* ghost in vpGhosts)
				{
					ghost->SetGhostState(CHASE);
					ghost->flipDirection();
				}
			}
		}
}

void Timer::frightenedTimer()
{
	if (bFrightenedMode != NULL)
		if (bFrightenedMode)
		{
			fFrightenedTime -= UG::GetDeltaTime();
			if (fFrightenedTime <= 0.f)
			{
				bFrightenedMode = false;
				fFrightenedTime = 12.0f;
				ResetGhostScore();

				for each (Ghost* ghost in vpGhosts)
				{
					if (bScatterMode)
						ghost->SetGhostState(SCATTER);
					if (bChaseMode)
						ghost->SetGhostState(CHASE);
				}
			}
		}
}

bool Timer::FrighenedMode()
{
	return bFrightenedMode;
}

bool Timer::ChaseMode()
{
	return bChaseMode;
}

bool Timer::ScatterMode()
{
	return bScatterMode;
}

void Timer::SetPlayerStats(PlayerStatistics * a_pPlayerStats)
{
	pPlayerStats = a_pPlayerStats;
}

void Timer::AddGhostScore()
{
	iGhostScore *= 2;
	pPlayerStats->AddScore(iGhostScore);
}

void Timer::ResetGhostScore()
{
	iGhostScore = 100;
}
