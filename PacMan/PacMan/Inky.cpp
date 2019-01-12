#include "Inky.h"

//constructor
Inky::Inky()
{
	SetWorldPosition(Vector2<float>(-1, -1));
	SetSpeed(60);
	SetIsMoving(true);
	SetCanMoveHouseTiles(true);
	POI = HousePOI();
	SetNextDirection(LEFT);
}

//Bottom Right scatter location
void Inky::Scatter()
{
	POI = Vector2<float>(27, MAP_HEIGHT - 5);
}

//inky's chase function
void Inky::Chase()
{
	//Inky's target tile is based off pacmans location and blinky's location so we need both

	//grab the pacman stuff
	MovementDirection pacmanDirection = Pacman->GetCurrentDirection();
	Vector2<float> pacmanGridPos = Pacman->GetGridPosition();

	//grab pinkys stuff
	Vector2<float> blinkyPos = blinky->GetGridPosition();
	Vector2<float> currentGridTarget;

	bool noPathFound = true;
	
	//set the currentgridtarget based on pacmans direction
	if (pacmanDirection == DOWN)
		currentGridTarget = Vector2<float>(pacmanGridPos.x, pacmanGridPos.y + 2);

	else if (pacmanDirection == RIGHT)
		currentGridTarget = Vector2<float>(pacmanGridPos.x + 2, pacmanGridPos.y);

	else if (pacmanDirection == LEFT)
		currentGridTarget = Vector2<float>(pacmanGridPos.x - 2, pacmanGridPos.y);

	else if (pacmanDirection == UP)
		currentGridTarget = Vector2<float>(pacmanGridPos.x, pacmanGridPos.y - 2);

	//distance between blinky and the currentgridtarget * 2
	currentGridTarget.x = (currentGridTarget.x * 2) - blinkyPos.x;
	currentGridTarget.y = (currentGridTarget.y * 2) - blinkyPos.y;
	
	//if there isnt a path cause its outside the map
	while (noPathFound)
	{
		//retrace steps till we are back on the map
		if (currentGridTarget.x > MAP_WIDTH-1)
			currentGridTarget = Vector2<float>(currentGridTarget.x - 1, currentGridTarget.y);
		if (currentGridTarget.x < 2)
			currentGridTarget = Vector2<float>(currentGridTarget.x + 1, currentGridTarget.y);
		if (currentGridTarget.y > MAP_HEIGHT-1)
			currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y - 1);
		if (currentGridTarget.y < 1)
			currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y + 1);

		if (currentGridTarget.x > MAP_WIDTH-1 || currentGridTarget.x < 2 ||
			currentGridTarget.y > MAP_HEIGHT-1 || currentGridTarget.y < 1)
			continue;

		noPathFound = false;
	}
	
	//retrace steps if we are not on a tile we can do stuff on
	if (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking)
	{
		do
		{
			if (currentGridTarget.x < pacmanGridPos.x)
				currentGridTarget = Vector2<float>(currentGridTarget.x + 1, currentGridTarget.y);
			if (currentGridTarget.x > pacmanGridPos.x)
				currentGridTarget = Vector2<float>(currentGridTarget.x - 1, currentGridTarget.y);
			if (currentGridTarget.y < pacmanGridPos.y)
				currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y + 1);	
			if (currentGridTarget.y > pacmanGridPos.y)
				currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y - 1);

		} while (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking);
	}
	//set the POI as currentgridtarget
	POI = currentGridTarget;
}

void Inky::SetBlinky(Entity * _blinky)
{
	blinky = _blinky;
}
