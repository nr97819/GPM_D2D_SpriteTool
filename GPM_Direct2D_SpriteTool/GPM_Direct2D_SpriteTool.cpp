
#include <windows.h>

#include "CToolApp.h"

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int msg = {};
	CToolApp toolApp;

	if (SUCCEEDED(toolApp.Init(hInstance, nCmdShow)))
	{
		msg = toolApp.RunLoop();
	}
	toolApp.Release();

	return msg;
}

