#include "Engine.h"

CEngine::CEngine()
{
	this->Size[0] = NULL;
	this->Size[1] = NULL;

	this->Target = NULL;
}

bool CEngine::Attach(char * targetName)
{
	Target = FindWindow(NULL, targetName);

	if (!Target)
		return false;

	if (!GetSize())
		return false;

	return true;
}

bool CEngine::OpenTarget(HWND wndTarget, DWORD Access)
{
	DWORD dwProcess;
	
	GetWindowThreadProcessId(wndTarget, &dwProcess);
	Handle = OpenProcess(Access, NULL, dwProcess);

	if (!Handle)
		return false;

	return true;
}

bool CEngine::GetSize()
{
	if (!GetWindowRect(Target, &WindowRect))
		exit(1);
	
	Size[0] = WindowRect.right - WindowRect.left;
	Size[1] = WindowRect.bottom - WindowRect.top;

	Position[0] = WindowRect.left;
	Position[1] = WindowRect.top;

	return true;
}

bool CEngine::IsWindowActive()
{
	HWND ActiveWindow = GetForegroundWindow();

	if (ActiveWindow != Target)
		return false;

	return true;
}