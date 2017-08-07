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
