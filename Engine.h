#ifndef ENGINE_H
#define ENGINE_H

#include "Main.h"

class CEngine
{
public:
	HWND Target;
	RECT WindowRect;
	int Size[2];
	int Position[2];

	int oldSize[2];

public:
	CEngine();
	bool Attach(char * targetName);
	bool GetSize();
	bool IsWindowActive();
};

#endif