#include "draw.h"
#include "../aequus_headers.h"
#include "../../pessum_files/pessum_headers.h"

namespace aequus {
	namespace video {
		namespace draw {
			SDL_Renderer* sdlrenderer = NULL;
			int logloc = 0;
			double drawcolor[4] = { 0 };
		}
	}
}

void aequus::video::draw::InitializeDraw(SDL_Renderer * renderer)
{
	sdlrenderer = renderer;
	logloc = pessum::logging::AddLogLocation("aequus_files/video/draw.h/");
}

void aequus::video::draw::SetRenderer(SDL_Renderer * renderer)
{
	sdlrenderer = renderer;
}

void aequus::video::draw::Line(int a[2], int b[2])
{
	if (sdlrenderer != NULL) {
		if (SDL_RenderDrawLine(sdlrenderer, a[0], a[1], b[0], b[1]) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw line", logloc, "Line");
		}
	}
}

void aequus::video::draw::Lines(std::vector<int *> points)
{
	if (sdlrenderer != NULL) {
		std::vector<SDL_Point> sdlvec;
		for (unsigned a = 0; a < points.size(); a++) {
			SDL_Point newpoint;
			newpoint.x = points[a][0];
			newpoint.y = points[a][1];
			sdlvec.push_back(newpoint);
		}
		SDL_Point* sdlpoints = &sdlvec[0];
		if (SDL_RenderDrawLines(sdlrenderer, sdlpoints, points.size()) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw lines", logloc, "Lines");
		}
	}
}

void aequus::video::draw::Point(int p[2])
{
	if (sdlrenderer != NULL) {
		if (SDL_RenderDrawPoint(sdlrenderer, p[0], p[1]) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw point", logloc, "Point");
		}
	}
}

void aequus::video::draw::Points(std::vector<int*> points)
{
	if (sdlrenderer != NULL) {
		std::vector<SDL_Point> sdlvec;
		for (unsigned a = 0; a < points.size(); a++) {
			SDL_Point newpoint;
			newpoint.x = points[a][0];
			newpoint.y = points[a][1];
			sdlvec.push_back(newpoint);
		}
		SDL_Point* sdlpoints = &sdlvec[0];
		if (SDL_RenderDrawPoints(sdlrenderer, sdlpoints, points.size()) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw points", logloc, "Points");
		}
	}
	else {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Renderer Undeclaired", logloc, "Points");
	}
}

void aequus::video::draw::Rect(int rect[4])
{
	if (sdlrenderer != NULL) {
		SDL_Rect sdlrect = { rect[0] , rect[1], rect[2], rect[3] };
		if (SDL_RenderDrawRect(sdlrenderer, &sdlrect) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw rectangle", logloc, "Rect");
		}
	}
}

void aequus::video::draw::Rects(std::vector<int*> rects)
{
	if (sdlrenderer != NULL) {
		std::vector<SDL_Rect> sdlvec;
		for (unsigned a = 0; a < rects.size(); a++) {
			SDL_Rect newrect = { rects[a][0], rects[a][1], rects[a][2], rects[a][3] };
			sdlvec.push_back(newrect);
		}
		SDL_Rect* sdlrects = &sdlvec[0];
		if (SDL_RenderDrawRects(sdlrenderer, sdlrects, sdlvec.size()) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to draw rectangles", logloc, "Rects");
		}
	}
}

void aequus::video::draw::FillRect(int rect[4])
{
	if (sdlrenderer != NULL) {
		SDL_Rect sdlrect = { rect[0] , rect[1], rect[2], rect[3] };
		if (SDL_RenderFillRect(sdlrenderer, &sdlrect) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to fill rectangle", logloc, "FillRect");
		}
	}
}

void aequus::video::draw::FillRects(std::vector<int*> rects)
{
	if (sdlrenderer != NULL) {
		std::vector<SDL_Rect> sdlvec;
		for (unsigned a = 0; a < rects.size(); a++) {
			SDL_Rect newrect = { rects[a][0], rects[a][1], rects[a][2], rects[a][3] };
			sdlvec.push_back(newrect);
		}
		SDL_Rect* sdlrects = &sdlvec[0];
		if (SDL_RenderFillRects(sdlrenderer, sdlrects, sdlvec.size()) != 0) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to fill rectangles", logloc, "FillRects");
		}
	}
}

void aequus::video::draw::SetColor(double red, double green, double blue, double alpha)
{
	drawcolor[0] = red;
	drawcolor[1] = green;
	drawcolor[2] = blue;
	drawcolor[3] = alpha;
	SDL_SetRenderDrawColor(sdlrenderer, red * 255, green * 255, blue * 255, alpha * 255);
}