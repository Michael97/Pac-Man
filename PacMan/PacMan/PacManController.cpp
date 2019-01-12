#include "PacManController.h"
#include "../Grid.h"

PacMan::PacMan()
{
	SetWorldPosition(Vector2<float> (-1, -1));
	SetSpeed(64);
	SetIsMoving(true);
	SetNextDirection(LEFT);
}

void PacMan::update(int _spriteID)
{
	SetSpriteID(_spriteID);
	UpdateSprites();	
	setRotation();
	UG::SetSpritePosition(GetSpriteID(), GetWorldPosition().x, WINDOW_SIZE_HEIGHT - GetWorldPosition().y);
	UG::DrawSprite(GetSpriteID());

	if (GetEntityState() == ALIVE && *GetGameState() == INGAME)
	{
		Move();
		checkForCollision();
	}
}

void PacMan::UpdateSprites()
{
	if (GetEntityState() == EntityState::DEAD)
		viCurrentSprites = viDeadSprites;

	else if (GetEntityState() == EntityState::ALIVE)
		viCurrentSprites = viMovementSprites;

	bool currentFound = false;
	for each (int animationID in viCurrentSprites)
		if (currentSpriteID == animationID)
			currentFound = true;

	if (!currentFound)
		currentSpriteID = viCurrentSprites[0];
}

void PacMan::SetTimer(Timer * a_pfTimer)
{
	pfTimer = a_pfTimer;
}

//Collision detection based on grid location
void PacMan::checkForCollision()
{

	Tile& currentTile = GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x];

	//if the current tile has a dot, then we collided with it!
	if (currentTile.hasDot)
	{
		//addscore to the player stats
		pStats->AddScore(10);
		pStats->SubtractPellets(1);

		//the tile no longer has a dot
		currentTile.hasDot = false;
		
		//stop drawing the dot
		currentTile.canDraw = false;

		//destroy the sprite
		UG::DestroySprite(currentTile.ID);
	}

	//if the current tile has a power pill, then we collided with it!
	if (currentTile.hasPowerPill)
	{
		//add score to the player stats
		pStats->AddScore(50);
		pStats->SubtractPellets(1);

		//the tile no longer has a pill
		currentTile.hasPowerPill = false;
		currentTile.canDraw = false;

		UG::DestroySprite(currentTile.ID);

		//if the level is less than 5 then the ghost gets frightened
		if (pStats->GetLevel() < 5)
			pfTimer->SetFrightenedMode();
	}
}

void PacMan::frightened()
{

}

void PacMan::flipDirection()
{

}

void PacMan::noPath()
{

}

bool PacMan::canMoveToTargetTile(Vector2<float> _targetGridPosition)
{
	bool _isBlocking = GetGrid()->mGrid[(int)_targetGridPosition.y][(int)_targetGridPosition.x].isBlocking;
	bool _isHouseTile = GetGrid()->mGrid[(int)_targetGridPosition.y][(int)_targetGridPosition.x].isHouseTile;

	if (_isHouseTile || _isBlocking)
		return false;
	else
		return true;
}

void PacMan::setRotation()
{
	switch (GetCurrentDirection())
	{
	case UP:
		UG::SetSpriteRotation(GetSpriteID(), 90.0f);
		break;
	case DOWN:
		UG::SetSpriteRotation(GetSpriteID(), -90.0f);
		break;
	case RIGHT:
		UG::SetSpriteRotation(GetSpriteID(), 0.0f);
		break;
	case LEFT:
		UG::SetSpriteRotation(GetSpriteID(), -180.0f);
		break;
	}
}
