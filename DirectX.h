#ifndef DIRECTX_H
#define DIRECTX_H

#include "Main.h"

class CDirectX
{
private:
	ID3DXFont * Font;
	ID3DXLine * LinePtr;
	IDirect3D9 * Direct3D;	
	IDirect3DDevice9 * Direct3DDevice;
	D3DPRESENT_PARAMETERS Parameters;
	
public: 
	D3DVIEWPORT9 Viewport; /* if problems happen FLOAT TO DWORD in d3d9types.h */


public:
	CDirectX();
	bool Initialize(HWND hWindow, int Width, int Heigth);
	void Render(bool Active);
	void Reset(int Width, int Heigth);

	

	

public:
	void String(char * szString, float X, float Y, int R, int G, int B, int A, bool Centered = 0);
	void Line(float X, float Y, float X2, float Y2, int R, int G, int B, int A);
};

extern CDirectX * DirectX;

#endif