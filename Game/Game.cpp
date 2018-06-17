// Game.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>

#include "Draw.h"
#include "Map.h"

int main()
{
	Map map = Map();
	map.CreateMap();

	Draw draw;
	draw.DrawMatrix(&map);

	while (true);
    return 0;
}

