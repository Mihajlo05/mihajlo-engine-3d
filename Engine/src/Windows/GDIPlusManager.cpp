#define NO_SWITCHES
#include "MihajloWin.h"
#include "GDIPlusManager.h"

/* gdiplus needs min/max, but we disabled that (even in
 full no switches mode), so we need to inject min/max into
 the Gdiplus namespace */
#include <algorithm>
namespace Gdiplus
{
	using std::min;
	using std::max;
}
#include <gdiplus.h>

#pragma comment( lib,"gdiplus.lib" )

ULONG_PTR GDIPlusManager::token = 0;
int GDIPlusManager::refCount = 0;

GDIPlusManager::GDIPlusManager()
{
	if (refCount++ == 0)
	{
		Gdiplus::GdiplusStartupInput input;
		input.GdiplusVersion = 1;
		input.DebugEventCallback = nullptr;
		input.SuppressBackgroundThread = false;
		Gdiplus::GdiplusStartup(&token, &input, nullptr);
	}
}

GDIPlusManager::~GDIPlusManager()
{
	if (--refCount == 0)
	{
		Gdiplus::GdiplusShutdown(token);
	}
}