#include "texture.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/pessum_headers.h"

void aequus::video::Texture::CreateTexture(SDL_Surface * surface)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/texture.cpp/");
	sdlsurface = surface;
	int nullrect[4] = {0, 0, 0, 0};
	SetSourceRect(nullrect);
	SetDestinationRect(nullrect);
	LoadTexture();
}

void aequus::video::Texture::TerminateTexture()
{
	CloseTexture();
	sdlrenderer = NULL;
}

void aequus::video::Texture::SetRenderer(SDL_Renderer * renderer)
{
	sdlrenderer = renderer;
}

void aequus::video::Texture::Render()
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

void aequus::video::Texture::SetColorMod(double colormod[4])
{
	for (int a = 0; a < 4; a++) {
		color[a] = colormod[a];
	}
	if (SDL_SetTextureColorMod(sdltexture, color[0] * 255, color[1] * 255, color[2] * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture color mod", logloc, "SetColorMod");
		framework::GetError();
	}
	if (SDL_SetTextureAlphaMod(sdltexture, color[3] * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture alpha mod", logloc, "SetColorMod");
		framework::GetError();
	}
}

void aequus::video::Texture::SetBlendMode(BlendMode mode)
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
	if (sdltexture != NULL) {
		UpdateTexture();
	}
}

void aequus::video::Texture::Rotate(double angle, bool degree)
{
	if (degree == false) {
		angle = angle * (double)180 / (double) 3.1415926535;
	}
	rotateangle = angle;
}

void aequus::video::Texture::Flip(RenderFlip flip)
{
	renderflip = flip;
}

void aequus::video::Texture::SetRotatePoint(int x, int y)
{
	rotatex = x;
	rotatey = y;
}

void aequus::video::Texture::SetSourceRect(int rect[4])
{
	sourcerect.x = rect[0];
	sourcerect.y = rect[1];
	sourcerect.w = rect[2];
	sourcerect.h = rect[3];
}

void aequus::video::Texture::SetDestinationRect(int rect[4])
{
	destinationrect.x = rect[0];
	destinationrect.y = rect[1];
	destinationrect.w = rect[2];
	destinationrect.h = rect[3];
}

void aequus::video::Texture::LoadTexture()
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
		pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, std::to_string(texturewidth) + "x" + std::to_string(textureheight));
		SDL_FreeSurface(sdlsurface);
	}
}

void aequus::video::Texture::UpdateTexture()
{
	CloseTexture();
	LoadTexture();
}

void aequus::video::Texture::CloseTexture()
{
	SDL_DestroyTexture(sdltexture);
}
