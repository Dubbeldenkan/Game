#ifndef MAP_H
#define MAP_H

#include <stdlib.h>
#include <time.h>

#include "Image.h"
#include "Graphics.h"

class Map
{
public:
	static const int MAPXSIZE = 500;
	static const int MAPYSIZE = 500;
	static const int TILESIZE = 20;

	enum TileType { Undefined, FarmLand, Forest, Mountain, Swamp, Water };

	Map();
	~Map() {}; //TODO gör bra destructorer för alla klasser

	void InitMap(GraphicsNS::Graphics*);
	GraphicsNS::Image* GetTileImage(int, int);

private:
	const int _influenceDist = 7;
	const int _mapBorder = _influenceDist;

	void DefineTile(int, int);
	void SetTile(int, int, int);
	int GetTile(int, int);
	void CreateMap();

	int _matrix[MAPXSIZE][MAPYSIZE];

	GraphicsNS::Image _farmland;
	GraphicsNS::Image _forest;
	GraphicsNS::Image _mountain;
	GraphicsNS::Image _swamp;
	GraphicsNS::Image _water;
};

#endif // !MAP_H
