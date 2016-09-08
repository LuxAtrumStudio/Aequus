#include "surface.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::window::Surface::LoadSurface(std::string filepath)
{
	filepath = surfacefilepath;
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[" + filepath + "]/");
	sdlsurface = IMG_Load(filepath.c_str());
	if (sdlsurface == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to load image file", logloc, "LoadSurface");
		framework::GetError(2);
	}
	else {
		width = sdlsurface->w;
		height = sdlsurface->h;
		source = { 0, 0, 0, 0 };
		destination = { 0, 0, 0, 0 };
		colormod = { 1, 1, 1, 1 };
		ConvertRectangles();
		SetSurfaceColor();
		blendmode = BLEND;
	}
}

std::string aequus::video::window::Surface::GetSurfaceFilePath()
{
	if (sdlsurface != NULL) {
		return surfacefilepath;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetSurfaceFilePath");
		return("NULL");
	}
}

void aequus::video::window::Surface::SetSourceRectangle(Rectangle srcrect)
{
	source = srcrect;
	ConvertRectangles();
}

aequus::video::window::Surface::Rectangle aequus::video::window::Surface::GetSourceRectangle()
{
	if (sdlsurface != NULL) {
		return source;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetSourceRectangle");
		Rectangle null = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::window::Surface::SetDestinationRectangle(Rectangle destrect)
{
	destination = destrect;
	ConvertRectangles();
}

aequus::video::window::Surface::Rectangle aequus::video::window::Surface::GetDestinationRectangle()
{
	if (sdlsurface != NULL) {
		return destination;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetDestinationRectangle");
		Rectangle null = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::window::Surface::SetColorMod(Color mod)
{
	if (sdlsurface != NULL) {
		colormod = mod;
		SetSurfaceColor();
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "SetColorMod");
	}
}

aequus::video::window::Surface::Color aequus::video::window::Surface::GetColorMode()
{
	if (sdlsurface != NULL) {
		return colormod;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetColorMod");
		Color null = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::window::Surface::SetBlendMode(BlendMode mode)
{
	if (sdlsurface != NULL) {
		blendmode = mode;
		SetSurfaceBlend();
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "SetBlendMode");
	}
}

aequus::video::window::Surface::BlendMode aequus::video::window::Surface::GetBlendMode()
{
	if (sdlsurface != NULL) {
		return blendmode;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetBlendMode");
		BlendMode null = NONE;
		return(null);
	}
}

aequus::video::window::Surface::Pair aequus::video::window::Surface::GetSize()
{
	if (sdlsurface != NULL) {
		Pair size = { width, height };
		return(size);
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetSize");
		Pair null = { 0, 0 };
		return(null);
	}
}

void aequus::video::window::Surface::Terminate()
{
	if (sdlsurface != NULL) {
		SDL_FreeSurface(sdlsurface);
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "Terminate");
	}
}

void aequus::video::window::Surface::ConvertRectangles()
{
	if (source.width == 0 || source.height == 0) {
		sourcerect = NULL;
	}
	else {
		sourcerect->h = source.height;
		sourcerect->w = source.width;
		sourcerect->x = source.x;
		sourcerect->y = source.y;
	}
	if (destination.height == 0 || destination.width == 0) {
		destinationrect = NULL;
	}
	else {
		destinationrect->h = destination.height;
		destinationrect->w = destination.width;
		destinationrect->x = destination.x;
		destinationrect->y = destination.y;
	}
}

void aequus::video::window::Surface::SetSurfaceColor()
{
	if (SDL_SetSurfaceColorMod(sdlsurface, colormod.red * 255, colormod.green * 255, colormod.blue * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set surface color mod", logloc, "SetSurfaceColor");
		framework::GetError();
	}
	if (SDL_SetSurfaceAlphaMod(sdlsurface, colormod.alpha) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set surface alpha mod", logloc, "SetSurfaceColor");
		framework::GetError();
	}
}

void aequus::video::window::Surface::SetSurfaceBlend()
{
	SDL_BlendMode sdlblendmode = SDL_BLENDMODE_NONE;
	if (blendmode == BLEND) {
		sdlblendmode = SDL_BLENDMODE_BLEND;
	}
	else if (blendmode == ADD) {
		sdlblendmode = SDL_BLENDMODE_ADD;
	}
	else if (blendmode == MOD) {
		sdlblendmode = SDL_BLENDMODE_MOD;
	}
	if (SDL_SetSurfaceBlendMode(sdlsurface, sdlblendmode) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set surface blend mode", logloc, "SetSurfaceBlend");
		framework::GetError();
	}
}