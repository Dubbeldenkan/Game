#include "MovingObject.h"

MovingObject::MovingObject(TupleInt pos, GraphicsNS::Graphics* g, std::string fileName)
	: GameObject(pos, g, fileName)
{
	_pos.x = pos.x;
	_pos.y = pos.y;
}

MovingObject::MovingObject(TupleInt pos, GraphicsNS::Graphics* g, std::string fileName,
	int imageXSize, int imageYSize, int partImageSizeX, int partImageSizeY)
	: GameObject(pos, g, fileName, imageXSize, imageYSize, partImageSizeX, partImageSizeY)
{
	_pos.x = pos.x;
	_pos.y = pos.y;
}

int MovingObject::GetSleepTimeInMs()
{
	return sleepTimeInMs;
}

MovingObject::Direction MovingObject::GetAnimationDirection()
{
	return _animationDir;
}

MovingObject::AnimationState MovingObject::GetAnimationState()
{
	return _animationState;
}

void MovingObject::Move(Map* map)
{
	//TODO
}

void MovingObject::ResetMovement()
{
	_moveNorth = false;
	_moveSouth = false;
	_moveEast = false;
	_moveWest = false;
	_nextDir = none;
	_animationState = run1;
}

void MovingObject::UpdateXPos(Map* map)
{
	//TODO
}

void MovingObject::UpdateYPos(Map* map)
{
	//TODO
}

void MovingObject::UpdateAnimation()
{
	if (IsMoving())
	{
		_animationPxlCounter++;
		if (_animationPxlCounter == pxlBetweenAnimationUpdate)
		{
			_animationPxlCounter = 0;
			_animationState = (MovingObject::AnimationState) (((int)_animationState + 1) % 4);
		}
	}
}

bool MovingObject::IsMoving()
{
	return _moveSouth || _moveWest || _moveEast || _moveNorth;
}