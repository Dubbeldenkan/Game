#ifndef MAP_H
#define MAP_H

#include "Point.h"
#include <stdlib.h>
#include <time.h>

class Map
{
public:
	Map();

	int GetXMapSize();
	int GetYMapSize();
	void CreateMap();
	int GetTile(int, int);

private:
	static const int _mapXSize = 200;
	static const int _mapYSize = 50;
	const int _influenceDist = 4;
	const int _mapBorder = _influenceDist;

	const int _forestTileValue = 42;
	const int _mountainTileValue = 94;
	const int _grassTileValue = 95;
	const int _waterTileValue = 126;

	void DefineTile(int, int);
	void SetTile(int, int, int);

	int _matrix[_mapXSize][_mapYSize];
};

#endif // !MAP_H
