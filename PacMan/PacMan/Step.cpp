#include "Step.h"

Step::Step()
{
	position = Vector2<float>(0,0);
	score = PathScore();
}

Step::Step(Vector2<float> _position)
{
	position = _position;
	score = PathScore();
}

Step::Step(Vector2<float>* _position)
{
	//Dereferencing pointer
	position = *_position;
	score = PathScore();
}

bool Step::operator>(const Step& _step) const
{
	return score.GetTotal() > _step.score.GetTotal();
}


