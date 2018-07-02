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

	enum TileType { Undefined, FarmLand, Forest, Mountain, Swamp, Water};

private:
	static const int _mapXSize = 1300;
	static const int _mapYSize = 660;
	const int _influenceDist = 20;
	const int _mapBorder = _influenceDist;

	void DefineTile(int, int);
	void SetTile(int, int, int);

	int _matrix[_mapXSize][_mapYSize];
};

#endif // !MAP_H
