#include "Drawing.h"

CDrawing::CDrawing()
{

}
/*
public const long Entity = 0x1948; // --
public const long ItemEntity = 0x6B0; //--
public const long ItemPos = 0x19D0; // --
public const long Count = 0x60; //--
public const long Next = 0x6C0; // 0x6A8
public const long Type = 0x3E8; // --
public const long Stance = 0x8E0; //--
public const long Id = 0x888; //--
public const long Name = 0x730; // 0x740
public const long NameLength = 0x748; // --
public const long Alive = 0x1c08; // 0x1b98
public const long Yaw = 0x520;


*/
void CDrawing::Draw()
{
	DirectX->String("- BIGZANE HAT EINEN KLEINEN PENIS -", ((FLOAT)DirectX->Viewport.Width / 2), 0, 255, 255, 0, 255, true);
	Crosshair();

	Vector3 Position;
	Position.x = 0;
	Position.y = 0;
	Position.z = 0;

}


void CDrawing::Crosshair()
{
	D3DXVECTOR2 Screen((FLOAT)DirectX->Viewport.Width / 2, (FLOAT)DirectX->Viewport.Height / 2);

	DirectX->Line(Screen.x + 5, Screen.y, Screen.x - 5, Screen.y, 255, 255, 0, 255);
	DirectX->Line(Screen.x, Screen.y + 5, Screen.x, Screen.y - 5, 255, 255, 0, 255);
}
