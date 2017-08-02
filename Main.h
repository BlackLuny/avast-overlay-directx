#ifndef MAIN_H
#define MAIN_H
#define _CRT_SECURE_NO_WARNINGS

#include <Windows.h>
#include <windef.h>
#include <dwmapi.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <stdio.h>

#include "Function.h"
#include "DirectX.h"
#include "Engine.h"
#include "resource.h"
#include "Drawing.h"
#include "Process.h"

#pragma once
#pragma comment(lib, "dwmapi.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR CmdLine, int CmdShow);

class CMain
{
public:
	HWND Window;
	WNDCLASSEX WindowClassEx;
	MSG Message;
};


#endif