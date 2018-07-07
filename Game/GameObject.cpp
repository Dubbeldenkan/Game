#include "GameObject.h"

GameObject::GameObject(TupleInt pos, GraphicsNS::Graphics* g, std::string fileName)
{
	_pos = pos;
	//TODO l�gg till storlek p� bilden?
	g->LoadImageFromFile(fileName.c_str(), &_image);
}

GameObject::GameObject(TupleInt pos, GraphicsNS::Graphics* g, std::string fileName, int imageXSize, int imageYSize,
	int partImageSizeX, int partImageSizeY)
{
	_pos = pos;
	g->LoadImageFromFile(fileName.c_str(), &_image, imageXSize, imageYSize, partImageSizeX, partImageSizeY);
}

GraphicsNS::Image* GameObject::GetImage()
{
	return &_image;
}

TupleInt GameObject::GetPos()
{
	return _pos;
}