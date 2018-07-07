#ifndef HELP_STRUCTS_H
#define HELP_STRUCTS_H

struct TupleInt
{
	int x;
	int y;

	TupleInt() {};

	TupleInt(int xIn, int yIn)
	{
		x = xIn;
		y = yIn;
	}
};

//TODO kan anv�ndas f�r v�gar och ev floder
struct TileStruct
{
	//riktningarna �r definierade som 0, 90, 180, 270 grader men skrivna i 
	// pi/2, pi, 3/4*pi *100 f�r att kunna skriva det som ints
	enum TileDir {down = 0, left = 157, up = 314, right = 471};
	enum TileImage {none, one, two_I, two_L, three, four};
	TileImage tileImage;
	TileDir tileDir;

	TileStruct() {};

	TileStruct(TileImage tileImageIn, TileDir tileDirIn)
	{
		tileImage = tileImageIn;
		tileDir = tileDirIn;
	}
};

#endif // !HELP_STRUCTS_H