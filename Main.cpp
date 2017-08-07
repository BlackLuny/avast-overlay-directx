#include "Main.h"

CDirectX * DirectX = new CDirectX();
CEngine * Engine = new CEngine();
CMain * Main = new CMain();
CProcess * Process = new CProcess();

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hInstancePrev, LPSTR CmdLine, int CmdShow)
{
	CFunction Function;

	Function.LoadConsole();

	if (!Function.IsAeroEnabled())
		Function.ShowMessage("To use this cheat you need to have Aero enabled.", "Error", MB_ICONERROR | MB_OK);
	
	if (!Engine->Attach("Untitled - Notepad"))
		Function.ShowMessage("Error while attaching to the target window!", "Error", MB_ICONERROR | MB_OK);

	if (!Engine->OpenTarget(Engine->Target, PROCESS_ALL_ACCESS))
		Function.ShowMessage("Error while open up the process!", "Error", MB_ICONASTERISK | MB_OK);

	Function.LoadMemoryFont(IDR_FONT0);
	Function.LoadMemoryFont(IDR_FONT1);
	Function.LoadMemoryFont(IDR_FONT2);
	Function.LoadMemoryFont(IDR_FONT3);

	Main->WindowClassEx.cbClsExtra = NULL;
	Main->WindowClassEx.cbSize = sizeof(WNDCLASSEX);
	Main->WindowClassEx.cbWndExtra = NULL;
	Main->WindowClassEx.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	Main->WindowClassEx.hCursor = LoadCursor(0, IDC_ARROW);
	Main->WindowClassEx.hIcon = LoadIcon(0, IDI_APPLICATION);
	Main->WindowClassEx.hIconSm = LoadIcon(0, IDI_APPLICATION);
	Main->WindowClassEx.hInstance = hInstance;
	Main->WindowClassEx.lpfnWndProc = WinProc;
	Main->WindowClassEx.lpszClassName = "Chrome";
	Main->WindowClassEx.lpszMenuName = "Chrome";
	Main->WindowClassEx.style = CS_HREDRAW | CS_VREDRAW;

	if (!RegisterClassEx(&Main->WindowClassEx))
		exit(1);

	Main->Window = CreateWindowEx(WS_EX_TOPMOST | WS_EX_LAYERED | WS_EX_TOOLWINDOW, Main->WindowClassEx.lpszClassName, Main->WindowClassEx.lpszMenuName, WS_POPUP, Engine->Position[0], Engine->Position[1], Engine->Size[0], Engine->Size[1], 0, 0, 0, 0);
	SetLayeredWindowAttributes(Main->Window, RGB(0, 0, 0), 255, LWA_COLORKEY | LWA_ALPHA);
	ShowWindow(Main->Window, SW_SHOW);

	MARGINS Margin = { -1, -1, -1, -1 };

	if (DwmExtendFrameIntoClientArea(Main->Window, &Margin) != S_OK)
		Function.ShowMessage("Cannot extend frame area of the window.", "Error", MB_ICONASTERISK | MB_OK);

	if (!DirectX->Initialize(Main->Window, Engine->Size[0], Engine->Size[1]))
		Function.ShowMessage("Cannot initialize DirectX3D. ", "Error", MB_ICONERROR | MB_OK);

	while (GetMessage(&Main->Message, 0, 0, 0))
	{
		TranslateMessage(&Main->Message);
		DispatchMessage(&Main->Message);	
	}

	return 0;
}

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
			Engine->GetSize();
			MoveWindow(Main->Window, Engine->Position[0], Engine->Position[1], Engine->Size[0], Engine->Size[1], false);
			DirectX->Render(Engine->IsWindowActive());
		break;
	case WM_SIZE:
			DirectX->Reset(Engine->Size[0], Engine->Size[1]);
		break;
	case WM_DESTROY:
			PostQuitMessage(1);
		break;
	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
	}
	return 0;
}
