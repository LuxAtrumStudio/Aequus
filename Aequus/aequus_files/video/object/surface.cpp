#include "surface.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/pessum_headers.h"

void aequus::video::Surface::LoadSurface(std::string filepath)
{
	surfacefilepath = filepath;
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface.cpp[" + filepath + "]/");
	sdlsurface = IMG_Load(filepath.c_str());
	if (sdlsurface == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to load image file", logloc, "LoadSurface");
		framework::GetError(2);
	}
	else {
		width = sdlsurface->w;
		height = sdlsurface->h;
		source[0] = width;
		source[1] = height;
		source[2] = 0;
		source[3] = 0;
		destination[0] = width;
		destination[1] = height;
		destination[2] = 0;
		destination[3] = 0;
		colormod[0] = 1;
		colormod[1] = 1;
		colormod[2] = 1;
		colormod[3] = 1;
		ConvertRectangles();
		SetSurfaceColor();
		blendmode = BLEND;
	}
}

std::string aequus::video::Surface::GetSurfaceFilePath()
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

void aequus::video::Surface::SetSourceRectangle(int rectangle[4])
{
	for (int a = 0; a < 4; a++) {
		source[a] = rectangle[a];
	}
	ConvertRectangles();
}

int* aequus::video::Surface::GetSourceRectangle()
{
	if (sdlsurface != NULL) {
		return source;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetSourceRectangle");
		int null[4] = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::Surface::SetDestinationRectangle(int rectangle[4])
{
	for (int a = 0; a < 4; a++) {
		destination[a] = rectangle[a];
	}
	ConvertRectangles();
}

int* aequus::video::Surface::GetDestinationRectangle()
{
	if (sdlsurface != NULL) {
		return destination;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetDestinationRectangle");
		int null[4] = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::Surface::SetColorMod(double color[4])
{
	if (sdlsurface != NULL) {
		for (int a = 0; a < 4; a++) {
			colormod[a] = color[a];
		}
		SetSurfaceColor();
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "SetColorMod");
	}
}

double* aequus::video::Surface::GetColorMode()
{
	if (sdlsurface != NULL) {
		return colormod;
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetColorMod");
		double null[4] = { 0, 0, 0, 0 };
		return(null);
	}
}

void aequus::video::Surface::SetBlendMode(BlendMode mode)
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

aequus::video::Surface::BlendMode aequus::video::Surface::GetBlendMode()
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

int* aequus::video::Surface::GetSize()
{
	if (sdlsurface != NULL) {
		int size[2] = { width, height };
		return(size);
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "GetSize");
		int null[2] = { 0, 0 };
		return(null);
	}
}

void aequus::video::Surface::Terminate()
{
	if (sdlsurface != NULL) {
		SDL_FreeSurface(sdlsurface);
	}
	else {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/object/surface[NULL]/");
		pessum::logging::LogLoc(pessum::logging::LOG_WARNING, "Surface has not been created", logloc, "Terminate");
	}
}

void aequus::video::Surface::ConvertRectangles()
{
	if (source[0] == 0 || source[0] == 0) {
		sourcerect = NULL;
	}
	else {
		if (sourcerect == NULL) {
			SDL_Rect null;
			null = { 0 , 0, 0, 0 };
			sourcerect = &null;
		}
		sourcerect->x = source[0];
		sourcerect->y = source[1];
		sourcerect->w = source[2];
		sourcerect->h = source[3];
	}
	if (destination[0] == 0 || destination[0] == 0) {
		destinationrect = NULL;
	}
	else {
		if (destinationrect == NULL) {
			SDL_Rect null;
			null = { 0 , 0, 0, 0 };
			destinationrect = &null;
		}
		destinationrect->x = destination[0];
		destinationrect->y = destination[1];
		destinationrect->w = destination[2];
		destinationrect->h = destination[3];
	}
}

void aequus::video::Surface::SetSurfaceColor()
{
	if (SDL_SetSurfaceColorMod(sdlsurface, colormod[0] * 255, colormod[1] * 255, colormod[2] * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set surface color mod", logloc, "SetSurfaceColor");
		framework::GetError();
	}
	if (SDL_SetSurfaceAlphaMod(sdlsurface, colormod[3] * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set surface alpha mod", logloc, "SetSurfaceColor");
		framework::GetError();
	}
}

void aequus::video::Surface::SetSurfaceBlend()
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