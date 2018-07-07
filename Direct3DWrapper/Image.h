#ifndef IMAGE_H
#define IMAGE_H

#include <d3dx9.h>

namespace GraphicsNS
{

	class Image
	{
		int _xSize = 0;
		int _ySize = 0;
		LPDIRECT3DTEXTURE9 _texture;
	public:

		Image() {};

		int GetXSize();
		int GetYSize();

		void SetXSize(int);
		void SetYSize(int);

		LPDIRECT3DTEXTURE9* GetTexture();
	};
}

#endif // !IMAGE_H
