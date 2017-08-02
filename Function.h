#ifndef FUNCTION_H
#define FUNCTION_H

#include "Main.h"

class CFunction
{
public:
	bool IsAeroEnabled(void);
	void ShowMessage(char * Message, char * Caption, UINT Type);
	void LoadMemoryFont(int fontId);
	void LoadConsole();
	char * RandomString(int stringSize);
};

#endif