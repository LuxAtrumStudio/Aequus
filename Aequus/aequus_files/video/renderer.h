#ifndef _AEQUUS_FILES_VIDEO_RENDERER_H_
#define _AEQUUS_FILES_VIDEO_RENDERER_H_
#include <vector>
#include "../sdl_headers.h"
#include "window.h"
namespace aequus {
	namespace video {
		namespace window {
			class Renderer {
			public:
				enum RendererFlags
				{
					SOFTWARE = SDL_RENDERER_SOFTWARE,
					ACCELERATED = SDL_RENDERER_ACCELERATED,
					VSYNC = SDL_RENDERER_PRESENTVSYNC,
					TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
				};
				enum BlendMode
				{
					NONE = SDL_BLENDMODE_NONE,
					BLEND = SDL_BLENDMODE_BLEND,
					ADD = SDL_BLENDMODE_ADD,
					MOD = SDL_BLENDMODE_MOD
				};
				struct Rectangle
				{
					int x, y, width, height;
				};
				struct Point
				{
					int x, y;
				};
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
				void CopyTextureToTarget(Texture source, Rectangle sourcerect, Rectangle destrect);
				void Clear();
			private:
				int logloc = 0;
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_RENDERER_H_
