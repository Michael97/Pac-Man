//\===========================================================================================================================================
//\ Filename: AStar.cpp
//\ Author  : Michael Thomas
//\ Date    : 14/10/2017
//\ Brief   : .cpp file that holds all the functions to generate a a* path
//\===========================================================================================================================================

#include "AStar.h"


AStar::AStar()
{

}

AStar::AStar(Entity* _ghost, Vector2<float> _destination)
{
	ghost = _ghost;
	source = ghost->GetGridPosition();
	destination = _destination;

	//Prepare starting Step (the position which we start from)
	Step* step = new Step();
	step->position = source;

	open.push_back(step);

	//Stops backtracking
	stepBehind = new Step();
	
	if (ghost->GetCurrentDirection() == UP)
		stepBehind->position = Vector2<float>(ghost->GetGridPosition().x, ghost->GetGridPosition().y + 1);
	else if (ghost->GetCurrentDirection() == DOWN)
		stepBehind->position = Vector2<float>(ghost->GetGridPosition().x, ghost->GetGridPosition().y - 1);
	else if (ghost->GetCurrentDirection() == LEFT)
		stepBehind->position = Vector2<float>(ghost->GetGridPosition().x + 1, ghost->GetGridPosition().y);
	else if (ghost->GetCurrentDirection() == RIGHT)
		stepBehind->position = Vector2<float>(ghost->GetGridPosition().x - 1, ghost->GetGridPosition().y);

	closed.push_back(stepBehind);

	Path();
}

void AStar::CantComputePath()
{
	if (stepBehind->position == destination)
	{
		auto adjacentSteps = ghost->GetGrid()->mGrid[(int)ghost->GetGridPosition().y][(int)ghost->GetGridPosition().x].neighbourSteps;
		
		for each (Step* adjacentStep in adjacentSteps)
		{
			//Skips the empty neighbour steps
			if (adjacentStep == nullptr)
				continue;
				
			//stops backtracking
			if (adjacentStep->position == stepBehind->position)
				continue;

			//if the step is a house tile, and its not aloud to move there then dont
			if (adjacentStep->isHouseTile && !ghost->CanMoveHouseTiles())
				continue;

			if (adjacentStep->position == ghost->GetGridPositionRight())
				ghost->SetNextDirection(RIGHT);
			else if (adjacentStep->position == ghost->GetGridPositionLeft())
				ghost->SetNextDirection(LEFT);
			else if (adjacentStep->position == ghost->GetGridPositionUp())
				ghost->SetNextDirection(UP);
			else if (adjacentStep->position == ghost->GetGridPositionDown())
				ghost->SetNextDirection(DOWN);

		}
	}
}

void AStar::Path()
{
	while (open.size() > 0)
	{
		std::vector<Step*> shortestSteps = StepsWithLowestFScoreVal();

		//if we are at the destination, create the path
		if (shortestSteps[0]->position.x == destination.x && shortestSteps[0]->position.y == destination.y)
		{
			totalPath = ReconstructPath(shortestSteps[0]);
			return;
		}

		//Add the current shortest step to closed
		if (std::find(closed.begin(), closed.end(), shortestSteps[0]) == closed.end())
			closed.push_back(shortestSteps[0]);

		//Remove the current shortest step from open
		open.erase(std::remove(open.begin(), open.end(), shortestSteps[0]), open.end());

		auto adjacentSteps = ghost->GetGrid()->mGrid[(int)shortestSteps[0]->position.y][(int)shortestSteps[0]->position.x].neighbourSteps;

		for each (Step* adjacentStep in adjacentSteps)
		{
			//Skips the empty neighbour steps
			if (adjacentStep == nullptr)
				continue;

			//if the step is a house tile, and its not aloud to move there then dont
			if (adjacentStep->isHouseTile && !ghost->CanMoveHouseTiles())
				continue;

			//if not in closed or open then we add it
			if (!StepExistsInVector(adjacentStep, open))
				if (!StepExistsInVector(adjacentStep, closed))
					open.push_back(adjacentStep);

			//for backtracking
			adjacentStep->parentStep = shortestSteps[0];
			adjacentStep->score.SetMovement(movementValue);
			adjacentStep->score.SetHeuristics(ComputeHeuristics(adjacentStep->position, destination));
		}
	}
	CantComputePath();
}

std::vector<Vector2<float>> AStar::ReconstructPath(Step * _lastStep)
{
	std::vector<Vector2<float>> generatedPath;
	//Get the parent steps and stuff
	while (_lastStep->parentStep != nullptr)
	{
		Step* currentStep = _lastStep;
		generatedPath.push_back(currentStep->position);
		_lastStep = currentStep->parentStep;
	}	

	//add the source
	generatedPath.push_back(source);
	//reverse the vector cause its backwards atm
	std::reverse(generatedPath.begin(), generatedPath.end());

	return generatedPath;
}

std::vector<Step*> AStar::StepsWithLowestFScoreVal()
{
	std::vector<Step*> shortestSteps;

	int lowestTotalScore = std::numeric_limits<int>::max(); 

	for each (Step* openStep in open)
		if (openStep->score.GetTotal() < lowestTotalScore)
			lowestTotalScore = openStep->score.GetTotal();

	for each (Step* openStep in open)
		if (lowestTotalScore == openStep->score.GetTotal())
			shortestSteps.push_back(openStep);

	return shortestSteps;
}

bool AStar::StepExistsInVector(Step * step, std::vector<Step*> steps)
{
	for each (Step* stepIn in steps)
		if (step->position.x == stepIn->position.x && step->position.y == stepIn->position.y)
			return true;
	
	return false;
}

int AStar::ComputeHeuristics(Vector2<float> _position, Vector2<float> _destination)
{
	return std::abs((int)_destination.x - (int)_position.x) + std::abs((int)_destination.y - (int)_position.y);
}