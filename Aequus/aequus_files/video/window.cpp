#include "window.h"
#include "../sdl_headers.h"
#include "../framework.h"
#include "../../pessum_files/logging.h"

void aequus::video::Window::CreateWindow(std::string title, int x, int y, int width, int height, Uint32 flags)
{
	windowvars.logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + title + "]");
	windowvars.sdlwindow = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
	if (windowvars.sdlwindow == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Unable to create SDL window: " + title);
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Created new SDL window: " + title);
	}
}

void aequus::video::Window::TerminateWindow()
{
	SDL_DestroyWindow(windowvars.sdlwindow);
	WindowData cleandata;
	windowvars = cleandata;
}