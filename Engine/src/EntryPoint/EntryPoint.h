#pragma once

#include "Application.h"
#include "Windows/GDIPlusManager.h"
#include "Gui/imgui/ImGuiManager.h"

extern std::unique_ptr<Application> GetApplication();

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	try
	{
		GDIPlusManager gpm;
		auto pApp = GetApplication();

		std::optional<int> ecode;

		while (!(ecode = Window::ProcessMessages()))
		{
			pApp->Go();
		}

		return *ecode;
	}
	catch (const MihajloException& e)
	{
		Window::CreateErrorMsgBox(e.GetType(), e.what());
	}
	catch (const std::exception& e)
	{
		Window::CreateErrorMsgBox("Standard Exception", e.what());
	}
	catch (...)
	{
		Window::CreateErrorMsgBox("Unknown Exception", "No details available");
	}

	return -1;
}