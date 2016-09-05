#include "window.h"
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

namespace aequus {
	namespace video {
		namespace window {
			WindowData data;
			std::vector<MessageBox> messageboxes;
			Renderer render;
		}
	}
}
void aequus::video::window::CreateWindow(std::string title, int x, int y, int width, int height, Uint32 flags)
{
	data.logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + title + "]/");
	data.title = title;
	data.sdlwindow = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
	if (data.sdlwindow == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Unable to create SDL window: " + title, data.logloc, "CreateWindow");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Created new SDL window: " + title, data.logloc, "CreateWindow");
		SDL_GetWindowSurface(data.sdlwindow);
		render.CreateRenderer(data.sdlwindow, data.title, Renderer::ACCELERATED);
	}
}

void aequus::video::window::TerminateWindow()
{
	SDL_DestroyWindow(data.sdlwindow);
	WindowData cleandata;
	pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Terminated window: " + data.title, data.logloc, "TerminateWindow");
	data = cleandata;
}

void aequus::video::window::SetHidden(bool hide)
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

void aequus::video::window::Maximize()
{
	if (data.maximized != true) {
		SDL_MaximizeWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Maximized window", data.logloc, "Maximize");
	}
	data.maximized = true;
}

void aequus::video::window::Minimize()
{
	if (data.minimized != true) {
		SDL_MinimizeWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Minimized window", data.logloc, "Minimize");
	}
	data.minimized = true;
}

void aequus::video::window::Raise()
{
	SDL_RaiseWindow(data.sdlwindow);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Raised window", data.logloc, "Raise");
}

void aequus::video::window::Restore()
{
	if (data.minimized == true || data.minimized == true) {
		SDL_RestoreWindow(data.sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Restored window position and size", data.logloc, "Restore");
	}
}

void aequus::video::window::SetBordered(bool border)
{
	if (border == false && data.bordered == true) {
		SDL_SetWindowBordered(data.sdlwindow, SDL_FALSE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window border to false", data.logloc, "SetBordered");
	}
	else if (border == true && data.bordered == false) {
		SDL_SetWindowBordered(data.sdlwindow, SDL_TRUE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window border to true", data.logloc, "SetBordered");
	}
}

void aequus::video::window::SetBrightness(float brightness)
{
	if (SDL_SetWindowBrightness(data.sdlwindow, brightness) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window brightness", data.logloc, "SetBrightness");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window brightness", data.logloc, "SetBrightness");
	}
}

void aequus::video::window::SetFullscreen(Uint32 flags)
{
	if (SDL_SetWindowFullscreen(data.sdlwindow, flags) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window fullscreen", data.logloc, "SetFullscreen");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window fullscreen", data.logloc, "SetFullscreen");
	}
}

void aequus::video::window::SetGammaRamp(float red, float green, float blue)
{
	Uint16 r, g, b;
	r = (red * 255);
	g = (green * 255);
	b = (blue * 255);
	if (SDL_SetWindowGammaRamp(data.sdlwindow, &r, &g, &b) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window gamma ramp", data.logloc, "SetGammaRamp");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window gamma ramp", data.logloc, "SetGammaRamp");
	}
}

void aequus::video::window::SetGrab(bool grab)
{
	if (grab == true && data.grabbed == false) {
		SDL_SetWindowGrab(data.sdlwindow, SDL_TRUE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Grabbed window", data.logloc, "SetGrab");
	}
	else if (grab == false && data.grabbed == true) {
		SDL_SetWindowGrab(data.sdlwindow, SDL_FALSE);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Released window", data.logloc, "SetGrab");
	}
}

void aequus::video::window::SetIcon(std::string iconfiledirectory)
{
}

void aequus::video::window::SetMaximumSize(int width, int height)
{
	SDL_SetWindowMaximumSize(data.sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window maximum size: " + std::to_string(width) + "x" + std::to_string(height), data.logloc, "SetMaximumSize");
}

void aequus::video::window::SetMinimumSize(int width, int height)
{
	SDL_SetWindowMinimumSize(data.sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window minimum size: " + std::to_string(width) + "x" + std::to_string(height), data.logloc, "SetMinimumSize");
}

void aequus::video::window::SetPosition(int x, int y)
{
	SDL_SetWindowPosition(data.sdlwindow, x, y);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window position: (" + std::to_string(x) + "," + std::to_string(y) + ")", data.logloc, "SetPosition");
}

void aequus::video::window::SetSize(int width, int height)
{
	SDL_SetWindowSize(data.sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window size: " + std::to_string(width) + "x" + std::to_string(height), data.logloc, "SetSize");
}

void aequus::video::window::SetTitle(std::string title)
{
	SDL_SetWindowTitle(data.sdlwindow, title.c_str());
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window title: " + data.title + " to: " + title, data.logloc, "SetTitle");
	data.title = title;
}

void aequus::video::window::Update()
{
	//render.Update();
	if (SDL_UpdateWindowSurface(data.sdlwindow) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to update window surface", data.logloc, "Update");
		framework::SdlError();
	}
}