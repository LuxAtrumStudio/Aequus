#include "window.h"
#include "../sdl_headers.h"
#include "../framework.h"
#include "../../pessum_files/logging.h"

void aequus::video::Window::CreateWindow(std::string title, int x, int y, int width, int height, Uint32 flags)
{
	data.logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + title + "]");
	data.sdlwindow = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
	if (data.sdlwindow == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Unable to create SDL window: " + title, data.logloc, "CreateWindow");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Created new SDL window: " + title, data.logloc, "CreateWindow");
	}
}

void aequus::video::Window::TerminateWindow()
{
	SDL_DestroyWindow(data.sdlwindow);
	WindowData cleandata;
	data = cleandata;
}

void aequus::video::Window::SetHidden(bool hide)
{
	if (hide == true && data.hidden == false) {
		SDL_HideWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window to hide", data.logloc, "SetHidden");
	}
	else if (hide == false && data.hidden == true) {
		SDL_ShowWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window to show", data.logloc, "SetHidden");
	}
	data.hidden = hide;
}

void aequus::video::Window::Maximize()
{
	if (data.maximized != true) {
		SDL_MaximizeWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Maximized window", data.logloc, "Maximize");
	}
	data.maximized = true;
}

void aequus::video::Window::Minimize()
{
	if (data.minimized != true) {
		SDL_MinimizeWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Minimized window", data.logloc, "Minimize");
	}
	data.minimized = true;
}

void aequus::video::Window::Raise()
{
	SDL_RaiseWindow(data.sdlwindow);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Raised window", data.logloc, "Raise");
}

void aequus::video::Window::Restore()
{
	if (data.minimized == true || data.minimized == true) {
		SDL_RestoreWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Restored window position and size", data.logloc, "Restore");
	}
}

void aequus::video::Window::SetBordered(bool border)
{
}

void aequus::video::Window::SetBrightness(float brightness)
{
}

void aequus::video::Window::SetFullscreen(Uint32 flags)
{
}

void aequus::video::Window::SetGammaRamp(float red, float green, float blue)
{
}

void aequus::video::Window::SetGrab(bool grab)
{
}

void aequus::video::Window::SetIcon(std::string iconfiledirectory)
{
}

void aequus::video::Window::SetMaximumSize(int width, int height)
{
}

void aequus::video::Window::SetMinimumSize(int width, int height)
{
}

void aequus::video::Window::SetPosition(int x, int y)
{
}

void aequus::video::Window::SetSize(int width, int height)
{
}

void aequus::video::Window::SetTitle(std::string title)
{
}