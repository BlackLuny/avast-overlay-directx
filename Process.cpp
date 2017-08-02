#include "Process.h"

CProcess::CProcess()
{
	Handle = INVALID_HANDLE_VALUE;
}

bool CProcess::Attach(HANDLE HandleId)
{
	Handle = HandleId;

	printf("Handle: 0x%X\n", HandleId);

	if(Handle == nullptr)
		return false;
	else
		return true;
}

//Credits to uc.
bool CProcess::WorldToScreen(const Vector3& vIn, float * ScreenX, float * ScreenY)
{
	DWORD_PTR Graphics;
	ReadProcessMemory(Handle, (LPCVOID)0x144FB1B30, &Graphics, sizeof(DWORD_PTR), NULL);

	DWORD_PTR Camera;
	ReadProcessMemory(Handle, (LPCVOID)(Graphics + 0x48), &Camera, sizeof(DWORD_PTR), NULL);
	
	DWORD_PTR CameraMatrix;
	ReadProcessMemory(Handle, (LPCVOID)(Camera + 0x30), &CameraMatrix, sizeof(DWORD_PTR), NULL);

	CameraMatrix += 0x10;

	int ScreenWidth = 1920;
	int ScreenHeight = 1080;

	D3DXMATRIX Matrix;
	ReadProcessMemory(Handle, (LPCVOID)(CameraMatrix + 0x1A0), &Matrix, sizeof(D3DXMATRIX), NULL);

	D3DXMatrixTranspose(&Matrix, &Matrix);

	Matrix4x4 vMatrix = *(Matrix4x4*)&Matrix;

	vMatrix._21 *= -1;
	vMatrix._22 *= -1;
	vMatrix._23 *= -1;
	vMatrix._24 *= -1;

	float w = vMatrix.GetAxis(3).Dot(vIn) + vMatrix.m[3][3];

	if (w < 0.098) {
		return false;
	}

	float x = vMatrix.GetAxis(0).Dot(vIn) + vMatrix.m[0][3];
	float y = vMatrix.GetAxis(1).Dot(vIn) + vMatrix.m[1][3];

	*ScreenX = (ScreenWidth / 2) * (1.0 + x / w);
	*ScreenY = (ScreenHeight / 2) * (1.0 - y / w);

	return true;
}

