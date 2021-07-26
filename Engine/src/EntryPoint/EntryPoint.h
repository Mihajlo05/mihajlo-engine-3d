#pragma once

#include "Application.h"
#include "Windows/GDIPlusManager.h"
#include "Gui/imgui/ImGuiManager.h"

extern Application* GetApplication();

int CALLBACK WinMain(
	HINSTANCE hInst,
	HINSTANCE hInstPrev,
	LPSTR	  lpCmdLine,
	int		  nCmdShow
)
{
	Application* pApp = nullptr;
	try
	{
		GDIPlusManager gpm;
		ImGuiManager igm;
		pApp = GetApplication();

		std::optional<int> ecode;

		while (!(ecode = Window::ProcessMessages()))
		{
			pApp->Go();
		}

		delete pApp;
		return *ecode;
	}
	catch (const MihajloException& e)
	{
		delete pApp;
		Window::CreateErrorMsgBox(e.GetType(), e.what());
	}
	catch (const std::exception& e)
	{
		delete pApp;
		Window::CreateErrorMsgBox("Standard Exception", e.what());
	}
	catch (...)
	{
		delete pApp;
		Window::CreateErrorMsgBox("Unknown Exception", "No details available");
	}

	return -1;
}