#ifndef GRAPHICS_H
#define GRAPHICS_H

//TODO jämför denna fil med den i platformsspelet om den är nyare. 

#include <d3d9.h>
#include <Windows.h>
#include "Image.h"
#include <stdio.h>
#include <D3dx9math.h>
#include <vector>
#include <string>

namespace GraphicsNS
{

	class Graphics
	{
	public:
		const static int FONT_SIZE_SMALL = 8;
		const static int FONT_SIZE_BIG = 15;
		const static D3DCOLOR WHITE = D3DCOLOR_XRGB(255, 255, 255);
		const static D3DCOLOR BLACK = D3DCOLOR_XRGB(0, 0, 0);
		const static D3DCOLOR RED = D3DCOLOR_XRGB(255, 0, 0);
		const static D3DCOLOR BLUE = D3DCOLOR_XRGB(0, 0, 255);

		LPDIRECT3D9 _d3d;
		LPDIRECT3DDEVICE9 _d3dDevice;
		LPD3DXFONT _font8;
		LPD3DXFONT _font15;
		HDC _hdc;
		LPD3DXSPRITE _sprite = 0;
		std::vector<Image*> imageVector;
		char imagePath[MAX_PATH];

	public:
		Graphics();
		Graphics(HWND hWnd);
		~Graphics();

		void Flip(bool waitRetrace = true);

		void Clear(DWORD color = 0);

		Image LoadImage(const char* filename);

		void StartDrawing();

		void StopDrawing();

		void Draw(Image*, int, int, float);

		void PrintText8(char*, int, int, D3DCOLOR);

		void PrintText15(char*, int, int, D3DCOLOR);

		void PrintText8(int, int, int, D3DCOLOR);

		void PrintText15(int, int, int, D3DCOLOR);

		//void SetTextSize(int);
	};
}

#endif