#include "Ghost.h"

Ghost::Ghost()
{
}

void Ghost::update(int _spriteID)
{
	if (pfTimer->FrighenedMode())
	{
		if (viCurrentSprites != viFrightenedSprites)
			viCurrentSprites = viFrightenedSprites;
	}

	SetSpriteID(_spriteID);

	UpdateSprites();

	UG::SetSpritePosition(GetSpriteID(), GetWorldPosition().x, WINDOW_SIZE_HEIGHT - GetWorldPosition().y);
	UG::DrawSprite(GetSpriteID());


	if (Pacman->GetEntityState() == ALIVE)
	{
		if (!LockPosition())
		{
			if (previousPacmanGridPosition == empty)
				previousPacmanGridPosition = Pacman->GetGridPosition();

			Vector2<float> currentPacmanGridPosition = Pacman->GetGridPosition();

			InHouse();

			//Changing the POI if needed based off timer
			if (GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x].isNode)
			{
				if (pfTimer != nullptr)
				{
					if (pfTimer->ChaseMode())
						Chase();

					if (pfTimer->ScatterMode())
						Scatter();

					if (!isEaten)
						if (pfTimer->FrighenedMode())
							frightened();

					if (isEaten)
						Chase();
				}
			}


			if (GetEntityState() == DEAD)
				MoveToHouse();

			//Updates current POI based off location
			UpdatePath();

			Move();
			checkForCollision();
		}
	}
}

void Ghost::SetPacMan(PacMan * _pacman) 
{
	Pacman = _pacman;	
}

void Ghost::SetTimer(Timer * _timer)
{
	pfTimer = _timer;
}

void Ghost::checkForCollision()
{
	if (GetCollider().CheckCollision(Pacman->GetCollider()))
		if (pfTimer->FrighenedMode() && GetEntityState() == ALIVE && !isEaten)
		{			
			SetEntityState(DEAD);
			SetGhostState(CHASE);
			isEaten = true;
			pfTimer->AddGhostScore();
			
		}
		else if (GetEntityState() == ALIVE)
		{
			Pacman->SetEntityState(DEAD);
		}
}


void Ghost::frightened()
{
	std::vector<Step*> adjacentSteps = GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x].neighbourSteps;
	
	std::vector<Step*> possibleSteps;

	srand((unsigned int)time(NULL));

	ghostState = FRIGHTENED;

	for each (Step* step in adjacentSteps)
	{
		if (step == nullptr)
			continue;

		if (CheckForBackTracking(step))
			continue;

		possibleSteps.push_back(step);
	}

	int indexStep = rand() % possibleSteps.size();

	if (possibleSteps[indexStep]->position.x < GetGridPosition().x) //Left
		SetNextDirection(LEFT);
	else if (possibleSteps[indexStep]->position.x > GetGridPosition().x) //Right
		SetNextDirection(RIGHT);
	else if (possibleSteps[indexStep]->position.y < GetGridPosition().y) //Up
		SetNextDirection(UP);
	else if (possibleSteps[indexStep]->position.y > GetGridPosition().y) //Down
		SetNextDirection(DOWN);

}

void Ghost::IsMoving()
{

	Vector2<float> currentWorldPosition = GetWorldPosition();

	if (previousWorldPos == empty)
	{
		previousWorldPos = currentWorldPosition;
		return;
	}

	if (previousWorldPos == currentWorldPosition)
	{
		SetIsMoving(false);
	}
	else
	{
		previousWorldPos = currentWorldPosition;
		SetIsMoving(true);
	}
}

void Ghost::MoveToPOI()
{
	AStarPath = AStar(this, POI);

	Vector2<float> gridPos = GetGridPosition();

	if (AStarPath.totalPath.size() > 1)
	{
		if (AStarPath.totalPath[1].x < GetGridPosition().x) //Left
			SetNextDirection(LEFT);
		else if (AStarPath.totalPath[1].x > GetGridPosition().x) //Right
			SetNextDirection(RIGHT);
		else if (AStarPath.totalPath[1].y < GetGridPosition().y) //Up
			SetNextDirection(UP);
		else if (AStarPath.totalPath[1].y > GetGridPosition().y) //Down
			SetNextDirection(DOWN);
	}
}

bool Ghost::canMoveToTargetTile(Vector2<float> _targetGridPosition)
{
	bool _isBlocking = GetGrid()->mGrid[(int)_targetGridPosition.y][(int)_targetGridPosition.x].isBlocking;
	bool _isHouseTile = GetGrid()->mGrid[(int)_targetGridPosition.y][(int)_targetGridPosition.x].isHouseTile;
	
	//if the ghost cant move to house tiles and the tile is housetile
	if (!CanMoveHouseTiles() && _isHouseTile)
		return false;
	//else if the tile is blocking
	if (_isBlocking)
		return false;
	if (CanMoveHouseTiles() && _isHouseTile)
		return true;
	if (!_isBlocking)
		return true;
	return true;
}

void Ghost::MoveToHouse()
{
	SetCanMoveHouseTiles(true);
	POI = housePOI;
}

void Ghost::UpdatePath()
{	
	if (GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x].isNode)
		MoveToPOI();
}

bool Ghost::CheckForBackTracking(Step* _step)
{
	MovementDirection direction = GetCurrentDirection();

	if (_step->position.x < GetGridPosition().x) //Left
		if (direction == RIGHT)
			return true;

	if (_step->position.x > GetGridPosition().x) //Right
		if(direction == LEFT)
			return true;

	if (_step->position.y < GetGridPosition().y) //Up
		if(direction == DOWN)
			return true;

	if (_step->position.y > GetGridPosition().y) //Down
		if(direction == UP)
			return true;

	return false;
}

void Ghost::SetGhostState(GhostState _ghostState)
{
	ghostState = _ghostState;
}

GhostState Ghost::GetGhostState()
{
	return ghostState;
}

void Ghost::SetIsEaten(bool _isEaten)
{
	isEaten = _isEaten;
}

void Ghost::UpdateSprites()
{
	if (GetEntityState() == EntityState::DEAD)
		viCurrentSprites = viDeadSprites;

	else if (ghostState == GhostState::FRIGHTENED)
		viCurrentSprites = viFrightenedSprites;

	else if (GetCurrentDirection() == MovementDirection::UP)
	{
		viCurrentSprites = viUpMovementSprites;
	}


	else if (GetCurrentDirection() == MovementDirection::DOWN)
	{
		viCurrentSprites = viDownMovementSprites;
	}

	else if (GetCurrentDirection() == MovementDirection::RIGHT)
		viCurrentSprites = viRightMovementSprites;

	else if (GetCurrentDirection() == MovementDirection::LEFT)
		viCurrentSprites = viLeftMovementSprites;

	bool currentFound = false;
	for each (int animationID in viCurrentSprites)
		if (currentSpriteID == animationID)
			currentFound = true;
	
	if (!currentFound)
		currentSpriteID = viCurrentSprites[0];
}

void Ghost::flipDirection()
{
	if (GetCurrentDirection() == UP)
		SetNextDirection(DOWN);

	else if (GetCurrentDirection() == DOWN)
		SetNextDirection(UP);

	else if (GetCurrentDirection() == RIGHT)
		SetNextDirection(LEFT);

	 else if (GetCurrentDirection() == LEFT)
		 SetNextDirection(RIGHT);
}

void Ghost::InHouse()
{
	bool isDoor = GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x].isDoor;
	bool isHouseTile = GetGrid()->mGrid[(int)GetGridPosition().y][(int)GetGridPosition().x].isHouseTile;
	//if we reach the house then we become alive again to harass pacman
	if (!isDoor && isHouseTile)
		if (GetEntityState() == DEAD)
		{
			SetEntityState(ALIVE);
			SetGhostState(CHASE);
		}
}

Vector2<float> Ghost::HousePOI()
{
	return housePOI;
}
