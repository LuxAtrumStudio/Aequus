#ifndef _AEQUUS_FILES_VIDEO_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_TEXTURE_H_
#include <string>
#include <vector>
#include "video_objects.h"
#include "../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace window {
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
				SDL_Surface sdlsurface;
				SDL_Texture* sdltexture;
				std::vector<SubSurface> subsurfaces;
				void LoadSurface(std::string filepath = "NULL", SurfaceType type = SIMPLE);
				void SetSourceRect(int x, int y, int width, int height);
				void SetDestinationRect(int x, int y, int width, int height);
				void SetSurfaceColorMod(float red, float green, float blue, float alpha);
				void SetBlendMode(BlendMode mode);
				void CompileSurface();
			private:
				SurfaceType surfacetype = SIMPLE;
				int currentsurface = 0;
				int logloc = 0;
			};
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_TEXTURE_H_