#include "TargetTileSprite.h"

TargetTileSprite::TargetTileSprite()
{
	SetWorldPosition(Vector2<float>(-1, -1));

	
}

void TargetTileSprite::Target(Vector2<float> _location)
{
	Vector2<float> vec = CoordTranslator::translateToWorldPosition(_location);

	SetWorldPosition(vec);
	SetGridPosition(_location);
	SetTargetGridPosition(_location);

	Vector2<float> worldPos = GetWorldPosition();

	UG::SetSpritePosition(GetSpriteID(), vec.x, WINDOW_SIZE_HEIGHT - vec.y);

}

void TargetTileSprite::frightened()
{

}
void TargetTileSprite::flipDirection()
{

}

bool TargetTileSprite::canMoveToTargetTile(Vector2<float> _targetGridPosition)
{
	return false;
}


