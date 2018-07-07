#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "HelpStructs.h"
#include "Image.h"
#include "Graphics.h"
#include <string>
#include "Map.h"

class GameObject
{
protected:
	TupleInt _pos;
	GraphicsNS::Image _image;
	
public:
	GameObject() {};
	GameObject(TupleInt, GraphicsNS::Graphics*, std::string);
	GameObject(TupleInt, GraphicsNS::Graphics*, std::string, int, int, int, int);

	GraphicsNS::Image* GetImage();
	TupleInt GetPos();
};

#endif // !GAME_OBJECT_H