#include "window.h"
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

namespace aequus {
	namespace video {
		namespace window {
			std::vector<WindowData>windows;
			int boundwindow = 0;
			std::vector<MessageBox> messageboxes;
		}
	}
}
void aequus::video::window::CreateWindow(std::string title, int x, int y, int width, int height, Uint32 flags)
{
	WindowData newwindow;
	newwindow.logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + title + "]/");
	newwindow.title = title;
	newwindow.sdlwindow = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
	if (newwindow.sdlwindow == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Unable to create SDL window: " + title, newwindow.logloc, "CreateWindow");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Created new SDL window: " + title, newwindow.logloc, "CreateWindow");
		SDL_GetWindowSurface(newwindow.sdlwindow);
		newwindow.windowrenderer.CreateRenderer(newwindow.sdlwindow, newwindow.title, Renderer::ACCELERATED);
		windows.push_back(newwindow);
		BindWindow(windows.size() - 1);
	}
}

void aequus::video::window::TerminateWindow(int pointer)
{
	SDL_DestroyWindow(windows[pointer].sdlwindow);
	WindowData cleandata;
	pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Terminated window: " + windows[pointer].title, windows[pointer].logloc, "TerminateWindow");
	windows[pointer] = cleandata;
}

void aequus::video::window::SetHidden(bool hide, int pointer)
{
	if (hide == true && windows[pointer].hidden == false) {
		SDL_HideWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window to hide", windows[pointer].logloc, "SetHidden");
	}
	else if (hide == false && windows[pointer].hidden == true) {
		SDL_ShowWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window to show", windows[pointer].logloc, "SetHidden");
	}
	windows[pointer].hidden = hide;
}

void aequus::video::window::Maximize(int pointer)
{
	if (windows[pointer].maximized != true) {
		SDL_MaximizeWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Maximized window", windows[pointer].logloc, "Maximize");
	}
	windows[pointer].maximized = true;
}

void aequus::video::window::Minimize(int pointer)
{
	if (windows[pointer].minimized != true) {
		SDL_MinimizeWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Minimized window", windows[pointer].logloc, "Minimize");
	}
	windows[pointer].minimized = true;
}

void aequus::video::window::Raise(int pointer)
{
	SDL_RaiseWindow(windows[pointer].sdlwindow);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Raised window", windows[pointer].logloc, "Raise");
}

void aequus::video::window::Restore(int pointer)
{
	if (windows[pointer].minimized == true || windows[pointer].minimized == true) {
		SDL_RestoreWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Restored window position and size", windows[pointer].logloc, "Restore");
	}
}

void aequus::video::window::SetBordered(bool border, int pointer)
{
	if (border == false && windows[pointer].bordered == true) {
		SDL_SetWindowBordered(windows[pointer].sdlwindow, SDL_FALSE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window border to false", windows[pointer].logloc, "SetBordered");
	}
	else if (border == true && windows[pointer].bordered == false) {
		SDL_SetWindowBordered(windows[pointer].sdlwindow, SDL_TRUE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window border to true", windows[pointer].logloc, "SetBordered");
	}
}

void aequus::video::window::SetBrightness(float brightness, int pointer)
{
	if (SDL_SetWindowBrightness(windows[pointer].sdlwindow, brightness) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window brightness", windows[pointer].logloc, "SetBrightness");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window brightness", windows[pointer].logloc, "SetBrightness");
	}
}

void aequus::video::window::SetFullscreen(Uint32 flags, int pointer)
{
	if (SDL_SetWindowFullscreen(windows[pointer].sdlwindow, flags) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window fullscreen", windows[pointer].logloc, "SetFullscreen");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window fullscreen", windows[pointer].logloc, "SetFullscreen");
	}
}

void aequus::video::window::SetGammaRamp(float red, float green, float blue, int pointer)
{
	Uint16 r, g, b;
	r = (red * 255);
	g = (green * 255);
	b = (blue * 255);
	if (SDL_SetWindowGammaRamp(windows[pointer].sdlwindow, &r, &g, &b) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window gamma ramp", windows[pointer].logloc, "SetGammaRamp");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window gamma ramp", windows[pointer].logloc, "SetGammaRamp");
	}
}

void aequus::video::window::SetGrab(bool grab, int pointer)
{
	if (grab == true && windows[pointer].grabbed == false) {
		SDL_SetWindowGrab(windows[pointer].sdlwindow, SDL_TRUE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Grabbed window", windows[pointer].logloc, "SetGrab");
	}
	else if (grab == false && windows[pointer].grabbed == true) {
		SDL_SetWindowGrab(windows[pointer].sdlwindow, SDL_FALSE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Released window", windows[pointer].logloc, "SetGrab");
	}
}

void aequus::video::window::SetIcon(std::string iconfiledirectory, int pointer)
{
}

void aequus::video::window::SetMaximumSize(int width, int height, int pointer)
{
	SDL_SetWindowMaximumSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window maximum size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetMaximumSize");
}

void aequus::video::window::SetMinimumSize(int width, int height, int pointer)
{
	SDL_SetWindowMinimumSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window minimum size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetMinimumSize");
}

void aequus::video::window::SetPosition(int x, int y, int pointer)
{
	SDL_SetWindowPosition(windows[pointer].sdlwindow, x, y);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window position: (" + std::to_string(x) + "," + std::to_string(y) + ")", windows[pointer].logloc, "SetPosition");
}

void aequus::video::window::SetSize(int width, int height, int pointer)
{
	SDL_SetWindowSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetSize");
}

void aequus::video::window::SetTitle(std::string title, int pointer)
{
	SDL_SetWindowTitle(windows[pointer].sdlwindow, title.c_str());
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window title: " + windows[pointer].title + " to: " + title, windows[pointer].logloc, "SetTitle");
	windows[pointer].title = title;
}

void aequus::video::window::Update(int pointer)
{
	if (SDL_UpdateWindowSurface(windows[pointer].sdlwindow) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to update window surface", windows[pointer].logloc, "Update");
		framework::SdlError();
	}
}

void aequus::video::window::BindWindow(int pointer)
{
	if (pointer < windows.size()) {
		boundwindow = pointer;
	}
}