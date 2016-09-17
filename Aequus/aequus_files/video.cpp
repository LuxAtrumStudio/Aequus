#include "video.h"
#include "aequus_headers.h"
#include "../pessum_files/logging.h"

namespace aequus {
	namespace video {
		int logloc = 0;
		std::vector<WindowData>windows;
		int boundwindow = 0;
		int boundobj = 0;
		std::string globalresourcedir = "resources/";
		std::vector<MessageBox> messageboxes;
		WindowData* win = NULL;
	}
}
void aequus::video::CreateWindow(std::string title, int width, int height, int x, int y, Uint32 flags)
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
		draw::InitializeDraw(newwindow.windowrenderer.sdlrenderer);
		newwindow.sizex = width;
		newwindow.sizey = height;
		windows.push_back(newwindow);
		BindWindow(windows.size() - 1);
	}
}

void aequus::video::TerminateWindow(int pointer)
{
	SDL_DestroyWindow(windows[pointer].sdlwindow);
	WindowData cleandata;
	pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Terminated window: " + windows[pointer].title, windows[pointer].logloc, "TerminateWindow");
	windows[pointer] = cleandata;
}

void aequus::video::SetHidden(bool hide, int pointer)
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

void aequus::video::Maximize(int pointer)
{
	if (windows[pointer].maximized != true) {
		SDL_MaximizeWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Maximized window", windows[pointer].logloc, "Maximize");
	}
	windows[pointer].maximized = true;
}

void aequus::video::Minimize(int pointer)
{
	if (windows[pointer].minimized != true) {
		SDL_MinimizeWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Minimized window", windows[pointer].logloc, "Minimize");
	}
	windows[pointer].minimized = true;
}

void aequus::video::Raise(int pointer)
{
	SDL_RaiseWindow(windows[pointer].sdlwindow);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Raised window", windows[pointer].logloc, "Raise");
}

void aequus::video::Restore(int pointer)
{
	if (windows[pointer].minimized == true || windows[pointer].minimized == true) {
		SDL_RestoreWindow(windows[pointer].sdlwindow);
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Restored window position and size", windows[pointer].logloc, "Restore");
	}
}

void aequus::video::SetBordered(bool border, int pointer)
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

void aequus::video::SetBrightness(float brightness, int pointer)
{
	if (SDL_SetWindowBrightness(windows[pointer].sdlwindow, brightness) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window brightness", windows[pointer].logloc, "SetBrightness");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window brightness", windows[pointer].logloc, "SetBrightness");
	}
}

void aequus::video::SetFullscreen(Uint32 flags, int pointer)
{
	if (SDL_SetWindowFullscreen(windows[pointer].sdlwindow, flags) < 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set window fullscreen", windows[pointer].logloc, "SetFullscreen");
		framework::SdlError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Set window fullscreen", windows[pointer].logloc, "SetFullscreen");
	}
}

void aequus::video::SetGammaRamp(float red, float green, float blue, int pointer)
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

void aequus::video::SetGrab(bool grab, int pointer)
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

void aequus::video::SetIcon(std::string iconfiledirectory, int pointer)
{
}

void aequus::video::SetMaximumSize(int width, int height, int pointer)
{
	SDL_SetWindowMaximumSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window maximum size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetMaximumSize");
}

void aequus::video::SetMinimumSize(int width, int height, int pointer)
{
	SDL_SetWindowMinimumSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window minimum size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetMinimumSize");
}

void aequus::video::SetPosition(int x, int y, int pointer)
{
	SDL_SetWindowPosition(windows[pointer].sdlwindow, x, y);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window position: (" + std::to_string(x) + "," + std::to_string(y) + ")", windows[pointer].logloc, "SetPosition");
}

void aequus::video::SetSize(int width, int height, int pointer)
{
	SDL_SetWindowSize(windows[pointer].sdlwindow, width, height);
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window size: " + std::to_string(width) + "x" + std::to_string(height), windows[pointer].logloc, "SetSize");
}

void aequus::video::SetTitle(std::string title, int pointer)
{
	SDL_SetWindowTitle(windows[pointer].sdlwindow, title.c_str());
	pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Set window title: " + windows[pointer].title + " to: " + title, windows[pointer].logloc, "SetTitle");
	windows[pointer].title = title;
}

void aequus::video::Update(bool persistent, int pointer)
{
	if (persistent == false) {
		windows[pointer].windowrenderer.Clear();
	}
	for (unsigned a = 0; a < windows[pointer].objects.size(); a++) {
		windows[pointer].objects[a].DisplayObj();
	}
	windows[pointer].windowrenderer.Update();
}

void aequus::video::UpdateAll(bool persistent)
{
	for (unsigned a = 0; a < windows.size(); a++) {
		Update(persistent, a);
	}
}

void aequus::video::BindWindow(int pointer)
{
	if (pointer < windows.size()) {
		win = &windows[pointer];
		boundwindow = pointer;
	}
}

bool aequus::video::AllClose()
{
	if (windows.size() == 0) {
		return(true);
	}
	else {
		return(false);
	}
}

void aequus::video::NewObject(int pointer) {
	Object newobject;
	newobject.InitalizeObj(windows[pointer].windowrenderer.sdlrenderer, windows[pointer].objects.size(), globalresourcedir);
	windows[boundwindow].objects.push_back(newobject);
	boundobj = windows[boundwindow].objects.size() - 1;
	windows[boundwindow].obj = &windows[boundwindow].objects[boundobj];
}

void aequus::video::BindObject(int pointer)
{
	if (pointer < windows[boundwindow].objects.size()) {
		boundobj = pointer;
		windows[boundwindow].obj = &windows[boundwindow].objects[boundobj];
	}
}

void aequus::video::Bind(int windowpointer, int objectpointer)
{
	BindWindow(windowpointer);
	BindObject(objectpointer);
}

void aequus::video::SetScreenSaver(bool screensaver)
{
	if (screensaver == true) {
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Enabled screen saver", logloc, "SetScreenSaver");
		SDL_EnableScreenSaver();
	}
	else if (screensaver == false) {
		pessum::logging::LogLoc(pessum::logging::LOG_INFORMATION, "Disabled screen saver", logloc, "SetScreenSaver");
		SDL_DisableScreenSaver();
	}
}