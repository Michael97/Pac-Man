#ifndef __ENTITY_H__
#define __ENTITY_H__

//\===========================================================================================================================================
//\ Filename: Entity.h
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : This is the base class for all moveable and objects in the game (e.g, pacman and the ghosts)
//\===========================================================================================================================================

#include "../Grid.h"
#include "../Vector2.h"
#include "../CoordTranslator.h"
#include "../Collider.h"
#include "../MovementDirection.h"
#include "../EntityState.h"
#include "../GameState.h"

class Entity
{
public:
	void Move();

	//Getters and setters for worldPosition
	void SetWorldPosition(Vector2<float> newWorldPosition);
	Vector2<float> GetWorldPosition();

	//Getters and setters for gridPosition
	void SetGridPosition(Vector2<float> newGridPosition);
	Vector2<float> GetGridPosition();

	//Getters and setters for targetGridPosition
	void SetTargetGridPosition(Vector2<float> _targetGridPosition);
	void SetTargetGridPositionDirection();
	Vector2<float> GetTargetGridPosition();

	void SetSpeed(float _speed);
	float GetSpeed();

	void SetSpriteID(int _spriteID);
	int GetSpriteID();

	void SetIsMoving(bool _isMoving);
	bool IsMoving();

	//Animation GetAnimation();
	void SetGameState(GameState* a_pGameState);
	GameState* GetGameState();

	void SetCanMoveHouseTiles(bool _canMoveHouseTiles);
	bool CanMoveHouseTiles();

	void SetNextDirection(MovementDirection _direction);
	MovementDirection GetNextDirection();

	void SetCurrentDirection(MovementDirection _currentDirection);
	MovementDirection GetCurrentDirection();

	void SetEntityState(EntityState _entityState);
	EntityState GetEntityState();

	Collider GetCollider();

	bool LockPosition();

	void ResetWorldPosition();

	//Pointer to access the grid
	void SetGrid(Grid* _grid);
	Grid* GetGrid();

	virtual void frightened() = 0;
	virtual void flipDirection() = 0;
	void noPath();

	Vector2<float> GetGridPositionRight() { return Right; }
	Vector2<float> GetGridPositionLeft() { return Left; }
	Vector2<float> GetGridPositionUp() { return Up; }
	Vector2<float> GetGridPositionDown() { return Down; }

private:
	//Functions
	void UpdateBoundaries();

	void TranslateMovement();

	void UpdateDirectionValues();
	void UpdateTargetPosition();

	

	void ChangeDirection(Vector2<float> direction);

	virtual bool canMoveToTargetTile(Vector2<float> _targetGridPosition) = 0;

	void Teleport();

private:

	//Variables
	float speed;
	int spriteID;
	bool isMoving;
	bool canMoveHouseTiles;

	Vector2<float> gridPosition;
	Vector2<float> worldPosition;

	Vector2<float> targetGridPosition;
	Vector2<float> targetWorldPosition;

	Vector2<float> GetMovementVector(MovementDirection _MovementDirection);

	//Directions
	Vector2<float> Right = Vector2<float>(gridPosition.x + 1, gridPosition.y);
	Vector2<float> Left = Vector2<float>(gridPosition.x - 1, gridPosition.y);
	Vector2<float> Up = Vector2<float>(gridPosition.x, gridPosition.y - 1);
	Vector2<float> Down = Vector2<float>(gridPosition.x, gridPosition.y + 1);

	MovementDirection nextDirection;
	MovementDirection currentDirection;

	EntityState entityState;

	GameState* pGameState;

	Grid* grid;
};

#endif // __ENTITY_H__