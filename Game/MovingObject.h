#ifndef MOVING_OBJECT_H
#define MOVING_OBJECT_H

#include "HelpStructs.h"
#include "Image.h"
#include "GameObject.h"

class MovingObject : public GameObject
{
public:
	enum Direction { south, north, east, west, none };
	enum AnimationState {run1, run2, run3, run4};
protected:
	bool _moveEast = false;
	bool _moveWest = false;
	bool _moveNorth = false;
	bool _moveSouth = false;

	int sleepTimeInMs = 10;
	double sleepTimeInSec = (double)sleepTimeInMs / 1000.0;
	//Speed in pixel per iteration
	double speedPxlPerIt;

	bool _collision = false;

	AnimationState _animationState = run1;
	Direction _animationDir = south;
	Direction _nextDir = none;
	int pxlBetweenAnimationUpdate = 12;
	int _animationPxlCounter = 0;

public:
	MovingObject() {};
	MovingObject(TupleInt, GraphicsNS::Graphics*, std::string);
	MovingObject(TupleInt, GraphicsNS::Graphics*, std::string, int, int, int, int);

	void Move(Map*);

	Direction GetAnimationDirection();
	AnimationState GetAnimationState();
	int MovingObject::GetSleepTimeInMs();

	bool IsMoving();
protected:
	void UpdateXPos(Map*);
	void UpdateYPos(Map*);
	void UpdateAnimation();
	void ResetMovement();
};

#endif