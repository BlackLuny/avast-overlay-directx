#include "Drawing.h"

CDrawing::CDrawing()
{

}

void CDrawing::Draw()
{
	DirectX->String("- Unknowncheats Overlaybase by Grab -", ((FLOAT)DirectX->Viewport.Width / 2), 0, 255, 255, 0, 255, true);
	Crosshair();
}


void CDrawing::Crosshair()
{
	D3DXVECTOR2 Screen((FLOAT)DirectX->Viewport.Width / 2, (FLOAT)DirectX->Viewport.Height / 2);

	DirectX->Line(Screen.x + 5, Screen.y, Screen.x - 5, Screen.y, 255, 255, 0, 255);
	DirectX->Line(Screen.x, Screen.y + 5, Screen.x, Screen.y - 5, 255, 255, 0, 255);
}
