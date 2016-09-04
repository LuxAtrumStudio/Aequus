#include "renderer.h"
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

void aequus::video::window::Renderer::CreateRenderer(WindowData window, RendererFlags flags)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + window.title + "]/renderer");
	sdlrenderer = SDL_CreateRenderer(window.sdlwindow, -1, flags);
	rendererflag = flags;
	if (sdlrenderer == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to create renderer", logloc, "CreateRenderer");
		framework::GetError();
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Create renderer", logloc, "CreateRenderer");
	}
}

void aequus::video::window::Renderer::DestroyRenderer()
{
	SDL_DestroyRenderer(sdlrenderer);
	pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Destroyed renderer", logloc, "DestroyRenderer");
}

void aequus::video::window::Renderer::SetTargetTexture(Texture target)
{
	if (rendererflag == TARGETTEXTURE) {
		if (SDL_SetRenderTarget(sdlrenderer, target.sdltexture) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set render target texture", logloc, "SetTargetTexture");
			framework::GetError();
		}
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Renderer cannot target texture", logloc, "SetTargetTexture");
	}
}

void aequus::video::window::Renderer::SetDrawColor(float red, float green, float blue, float alpha)
{
	if (SDL_SetRenderDrawColor(sdlrenderer, red * 255, green * 255, blue * 255, alpha * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set draw color", logloc, "SetDrawColor");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::SetDrawBlendMode(BlendMode mode)
{
	SDL_BlendMode sdlmode;
	if (mode == NONE) {
		sdlmode = SDL_BLENDMODE_NONE;
	}
	else if (mode == ADD) {
		sdlmode = SDL_BLENDMODE_ADD;
	}
	else if (mode == BLEND) {
		sdlmode = SDL_BLENDMODE_BLEND;
	}
	else if (mode == MOD) {
		sdlmode == SDL_BLENDMODE_MOD;
	}
	if (SDL_SetRenderDrawBlendMode(sdlrenderer, sdlmode) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set renderer blend mode", logloc, "SetDrawBlendMode");
	}
}

void aequus::video::window::Renderer::SetViewport(Rectangle rect)
{
	SDL_Rect sdlrect;
	sdlrect.x = rect.x;
	sdlrect.y = rect.y;
	sdlrect.w = rect.width;
	sdlrect.h = rect.height;
	if (SDL_RenderSetViewport(sdlrenderer, &sdlrect) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set render viewport", logloc, "SetViewport");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::SetScale(float scalex, float scaley)
{
	if (SDL_RenderSetScale(sdlrenderer, scalex, scaley) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set render scale", logloc, "SetScale");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::SetResolution(int width, int height)
{
	if (SDL_RenderSetLogicalSize(sdlrenderer, width, height) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set render resolution", logloc, "SetResolution");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::SetTargetClip(Rectangle rect)
{
	SDL_Rect sdlrect;
	sdlrect.x = rect.x;
	sdlrect.y = rect.y;
	sdlrect.w = rect.width;
	sdlrect.h = rect.height;
	if (SDL_RenderSetClipRect(sdlrenderer, &sdlrect) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to set render clip", logloc, "SetTargetClip");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::Update()
{
	SDL_RenderPresent(sdlrenderer);
}

void aequus::video::window::Renderer::DrawRectangle(Rectangle rect)
{
}

void aequus::video::window::Renderer::DrawRectangles(std::vector<Rectangle> rects)
{
}

void aequus::video::window::Renderer::FillRectangle(Rectangle rect)
{
}

void aequus::video::window::Renderer::FillRectangles(std::vector<Rectangle> rects)
{
}

void aequus::video::window::Renderer::DrawPoint(Point point)
{
}

void aequus::video::window::Renderer::DrawPoints(std::vector<Point> points)
{
}

void aequus::video::window::Renderer::DrawLine(Point a, Point b)
{
}

void aequus::video::window::Renderer::DrawLines(std::vector<Point> points)
{
}

void aequus::video::window::Renderer::CopyTextureToTarget(Texture source, Rectangle sourcerect, Rectangle destrect)
{
}

void aequus::video::window::Renderer::Clear()
{
}