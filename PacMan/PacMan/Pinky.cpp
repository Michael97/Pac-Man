#include "Pinky.h"

Pinky::Pinky()
{
	SetWorldPosition(Vector2<float>(-1, -1));
	SetSpeed(52);
	SetIsMoving(true);
	SetCanMoveHouseTiles(true);
	POI = HousePOI();
	SetNextDirection(RIGHT);
}

//Top Left
void Pinky::Scatter()
{
	POI = Vector2<float>(2, 6);
}

void Pinky::Chase()
{
	MovementDirection direction = Pacman->GetCurrentDirection();

	Vector2<float> currentGridTarget;
	Vector2<float> GridPos = Pacman->GetGridPosition();

	if (direction == DOWN)
	{
		currentGridTarget = Vector2<float>(GridPos.x, GridPos.y + 4);

		do
		{
			currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y - 1);
		} while (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking);
	}

	else if (direction == RIGHT)
	{
		currentGridTarget = Vector2<float>(GridPos.x + 4, GridPos.y);

		do
		{
			currentGridTarget = Vector2<float>(currentGridTarget.x - 1, currentGridTarget.y);
		} while (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking);
	}

	else if (direction == LEFT)
	{
		currentGridTarget = Vector2<float>(GridPos.x - 4, GridPos.y);

		do
		{
			currentGridTarget = Vector2<float>(currentGridTarget.x + 1, currentGridTarget.y);
			if (currentGridTarget.x == GridPos.x)
				return;
		} while (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking);
	}

	else if (direction == UP)
	{
		currentGridTarget = Vector2<float>(GridPos.x, GridPos.y - 4);
		currentGridTarget = Vector2<float>(currentGridTarget.x - 4, currentGridTarget.y);

		do
		{
			currentGridTarget = Vector2<float>(currentGridTarget.x, currentGridTarget.y + 1);

			if (currentGridTarget.y == GridPos.y)
				currentGridTarget = Vector2<float>(currentGridTarget.x + 1, currentGridTarget.y);
			if (currentGridTarget.x == GridPos.x)
				return;

		} while (GetGrid()->mGrid[(int)currentGridTarget.y][(int)currentGridTarget.x].isBlocking);
	}
	
	POI = currentGridTarget;
}
