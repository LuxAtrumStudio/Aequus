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
			//Renderer class, used to store all data for an SDL renderer, aswell as
			//running all basic renderer funcitons, such as changing settings
			//and basic draw functions.
			class Renderer {
			public:
				//Used to set renderer mode between the different poslible SDL modes
				enum RendererFlags
				{
					SOFTWARE = SDL_RENDERER_SOFTWARE,
					ACCELERATED = SDL_RENDERER_ACCELERATED,
					VSYNC = SDL_RENDERER_PRESENTVSYNC,
					TARGETTEXTURE = SDL_RENDERER_TARGETTEXTURE
				};
				//Sets the blending mode for the renderer
				enum BlendMode
				{
					NONE = SDL_BLENDMODE_NONE,
					BLEND = SDL_BLENDMODE_BLEND,
					ADD = SDL_BLENDMODE_ADD,
					MOD = SDL_BLENDMODE_MOD
				};
				//Internal structure for the declaration of an SDL rect
				struct Rectangle
				{
					int x, y, width, height;
				};
				//Internal structure for the use of multiple bicoordinate points
				struct Point
				{
					int x, y;
				};
				//The pointer to the SDL renderer
				SDL_Renderer* sdlrenderer;
				//Internal storage of the renderer mode, for functions to check against
				RendererFlags rendererflag;
				//Genoreates a new renderer from a given window, and creates the log
				void CreateRenderer(SDL_Window* sdlwindow, std::string title, RendererFlags flags);
				//Destroys the renderer, but not the window
				void DestroyRenderer();
				//Sets a texture to render to
				void SetTargetTexture(Texture target);
				//Sets the color the draw funcitons use
				void SetDrawColor(float red, float green, float blue, float alpha);
				//Sets the blend mode for the draw funcitons
				void SetDrawBlendMode(BlendMode mode);
				//Sets the viewport of the renderer
				void SetViewport(Rectangle rect);
				//Sets the scale in an x factor and y factor of the renderer
				void SetScale(float scalex, float scaley);
				//Sets the resolution of the renderer, without changing the window
				void SetResolution(int width, int height);
				//Sets the zone to renderer to on the target texture
				void SetTargetClip(Rectangle rect);
				//Updates the renderer and displays everything that has been drawn
				void Update();
				//Draws a rectangle outline
				void DrawRectangle(Rectangle rect);
				//Draws multiple rectangle outlines
				void DrawRectangles(std::vector<Rectangle> rects);
				//Draws a filled in rectangle
				void FillRectangle(Rectangle rect);
				//Draws multiple filled in rectangles
				void FillRectangles(std::vector<Rectangle> rects);
				//Draws a point
				void DrawPoint(Point point);
				//Draws multiple points
				void DrawPoints(std::vector<Point> points);
				//Draws a line connecting the two points
				void DrawLine(Point a, Point b);
				//Draws multiple lines that are all conected, connecting all the points
				void DrawLines(std::vector<Point> points);
				//Clears the renderer with the current draw color
				void Clear();
			private:
				//Sets log location for aequus framework logging
				int logloc = 0;
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_RENDERER_H_
