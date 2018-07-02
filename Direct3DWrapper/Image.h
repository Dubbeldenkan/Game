#ifndef IMAGE_H
#define IMAGE_H

#include <d3dx9.h>

namespace GraphicsNS
{

	class Image
	{
		int xSize;
		int ySize;
	public:
		LPDIRECT3DTEXTURE9 _texture;

		Image() {};

		int GetxSize()
		{
			D3DSURFACE_DESC surfaceDesc;
			_texture->GetLevelDesc(0, &surfaceDesc);
			return surfaceDesc.Width;
		}

		int GetYSize()
		{
			D3DSURFACE_DESC surfaceDesc;
			_texture->GetLevelDesc(0, &surfaceDesc);
			return surfaceDesc.Height;
		}
	};

}

#endif // !IMAGE_H
