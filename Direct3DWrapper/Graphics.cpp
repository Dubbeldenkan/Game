#include "Graphics.h"

namespace GraphicsNS
{
	Graphics::Graphics() {};

	Graphics::Graphics(HWND hWnd)
	{
		char tempPath[MAX_PATH];
		GetModuleFileName(NULL, tempPath, MAX_PATH);
		std::string str = std::string(tempPath);
		str.erase(str.rfind('\\'));
		str.erase(str.rfind('\\'));
		strcpy_s(imagePath, "");
		strcpy_s(imagePath, str.c_str());
		strcat_s(imagePath, "\\Bilder\\");

		_d3d = Direct3DCreate9(D3D_SDK_VERSION);
		if (_d3d == 0)
		{
			OutputDebugString("Unable to setup Direct3DCreate9\n\n");
		}
		D3DPRESENT_PARAMETERS presentParameters = { 0 };
		presentParameters.Windowed = true;
		presentParameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
		presentParameters.BackBufferFormat = D3DFMT_UNKNOWN;

		_d3dDevice = 0;
		HRESULT hr = _d3d->CreateDevice(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			hWnd,
			D3DCREATE_SOFTWARE_VERTEXPROCESSING,
			&presentParameters,
			&_d3dDevice);

		if (FAILED(hr))
		{
			OutputDebugString("Unable to setup d3dDevice\n\n");
		}

		hr = D3DXCreateSprite(_d3dDevice, &_sprite);
		if (FAILED(hr))
		{
			OutputDebugString("Unable to setup sprite\n\n");
		}

		//Makes it possible to print text
		_hdc = GetDC(0);
		int logicalHeight = -MulDiv(FONT_SIZE_SMALL, GetDeviceCaps(_hdc, LOGPIXELSY), 72);
		hr = D3DXCreateFont(
			_d3dDevice,
			logicalHeight,
			0,
			0,
			1,
			0,
			ANSI_CHARSET,
			OUT_TT_ONLY_PRECIS,
			0,
			0,
			"Helvetica",
			&_font8);

		if (FAILED(hr))
		{
			OutputDebugString("Unable to setup font8\n\n");
		}

		logicalHeight = -MulDiv(FONT_SIZE_BIG, GetDeviceCaps(_hdc, LOGPIXELSY), 72);
		hr = D3DXCreateFont(
			_d3dDevice,
			logicalHeight,
			0,
			0,
			1,
			0,
			ANSI_CHARSET,
			OUT_TT_ONLY_PRECIS,
			0,
			0,
			"Helvetica",
			&_font15);

		if (FAILED(hr))
		{
			OutputDebugString("Unable to setup font8\n\n");
		}
	}

	Graphics::~Graphics()
	{
		if (_d3dDevice)
		{
			_d3dDevice->Release();
			_d3dDevice = 0;
		}
		if (_d3d)
		{
			_d3d->Release();
			_d3d = 0;
		}
		if (_sprite)
		{
			_sprite->Release();
			_sprite = 0;
		}
		for (int i = 0; static_cast<unsigned int>(i) < imageVector.size(); i++)
		{
			delete imageVector[i];
		}
	}

	void Graphics::Flip(bool waitRetrace)
	{
		_d3dDevice->Present(0, 0, 0, 0);
	}

	void Graphics::Clear(DWORD color)
	{
		int colorB = color % 256; color /= 256;
		int colorG = color % 256; color /= 256;
		int colorR = color % 256; color /= 256;
		HRESULT hr = _d3dDevice->Clear(
			0, 0,
			D3DCLEAR_TARGET,
			D3DCOLOR_XRGB(colorB, colorG, colorR),
			0, 0);
		if (FAILED(hr))
		{
			OutputDebugString("Unable to run clear for d3dDevice in function Flip\n\n");
		}
	}

	Image Graphics::LoadImage(const char* fileName)
	{
		char path[MAX_PATH];
		strcpy_s(path, imagePath);
		strcat_s(path, fileName);
		Image result;
		HRESULT hr = D3DXCreateTextureFromFile(
			_d3dDevice,
			path,
			&result._texture);
		if (FAILED(hr))
		{
			OutputDebugString("Cannot load image\n\n");
		}
		else
		{
			imageVector.push_back(&result);
			OutputDebugString("Image was loaded\n\n");
		}
		return result;
	}

	void Graphics::StartDrawing()
	{
		_d3dDevice->BeginScene();
	}

	void Graphics::StopDrawing()
	{
		_d3dDevice->EndScene();
	}

	void Graphics::Draw(Image* image, int x, int y, float scale)
	{
		D3DXVECTOR3 position(x / scale, y / scale, 0);
		_sprite->Begin(0);
		D3DXMATRIX transformMatrix;
		D3DXMatrixScaling(&transformMatrix, scale, scale, 0.0f);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Draw(
			image->_texture,
			0,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		_sprite->End();
	}

	void Graphics::PrintText8(char* text, int xPos, int yPos, D3DCOLOR color)
	{
		RECT rectangle = { xPos, yPos, 0, 0 };
		_font8->DrawText(
			0,
			text,
			-1,
			&rectangle,
			DT_NOCLIP,
			color);
	}

	void Graphics::PrintText8(int number, int xPos, int yPos, D3DCOLOR color)
	{
		std::string str;
		str = std::to_string(number);
		const char* buffer = str.c_str();
		PrintText8((char*)buffer, xPos, yPos, color);
	}

	void Graphics::PrintText15(char* text, int xPos, int yPos, D3DCOLOR color)
	{
		RECT rectangle = { xPos, yPos, 0, 0 };
		_font15->DrawText(
			0,
			text,
			-1,
			&rectangle,
			DT_NOCLIP,
			color);
	}

	void Graphics::PrintText15(int number, int xPos, int yPos, D3DCOLOR color)
	{
		std::string str;
		str = std::to_string(number);
		const char* buffer = str.c_str();
		PrintText15((char*)buffer, xPos, yPos, color);
	}

}