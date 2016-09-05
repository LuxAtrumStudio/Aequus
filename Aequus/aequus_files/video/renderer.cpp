#include "renderer.h"
#include <vector>
#include <string>
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

void aequus::video::window::Renderer::CreateRenderer(SDL_Window* sdlwindow, std::string title, RendererFlags flags)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + title + "]/renderer");
	sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, flags);
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
	SDL_Rect sdlrect;
	sdlrect.x = rect.x;
	sdlrect.y = rect.y;
	sdlrect.w = rect.width;
	sdlrect.h = rect.height;
	if (SDL_RenderDrawRect(sdlrenderer, &sdlrect) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw rectangle", logloc, "DrawRectangle");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::DrawRectangles(std::vector<Rectangle> rects)
{
	std::vector<SDL_Rect> sdlrects;
	for (unsigned a = 0; a < rects.size(); a++) {
		SDL_Rect sdlrect;
		sdlrect.x = rects[a].x;
		sdlrect.y = rects[a].y;
		sdlrect.w = rects[a].width;
		sdlrect.h = rects[a].height;
		sdlrects.push_back(sdlrect);
	}
	SDL_Rect* rectarray = &sdlrects[0];
	if (SDL_RenderDrawRects(sdlrenderer, rectarray, sdlrects.size()) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw rectangles", logloc, "DrawRectangles");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::FillRectangle(Rectangle rect)
{
	SDL_Rect sdlrect;
	sdlrect.x = rect.x;
	sdlrect.y = rect.y;
	sdlrect.w = rect.width;
	sdlrect.h = rect.height;
	if (SDL_RenderFillRect(sdlrenderer, &sdlrect) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to fill rectangle", logloc, "FillRectangle");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::FillRectangles(std::vector<Rectangle> rects)
{
	std::vector<SDL_Rect> sdlrects;
	for (unsigned a = 0; a < rects.size(); a++) {
		SDL_Rect sdlrect;
		sdlrect.x = rects[a].x;
		sdlrect.y = rects[a].y;
		sdlrect.w = rects[a].width;
		sdlrect.h = rects[a].height;
		sdlrects.push_back(sdlrect);
	}
	SDL_Rect* rectarray = &sdlrects[0];
	if (SDL_RenderFillRects(sdlrenderer, rectarray, sdlrects.size()) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to fill rectangles", logloc, "FillRectangles");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::DrawPoint(Point point)
{
	if (SDL_RenderDrawPoint(sdlrenderer, point.x, point.y) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw point", logloc, "DrawPoint");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::DrawPoints(std::vector<Point> points)
{
	std::vector<SDL_Point> sdlpoints;
	for (unsigned a = 0; a < points.size(); a++) {
		SDL_Point sdlpoint;
		sdlpoint.x = points[a].x;
		sdlpoint.y = points[a].y;
		sdlpoints.push_back(sdlpoint);
	}
	SDL_Point* pointarray = &sdlpoints[0];
	if (SDL_RenderDrawPoints(sdlrenderer, pointarray, sdlpoints.size()) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw points", logloc, "DrawPoints");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::DrawLine(Point pointa, Point pointb)
{
	if (SDL_RenderDrawLine(sdlrenderer, pointa.x, pointa.y, pointb.x, pointb.y) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw line", logloc, "DrawLine");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::DrawLines(std::vector<Point> points)
{
	std::vector<SDL_Point> sdlpoints;
	for (unsigned a = 0; a < points.size(); a++) {
		SDL_Point sdlpoint;
		sdlpoint.x = points[a].x;
		sdlpoint.y = points[a].y;
		sdlpoints.push_back(sdlpoint);
	}
	SDL_Point* pointarray = &sdlpoints[0];
	if (SDL_RenderDrawLines(sdlrenderer, pointarray, sdlpoints.size()) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw lines", logloc, "DrawLines");
		framework::GetError();
	}
}

void aequus::video::window::Renderer::Clear()
{
	if (SDL_RenderClear(sdlrenderer) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to clear renderer", logloc, "Clear");
		framework::GetError();
	}
}