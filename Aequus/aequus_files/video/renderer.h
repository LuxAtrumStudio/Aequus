#ifndef _AEQUUS_FILES_VIDEO_RENDERER_H_
#define _AEQUUS_FILES_VIDEO_RENDERER_H_
#include <vector>
#include "video_objects.h"
#include "../sdl_headers.h"
#include "window.h"
#include "texture.h"
namespace aequus {
	namespace video {
		namespace window {
			class Renderer {
			public:
				SDL_Renderer* sdlrenderer;
				RendererFlags rendererflag;
				void CreateRenderer(WindowData window, RendererFlags flags);
				void DestroyRenderer();
				void SetTargetTexture(Texture target);
				void SetDrawColor(float red, float green, float blue, float alpha);
				void SetDrawBlendMode(BlendMode mode);
				void SetViewport(Rectangle rect);
				void SetScale(float scalex, float scaley);
				void SetResolution(int width, int height);
				void SetTargetClip(Rectangle rect);
				void Update();
				void DrawRectangle(Rectangle rect);
				void DrawRectangles(std::vector<Rectangle> rects);
				void FillRectangle(Rectangle rect);
				void FillRectangles(std::vector<Rectangle> rects);
				void DrawPoint(Point point);
				void DrawPoints(std::vector<Point> points);
				void DrawLine(Point a, Point b);
				void DrawLines(std::vector<Point> points);
				void Clear();
			private:
				int logloc = 0;
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_RENDERER_H_
