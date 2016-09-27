#ifndef _AEQUUS_FILES_VIDEO_DRAW_H_
#define _AEQUUS_FILES_VIDEO_DRAW_H_
#include <string>
#include <vector>
#include "renderer.h"
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		//draw namespace is used to directly draw to the pixels of the set renderer
		namespace draw {
			//Pointer to sdl renderer to draw to
			extern SDL_Renderer* sdlrenderer;
			//Stores the logging location index
			extern int logloc;
			//Stores the current color to draw with
			//red, green, blue, alpha
			extern double drawcolor[4];
			//Initalizes neccesary data, and set the standard renderer to draw to
			void InitializeDraw(SDL_Renderer* renderer);
			//Sets the sdl renderer that will be drawn to
			void SetRenderer(SDL_Renderer* renderer);
			//Draws a line given two points
			//a = x, y
			//b = x, y
			void Line(int a[2] = 0, int b[2] = 0);
			//Draws a series of connected lines, given a vector of points
			//point = x, y
			void Lines(std::vector<int*> points);
			//Draws a single point
			//p = x, y
			void Point(int p[2] = 0);
			//Draws a series of points, given a vector of points
			//point = x, y
			void Points(std::vector<int*> points);
			//Draws a rectangle
			//rect = x, y, width, height
			void Rect(int rect[4]);
			//Draws a series of rectangels, given a vector of rectangle definitions
			//rectanlge = x, y, width, height
			void Rects(std::vector<int*> rects);
			//Draws a solid rectangles
			//rect = x, y, width, height
			void FillRect(int rect[4]);
			//Draws a series of solid rectangels, gicen a vector of rectangle definitions
			//rectanlge = x, y, width, height
			void FillRects(std::vector<int*>rects);
			//Sets the draw color for all drawing functions
			void SetColor(double red, double green, double blue, double alpha);
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_DRAW_H_
