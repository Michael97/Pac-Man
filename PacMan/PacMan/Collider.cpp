#include "Collider.h"

Collider::Collider(Vector2<float> _vector)
{
	vector = _vector;
}

Collider::~Collider()
{

}


bool Collider::CheckCollision(Collider other)
{
	Vector2<float> otherPosition = other.GetPosition();
	Vector2<float> otherHalfSize = other.GetHalfSize();
	Vector2<float> thisPosition = GetPosition();
	Vector2<float> thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	
	float intersectX = std::abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = std::abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		return true;
	}
	return false;
}
