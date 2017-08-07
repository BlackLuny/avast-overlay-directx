#ifndef PROCESS_H
#define PROCESS_H

#include "Main.h"

class CProcess 
{
private:
	

public:
	HANDLE Handle;

	CProcess();
	bool Attach(HANDLE HandleId);
};
extern CProcess * Process;

#endif

