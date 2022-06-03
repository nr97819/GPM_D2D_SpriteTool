
#include <windows.h>

#include "ToolApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int msg = {};
	SWCToolApp toolApp;

	if (SUCCEEDED(toolApp.Init(hInstance, nCmdShow)))
	{
		msg = toolApp.RunLoop();
	}
	toolApp.Release();

	return msg;
}

