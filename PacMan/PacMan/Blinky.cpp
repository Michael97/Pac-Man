#include "Blinky.h"

Blinky::Blinky() : Ghost()
{
	SetWorldPosition(Vector2<float>(-1, -1));
	SetSpeed(56);
	SetIsMoving(true);
	SetCanMoveHouseTiles(true);
	POI = HousePOI();
	SetNextDirection(UP);
}

//Top Right
void Blinky::Scatter()
{
	POI = Vector2<float>(27, 6);
	SetGhostState(SCATTER);
}

void Blinky::Chase()
{
	POI = Pacman->GetGridPosition();
	SetGhostState(CHASE);
}

