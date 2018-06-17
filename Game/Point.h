#ifndef POINT_H
#define POINT_H


const class Point
{
public:
	Point();
	Point(int, int);

	int GetXPos();
	int GetYPos();

	void SetXPos(int);
	void SetYPos(int);

private:
	int _xPos;
	int _yPos;
};

#endif // !POINT_H
