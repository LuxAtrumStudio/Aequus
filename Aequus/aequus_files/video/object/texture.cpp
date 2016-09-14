#include "texture.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::window::Texture::CreateTexture(SDL_Surface * surface)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/texture.cpp/");
	sdlsurface = surface;
	LoadTexture();
}

void aequus::video::window::Texture::TerminateTexture()
{
	CloseTexture();
	sdlrenderer = NULL;
}

void aequus::video::window::Texture::SetRenderer(SDL_Renderer * renderer)
{
	sdlrenderer = renderer;
}

void aequus::video::window::Texture::Render()
{
	SDL_Point rotatepoint = { rotatex, rotatey };
	SDL_RendererFlip sdlflip = SDL_FLIP_NONE;
	if (renderflip == HORIZONTAL) {
		sdlflip = SDL_FLIP_HORIZONTAL;
	}
	else if (renderflip == VERITCAL) {
		sdlflip = SDL_FLIP_VERTICAL;
	}
	SDL_Rect* sdlsource = NULL;
	SDL_Rect* sdldestination = NULL;
	if (sourcerect.h == 0 && sourcerect.w == 0) {
		sdlsource = NULL;
	}
	else {
		sdlsource = &sourcerect;
	}
	if (destinationrect.h == 0 && destinationrect.w == 0) {
		if (sdlsource != NULL) {
			sdldestination = sdlsource;
		}
		else {
			destinationrect.x = 0;
			destinationrect.y = 0;
			destinationrect.w = texturewidth;
			destinationrect.h = textureheight;
			sdldestination = &destinationrect;
		}
	}
	else {
		sdldestination = &destinationrect;
	}
	if (SDL_RenderCopyEx(sdlrenderer, sdltexture, sdlsource, sdldestination, rotateangle, &rotatepoint, sdlflip) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to copy texture to renderer", logloc, "Render");
		framework::GetError();
	}
}

void aequus::video::window::Texture::SetColorMod(float red, float green, float blue, float alpha)
{
	color[0] = red;
	color[1] = green;
	color[2] = blue;
	color[3] = alpha;
	if (SDL_SetTextureColorMod(sdltexture, red * 255, green * 255, blue * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture color mod", logloc, "SetColorMod");
		framework::GetError();
	}
	if (SDL_SetTextureAlphaMod(sdltexture, alpha * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture alpha mod", logloc, "SetColorMod");
		framework::GetError();
	}
}

void aequus::video::window::Texture::SetBlendMode(BlendMode mode)
{
	blendmode = mode;
	SDL_BlendMode sdlblendmode = SDL_BLENDMODE_NONE;
	if (mode == BLEND) {
		sdlblendmode = SDL_BLENDMODE_BLEND;
	}
	else if (mode == ADD) {
		sdlblendmode = SDL_BLENDMODE_ADD;
	}
	else if (mode == MOD) {
		sdlblendmode = SDL_BLENDMODE_MOD;
	}
	SDL_SetTextureBlendMode(sdltexture, sdlblendmode);
}

void aequus::video::window::Texture::Rotate(double angle, bool degree)
{
	if (degree == false) {
		angle = angle * (double)180 / (double) 3.1415926535;
	}
	rotateangle = angle;
}

void aequus::video::window::Texture::Flip(RenderFlip flip)
{
	renderflip = flip;
}

void aequus::video::window::Texture::SetRotatePoint(int x, int y)
{
	rotatex = x;
	rotatey = y;
}

void aequus::video::window::Texture::SetSourceRect(int x, int y, int width, int height)
{
	sourcerect.x = x;
	sourcerect.y = y;
	sourcerect.w = width;
	sourcerect.h = height;
}

void aequus::video::window::Texture::SetDestinationRect(int x, int y, int width, int height)
{
	destinationrect.x = x;
	destinationrect.y = y;
	destinationrect.w = width;
	destinationrect.h = height;
}

void aequus::video::window::Texture::LoadTexture()
{
	if (sdlsurface == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "No surface declaired", logloc, "LoadTexture");
	}
	else if (sdlrenderer == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "No renderer declaired", logloc, "LoadTexture");
	}
	else if (sdlsurface != NULL && sdlrenderer != NULL) {
		sdltexture = SDL_CreateTextureFromSurface(sdlrenderer, sdlsurface);
		if (sdltexture == NULL) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to create texture from surface", logloc, "LoadTexture");
			framework::GetError();
		}
		texturewidth = sdlsurface->w;
		textureheight = sdlsurface->h;
		SDL_FreeSurface(sdlsurface);
	}
}

void aequus::video::window::Texture::UpdateTexture()
{
	CloseTexture();
	LoadTexture();
}

void aequus::video::window::Texture::CloseTexture()
{
	SDL_DestroyTexture(sdltexture);
}