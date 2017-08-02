#include "Function.h"

bool CFunction::IsAeroEnabled(void)
{
	BOOL bEnabled = false;

	if (DwmIsCompositionEnabled(&bEnabled) != S_OK)
		return false;

	if (bEnabled)
		return true;
	else
		return false;
}

void CFunction::ShowMessage(char * Message, char * Caption, UINT Type)
{
	MessageBox(0, Message, Caption, Type);
	exit(1);
}

void CFunction::LoadMemoryFont(int fontId)
{
	HRSRC ResourceHandle = FindResource(NULL, MAKEINTRESOURCE(fontId), RT_RCDATA);
	HGLOBAL ResourceFile = LoadResource(NULL, ResourceHandle);
	void * CustomFont = LockResource(ResourceFile);
	int Size = SizeofResource(NULL, ResourceHandle);

	DWORD FontNum;
	AddFontMemResourceEx(CustomFont, Size, NULL, &FontNum);
}

void CFunction::LoadConsole()
{
	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
}

char * CFunction::RandomString(int stringSize)
{
	char Buffer[128];
	char Characters[] = "ABCDEFGHIJKLMNOPQRSTUVXYZ0123456789!?";
	
	for (int i = 0; i < stringSize; i++)
	{
		int Random = rand() % (strlen(Characters));
		Buffer[i] = Characters[Random];
	}

	Buffer[stringSize + 1] = '\0';

	printf_s("%s", Buffer);

	return Buffer;
}