#ifndef DRAW_H
#define DRAW_H

#include "Map.h"
#include <iostream>
#include <string>

#include "Graphics.h"

class Draw
{
public:
	struct Pos
	{
		int x;
		int y;
		float s;

		Pos(int xIn, int yIn)
		{
			x = xIn;
			y = yIn;
			s = 0.0;
		}
		Pos(int xIn, int yIn, float sIn)
		{
			x = xIn;
			y = yIn;
			s = sIn;
		}
	};

private:
	GraphicsNS::Graphics* _g;

	GraphicsNS::Image _farmland;
	GraphicsNS::Image _forest;
	GraphicsNS::Image _mountain;
	GraphicsNS::Image _swamp;
	GraphicsNS::Image _water;

public:
	Draw() {};
	Draw(HWND*);
	~Draw() {};

	void DrawView(Map*);
};

#endif // !DRAW_H