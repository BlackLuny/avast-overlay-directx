#include "DirectX.h"

CDrawing * Drawing = new CDrawing();

CDirectX::CDirectX()
{
	this->Direct3D = nullptr;
	this->Direct3DDevice = nullptr;
	this->Font = nullptr;
}

bool CDirectX::Initialize(HWND hWindow, int Width, int Heigth)
{
	ZeroMemory(&Parameters, sizeof(Parameters));

	Parameters.EnableAutoDepthStencil = TRUE;
	Parameters.AutoDepthStencilFormat = D3DFMT_D16;
	Parameters.Windowed = TRUE;
	Parameters.BackBufferCount = 1;
	Parameters.BackBufferFormat = D3DFMT_A8R8G8B8;
	Parameters.BackBufferWidth = Width;
	Parameters.BackBufferHeight = Heigth;
	Parameters.MultiSampleType = D3DMULTISAMPLE_NONE;
	Parameters.SwapEffect = D3DSWAPEFFECT_DISCARD;
	Parameters.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;
	Parameters.hDeviceWindow = hWindow;


	Direct3D = Direct3DCreate9(D3D_SDK_VERSION);

	if (!Direct3D)
		return false;

	if (FAILED(Direct3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWindow, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &Parameters, &Direct3DDevice)))
		return false;

	if (!Direct3DDevice)
		return false;

	return true;
}

void CDirectX::Render(bool Active)
{
	if(Direct3DDevice)
	{ 
		Direct3DDevice->Clear(NULL, NULL, D3DCLEAR_TARGET, NULL, 1.0f, NULL);
		Direct3DDevice->BeginScene();
	
		if(Active)
		{ 
			Direct3DDevice->GetViewport(&Viewport);

			Drawing->Draw(); 
		}

		Direct3DDevice->EndScene();
		Direct3DDevice->Present(NULL, NULL, NULL, NULL);
	}
}

void CDirectX::Reset(int Width, int Heigth)
{
	if (Direct3DDevice)
	{
		if (Font)
		{
			Font->Release();
			Font = NULL;
		}

		if (LinePtr)
		{
			LinePtr->Release();
			LinePtr = NULL;
		}

		Parameters.BackBufferWidth = Width;
		Parameters.BackBufferHeight = Heigth;
		Direct3DDevice->Reset(&Parameters);
	}
}

void CDirectX::String(char * szString, float X, float Y, int R, int G, int B, int A, bool Centered)
{
	if (!Font)
	{	
		D3DXCreateFont(Direct3DDevice, 25, 0, 0, 0, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, "leon", &Font);
	}
	else
	{
		RECT Center = { 0, 0, 0, 0 }, Position = { 0, 0, 0, 0 };

		if (Centered)
			Font->DrawTextA(0, szString, (INT)strlen(szString), &Center, DT_CALCRECT, NULL);
		
		Position.left = ((LONG)X + 1) - (Center.right / 2);
		Position.top = ((LONG)Y + 1);
		Font->DrawTextA(0, szString, (INT)strlen(szString), &Position, DT_NOCLIP, D3DCOLOR_ARGB(A, 0, 0, 0));

		Position.left = (LONG)X - (Center.right / 2);
		Position.top = (LONG)Y;
		Font->DrawTextA(0, szString, (INT)strlen(szString), &Position, DT_NOCLIP, D3DCOLOR_ARGB(A, R, G, B));
	}
}

void CDirectX::Line(float X, float Y, float X2, float Y2, int R, int G, int B, int A)
{
	if (!LinePtr)
		D3DXCreateLine(Direct3DDevice, &LinePtr);

	D3DXVECTOR2 Vertex[2];
	Vertex[0].x = X;
	Vertex[0].y = Y;
	Vertex[1].x = X2;
	Vertex[1].y = Y2;

	LinePtr->Draw(Vertex, 2, D3DCOLOR_ARGB(A, R, G, B));
}