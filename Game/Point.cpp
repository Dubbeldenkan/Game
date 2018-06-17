#include "Point.h"

Point::Point(int xPos, int yPos)
{
	_xPos = xPos;
	_yPos = yPos;
}

Point::Point()
{};

int Point::GetXPos()
{
	return _xPos;
}

int Point::GetYPos()
{
	return _yPos;
}

void Point::SetXPos(int xPos)
{
	_xPos = xPos;
}

void Point::SetYPos(int yPos)
{
	_yPos = yPos;
}