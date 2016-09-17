#ifndef _AEQUUS_FILES_VIDEO_DRAW_H_
#define _AEQUUS_FILES_VIDEO_DRAW_H_
#include <string>
#include <vector>
#include "renderer.h"
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace draw {
			extern SDL_Renderer* sdlrenderer;
			extern int logloc;
			extern double drawcolor[4];
			void InitializeDraw(SDL_Renderer* renderer);
			void SetRenderer(SDL_Renderer* renderer);
			void Line(int a[2] = 0, int b[2] = 0);
			void Lines(std::vector<int*> points);
			void Point(int p[2] = 0);
			void Points(std::vector<int*> points);
			void Rect(int rect[4]);
			void Rects(std::vector<int*> rects);
			void FillRect(int rect[4]);
			void FillRects(std::vector<int*>rects);
			void SetColor(double red, double green, double blue, double alpha);
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_DRAW_H_
