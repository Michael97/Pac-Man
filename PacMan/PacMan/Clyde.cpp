#include "Clyde.h"

Clyde::Clyde()
{
	SetWorldPosition(Vector2<float>(-1, -1));
	SetSpeed(64);
	SetIsMoving(true);
	SetCanMoveHouseTiles(true);
	POI = HousePOI();
	SetNextDirection(LEFT);
}

//Bottom Left
void Clyde::Scatter()
{
	POI = Vector2<float>(2, MAP_HEIGHT - 5);
}

void Clyde::Chase()
{
	//vec2 gridpospacman - vec2 gridposclyde
	//get ABS value
	// if greater than 8 (means pacman is more than 8 tiles away)
	int deltaPos = std::abs((int)Pacman->GetGridPosition().x - (int)GetGridPosition().x) + std::abs((int)Pacman->GetGridPosition().y - (int)GetGridPosition().y);

	if (deltaPos > 8)
		POI = Pacman->GetGridPosition();
	else
		Scatter();


}
