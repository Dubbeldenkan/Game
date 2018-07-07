#include "Image.h"

namespace GraphicsNS
{

	int Image::GetXSize()
	{
		if (_xSize == 0)
		{
			D3DSURFACE_DESC surfaceDesc;
			_texture->GetLevelDesc(0, &surfaceDesc);
			return surfaceDesc.Width;
		}
		return _xSize;
	}

	int Image::GetYSize()
	{
		if (_ySize == 0)
		{
			D3DSURFACE_DESC surfaceDesc;
			_texture->GetLevelDesc(0, &surfaceDesc);
			return surfaceDesc.Height;
		}
		return _ySize;
	}

	void Image::SetXSize(int size)
	{
		_xSize = size;
	}

	void Image::SetYSize(int size)
	{
		_ySize = size;
	}

	LPDIRECT3DTEXTURE9* Image::GetTexture()
	{
		return &_texture;
	}
}