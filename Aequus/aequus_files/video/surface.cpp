#include "surface.h"
#include "../sdl_headers.h"
#include "../framework.h"
#include "../../pessum_files/logging.h"

void aequus::video::Window::Texture::Surface::LoadSurface(std::string filepath, SurfaceType type)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/surface[" + filepath + "]");
	SDL_Surface* loadedsurface = IMG_Load(filepath.c_str());
	if (loadedsurface == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load image", logloc, "LoadSurface");
		framework::GetError(2);
	}
	SubSurface newsurface;
	newsurface.surface = *loadedsurface;
	currentsurface = subsurfaces.size();
	subsurfaces.push_back(newsurface);
	surfacetype = type;
	if (type == SIMPLE) {
		CompileSurface();
	}
}

void aequus::video::Window::Texture::Surface::SetSourceRect(int x, int y, int width, int height)
{
	subsurfaces[currentsurface].sourcerect = { x, y, width, height };
}

void aequus::video::Window::Texture::Surface::SetDestinationRect(int x, int y, int width, int height)
{
	subsurfaces[currentsurface].destinationrect = { x, y, width, height };
}

void aequus::video::Window::Texture::Surface::SetSurfaceColorMod(float red, float green, float blue, float alpha)
{
	SDL_SetSurfaceColorMod(&subsurfaces[currentsurface].surface, red * 255, green * 255, blue * 255);
	SDL_SetSurfaceAlphaMod(&subsurfaces[currentsurface].surface, alpha * 255);
}

void aequus::video::Window::Texture::Surface::SetBlendMode(BlendMode mode)
{
	SDL_BlendMode blendmode = SDL_BLENDMODE_NONE;
	if (mode == BLEND) {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	else if (mode == ADD) {
		blendmode = SDL_BLENDMODE_ADD;
	}
	else if (mode == MOD) {
		blendmode = SDL_BLENDMODE_MOD;
	}
	SDL_SetSurfaceBlendMode(&subsurfaces[currentsurface].surface, blendmode);
}

void aequus::video::Window::Texture::Surface::CompileSurface()
{
	if (surfacetype == SIMPLE) {
		compleatesurface = subsurfaces[0].surface;
	}
	else if (surfacetype == CLIP || surfacetype == SPRITESHEET) {
		int width = subsurfaces[0].surface.w, height = subsurfaces[0].surface.h;
		compleatesurface = *SDL_CreateRGBSurface(0, width, height, 16, 0, 0, 0, 0);
		SDL_BlitSurface(&subsurfaces[0].surface, &subsurfaces[0].sourcerect, &compleatesurface, &subsurfaces[0].destinationrect);
	}
	else if (surfacetype == COMBINATION) {
	}
}