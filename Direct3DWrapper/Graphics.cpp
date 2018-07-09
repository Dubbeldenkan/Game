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
		imagePath = str + "\\Bilder\\";

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

		//load pixel Images
		LoadImageFromFile("Pixel/Red.png", &redPixel);
		LoadImageFromFile("Pixel/Blue.png", &bluePixel);
		LoadImageFromFile("Pixel/Black.png", &blackPixel);
		LoadImageFromFile("Pixel/White.png", &whitePixel);
		LoadImageFromFile("Pixel/Green.png", &greenPixel);
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
		for (int i = 0; i < (int)imageVector.size(); i++)
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

	//Används då man bara har en bild, dvs inte flera tiles
	void Graphics::LoadImageFromFile(std::string fileName, Image* image)
	{
		LoadImageFromFile(fileName, image, 0, 0, 0, 0);
	}

	//Används då man bara har en bild, dvs inte flera tiles och definierad storlek
	void Graphics::LoadImageFromFile(std::string fileName, Image* image, int imageXSize, int imageYSize)
	{
		LoadImageFromFile(fileName, image, imageXSize, imageYSize, 0, 0);
	}

	//Används då man bara har en flera tiles
	void Graphics::LoadImageFromFile(std::string fileName, Image* image, int imageXSize, int imageYSize,
		int partImageSizeX, int partImageSizeY)
	{
		std::string path = imagePath + fileName;
		HRESULT hr = D3DXCreateTextureFromFileEx(
			_d3dDevice,
			path.c_str(),
			imageXSize, imageYSize,
			1,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DCOLOR_XRGB(0, 0, 0),
			0, 0,
			image->GetTexture());
		if (FAILED(hr))
		{
			OutputDebugString("Cannot load image\n\n");
		}
		else
		{
			imageVector.push_back(image);
			char result[100];
			strcpy_s(result, "Image ");
			strcat_s(result, fileName.c_str());
			strcat_s(result, " was loaded\n\n");
			OutputDebugString(result);
		}
		image->SetXSize(partImageSizeX);
		image->SetYSize(partImageSizeY);
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
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX transformMatrix;
		D3DXMatrixScaling(&transformMatrix, scale, scale, 0.0f);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Draw(
			*(image->GetTexture()),
			0,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		_sprite->End();
	}

	void Graphics::DrawTile(Image* image, int x, int y, int tileIndex, int orientation)
	{
		D3DXVECTOR3 position((float)x, (float)y, 0.0f);
		RECT* rect = new RECT();
		rect->top = 0;
		rect->bottom = image->GetYSize();
		rect->left = image->GetXSize()*tileIndex;
		rect->right = image->GetXSize()*(tileIndex + 1);
		D3DXVECTOR2 center((float)x + image->GetXSize() / 2, (float)y + image->GetYSize() / 2);
		D3DXMATRIX transformMatrix;
		D3DXMatrixTransformation2D(&transformMatrix, NULL, NULL, NULL, &center, ((float)orientation) / 100.0f, NULL);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		_sprite->Draw(
			*(image->GetTexture()),
			rect,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		free(rect);
		_sprite->End();
	}

	//if mirros is true the image should be mirrored over the y-axis
	void Graphics::DrawAnimation(Image* image, int xPos, int yPos, int imageIndex, int mirror)
	{
		D3DXVECTOR3 position;
		int direction;
		if (mirror)
		{
			position = D3DXVECTOR3((float)-xPos - image->GetXSize(), (float)yPos, 0.0f);
			direction = -1;
		}
		else
		{
			position = D3DXVECTOR3((float)xPos, (float)yPos, 0);
			direction = 1;
		}
		RECT* rect = new RECT();
		rect->top = 0;
		rect->bottom = image->GetYSize();
		rect->left = image->GetXSize()*imageIndex;
		rect->right = image->GetXSize()*(imageIndex + 1);
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX transformMatrix;
		D3DXMatrixScaling(&transformMatrix, (float)direction, 1.0f, 1.0f);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Draw(
			*(image->GetTexture()),
			rect,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		free(rect);
		_sprite->End();
	}

	void Graphics::DrawRotateImage(Image* image, int xPos, int yPos, double angle, int direction)
	{
		D3DXVECTOR3 position((float)xPos, (float)yPos, 0.0f);
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX transformMatrix;
		D3DXMatrixScaling(&transformMatrix, (float)direction, 1.0f, 1.0f);
		D3DXVECTOR2 center((float)xPos, (float)yPos);
		D3DXMatrixTransformation2D(&transformMatrix, NULL, NULL, NULL, &center, (float)angle, NULL);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Draw(
			*(image->GetTexture()),
			0,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		_sprite->End();
	}

	void Graphics::PrintText8(std::string text, int xPos, int yPos, D3DCOLOR color)
	{
		RECT rectangle = { xPos, yPos, 0, 0 };
		_font8->DrawText(
			0,
			text.c_str(),
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

	void Graphics::PrintText15(std::string text, int xPos, int yPos, D3DCOLOR color)
	{
		RECT rectangle = { xPos, yPos, 0, 0 };
		_font15->DrawText(
			0,
			text.c_str(),
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

	void Graphics::DrawRectangle(int xPos, int yPos, int xSize, int ySize, D3DCOLOR color)
	{
		Image* image = NULL;
		switch (color)
		{
		case WHITE:
		{
			image = &whitePixel;
			break;
		}
		case BLACK:
		{
			image = &blackPixel;
			break;
		}
		case RED:
		{
			image = &redPixel;
			break;
		}
		case BLUE:
		{
			image = &bluePixel;
			break;
		}
		case GREEN:
		{
			image = &greenPixel;
			break;
		}
		default:
			break;
		}
		D3DXVECTOR3 position((float)xPos / (float)xSize, (float)yPos / (float)ySize, 0.0f);
		_sprite->Begin(D3DXSPRITE_ALPHABLEND);
		D3DXMATRIX transformMatrix;
		D3DXMatrixScaling(&transformMatrix, (float)xSize, (float)ySize, 0.0f);
		_sprite->SetTransform(&transformMatrix);
		_sprite->Draw(
			*(image->GetTexture()),
			0,
			0,
			&position,
			D3DCOLOR_XRGB(255, 255, 255));
		_sprite->End();
	}
}
