#include "Entity.h"

void Entity::UpdateBoundaries()
{
	//Check if we move past the target grid world position, then move back
	switch (currentDirection)
	{
	case UP:
		//less than then its gone past it
		if (worldPosition.y < targetWorldPosition.y)
		{
			worldPosition.y = targetWorldPosition.y;
			gridPosition = targetGridPosition;
			SetIsMoving(true);
		}
		break;
	case DOWN:
		//greater than then its gone past it
		if (worldPosition.y > targetWorldPosition.y)
		{
			worldPosition.y = targetWorldPosition.y;
			gridPosition = targetGridPosition;
			SetIsMoving(true);
		}
		break;
	case LEFT:
		//less than then its gone past it
		if (worldPosition.x < targetWorldPosition.x)
		{
			worldPosition.x = targetWorldPosition.x;
			gridPosition = targetGridPosition;
			SetIsMoving(true);
		}
		break;
	case RIGHT:
		//greater than then its gone past it
		if (worldPosition.x > targetWorldPosition.x)
		{
			worldPosition.x = targetWorldPosition.x;
			gridPosition = targetGridPosition;
			SetIsMoving(true);
		}
		break;
	default:
		break;
	}
}

void Entity::TranslateMovement()
{
	switch (currentDirection)
	{
	case UP:
		worldPosition.y -= speed * UG::GetDeltaTime();
		break;
	case DOWN:
		worldPosition.y += speed * UG::GetDeltaTime();
		break;
	case LEFT:
		worldPosition.x -= speed * UG::GetDeltaTime();
		break;
	case RIGHT:
		worldPosition.x += speed * UG::GetDeltaTime();
		break;
	default:
		break;
	}
}

void Entity::Move()
{
	
	UpdateTargetPosition();
	if (!canMoveToTargetTile(targetGridPosition))
		return;

	TranslateMovement();
	UpdateBoundaries();

}

void Entity::ChangeDirection(Vector2<float> direction)
{
	currentDirection = nextDirection;
	targetGridPosition = direction;
	SetIsMoving(false);
}

void Entity::UpdateDirectionValues()
{
	Right = Vector2<float>(gridPosition.x + 1, gridPosition.y);
	Left = Vector2<float>(gridPosition.x - 1, gridPosition.y);
	Up = Vector2<float>(gridPosition.x, gridPosition.y - 1);
	Down = Vector2<float>(gridPosition.x, gridPosition.y + 1);
}

void Entity::UpdateTargetPosition()
{
	UpdateDirectionValues();

	//If the current tile is a wall then return
	if (grid->mGrid[(int)gridPosition.y][(int)gridPosition.x].isBlocking)
		return;

	if (!IsMoving())
		return;

	//if the gridposition is a node then teleport to the coorisponding portal node
	if (grid->mGrid[(int)gridPosition.y][(int)gridPosition.x].isPortal)
		Teleport();

	if (canMoveToTargetTile(GetMovementVector(nextDirection)))
		ChangeDirection(GetMovementVector(nextDirection));

	else
		SetTargetGridPositionDirection();

	targetWorldPosition = CoordTranslator::translateToWorldPosition(targetGridPosition);

	//If we have not updated our world position yet, we set it when we update our target position the first time
	if (worldPosition.x == -1 && worldPosition.y == -1)
		worldPosition = CoordTranslator::translateToWorldPosition(gridPosition);
}

void Entity::Teleport()
{
	auto adjacentSteps = grid->mGrid[(int)gridPosition.y][(int)gridPosition.x].neighbourSteps;

	for each(Step* adjacentStep in adjacentSteps)
	{
		//Skips the empty neighbour steps
		if (adjacentStep == nullptr)
			continue;

		if (adjacentStep->portal)
		{
			SetGridPosition(adjacentStep->position);
			SetWorldPosition(CoordTranslator::translateToWorldPosition(adjacentStep->position));
		}
	}
}

void Entity::flipDirection()
{

}

void Entity::SetWorldPosition(Vector2<float> newWorldPosition)
{
	worldPosition = newWorldPosition;
}

Vector2<float> Entity::GetWorldPosition()
{
	return worldPosition;
}

void Entity::SetGridPosition(Vector2<float> newGridPosition)
{
	gridPosition = newGridPosition;
}

Vector2<float> Entity::GetGridPosition()
{
	return gridPosition;
}

void Entity::SetSpeed(float _speed)
{
	speed = _speed;
}

float Entity::GetSpeed()
{
	return speed;
}

void Entity::SetSpriteID(int _spriteID)
{
	spriteID = _spriteID;
}

int Entity::GetSpriteID()
{
	return spriteID;
}

void Entity::SetIsMoving(bool _isMoving)
{
	isMoving = _isMoving;
}

bool Entity::IsMoving()
{
	return isMoving;
}


void Entity::SetGameState(GameState * a_pGameState)
{
	pGameState = a_pGameState;
}

GameState * Entity::GetGameState()
{
	return pGameState;
}

void Entity::SetCanMoveHouseTiles(bool _canMoveHouseTiles)
{
	canMoveHouseTiles = _canMoveHouseTiles;
}

bool Entity::CanMoveHouseTiles()
{
	return canMoveHouseTiles;
}

void Entity::SetNextDirection(MovementDirection _direction)
{
	nextDirection = _direction;
}

MovementDirection Entity::GetNextDirection()
{
	return nextDirection;
}

void Entity::SetCurrentDirection(MovementDirection _currentDirection)
{
	currentDirection = _currentDirection;
}

MovementDirection Entity::GetCurrentDirection()
{
	return currentDirection;
}

void Entity::SetEntityState(EntityState _entityState)
{
	entityState = _entityState;
}

EntityState Entity::GetEntityState()
{
	return entityState;
}

Collider Entity::GetCollider()
{
	return Collider(worldPosition);
}

bool Entity::LockPosition()
{
	if (GetGameState() != nullptr)
	{
		if (*GetGameState() == PAUSEMENU || *GetGameState() == DEADMENU)
			return true;
		else
			return false;
	}
	return false;
}

void Entity::ResetWorldPosition()
{
	entityState = ALIVE;
	currentDirection = LEFT;
	worldPosition = CoordTranslator::translateToWorldPosition(gridPosition);
	
	UpdateDirectionValues();
	SetTargetGridPositionDirection();

	targetWorldPosition = CoordTranslator::translateToWorldPosition(targetGridPosition);


}

void Entity::SetGrid(Grid * _grid)
{
	grid = _grid;
}

Grid * Entity::GetGrid()
{
	return grid;
}

Vector2<float> Entity::GetMovementVector(MovementDirection _MovementDirection)
{
	if (nextDirection == RIGHT)
		return Right;

	if (nextDirection == LEFT)
		return Left;

	if (nextDirection == UP)
		return Up;
	return Down;
}

void Entity::SetTargetGridPosition(Vector2<float> _targetGridPosition)
{
	targetGridPosition = _targetGridPosition;
}

void Entity::SetTargetGridPositionDirection()
{
	switch(currentDirection)
	{
	case RIGHT:
		targetGridPosition = Right;
		break;
	case LEFT:
		targetGridPosition = Left;
		break;
	case UP:
		targetGridPosition = Up;
		break;
	case DOWN:
		targetGridPosition = Down;
		break;
	default:
		break;
	}
}

void Entity::noPath()
{
	if (grid->mGrid[(int)targetGridPosition.y][(int)targetGridPosition.x].isBlocking)
	{
		frightened();
	}
}

Vector2<float> Entity::GetTargetGridPosition()
{
	return targetGridPosition;
}
