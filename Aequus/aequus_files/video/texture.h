#ifndef _AEQUUS_FILES_VIDEO_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_TEXTURE_H_
#include <string>
#include <vector>
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace window {
			//Class that is used to contain all information and functions for
			//managing textures
			class Texture {
			public:
				struct SubSurface {
					SDL_Surface surface;
					SDL_Rect sourcerect, destinationrect;
				};
				enum SurfaceType {
					SIMPLE,
					CLIP,
					SPRITESHEET,
					COMBINATION
				};
				enum BlendMode
				{
					NONE = SDL_BLENDMODE_NONE,
					BLEND = SDL_BLENDMODE_BLEND,
					ADD = SDL_BLENDMODE_ADD,
					MOD = SDL_BLENDMODE_MOD
				};
				enum RenderFlip {
					NOFLIP,
					HORIZONTAL,
					VERITCAL
				};
				SDL_Texture* sdltexture = NULL;
				std::vector<SubSurface> subsurfaces;
				//SURFACE FUNCTIONS
				void LoadSurface(std::string filepath = "NULL", SurfaceType type = SIMPLE);
				void SetSurfaceSourceRect(int x, int y, int width, int height, int pointer = -1);
				void SetSurfaceDestinationRect(int x, int y, int width, int height, int pointer = -1);
				void SetSurfaceColorMod(float red, float green, float blue, float alpha, int pointer = -1);
				void SetSurfaceBlendMode(BlendMode mode, int pointer = -1);
				void FreeSurface(int pointer = -1);
				void CompileTexture();
				//TEXTURE FUNCITONS
				void CreateTexture(std::string filepath = "NULL", std::string windowtitle = "NULL", SDL_Renderer* renderer = NULL, bool simple = true);
				void SetRenderer(SDL_Renderer* renderer);
				void Render();
				void DestroyTexture();
				void SetColorMod(float red, float green, float blue, float alpha);
				void SetBlendMode(BlendMode mode);
				void Rotate(double angle, bool degree = false);
				void Flip(RenderFlip flip);
				void SetRotatePoint(int x, int y);
				void SetSourceRect(int x, int y, int width, int height);
				void SetDestinationRect(int x, int y, int width, int height);
			private:
				SDL_Surface sdlsurface;
				SDL_Renderer* sldrenderer = NULL;
				SurfaceType surfacetype = SIMPLE;
				int currentsurface = 0;
				int logloc = 0;
				double rotateangle = 0;
				BlendMode blendmode = BlendMode::NONE;
				RenderFlip renderflip = RenderFlip::NOFLIP;
				int rotatex = -1, rotatey = -1;
				SDL_Rect source, destination;
			};
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_TEXTURE_H_