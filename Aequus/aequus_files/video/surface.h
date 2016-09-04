#ifndef _AEQUUS_FILES_VIDEO_WINDOW_TEXTURE_SURFACE_H_
#define _AEQUUS_FILES_VIDEO_WINDOW_TEXTURE_SURFACE_H_
#include <string>
#include <vector>
#include "../sdl_headers.h"
#include "../aequus_core.h"
#include "../video.h"
namespace aequus {
	namespace video {
		namespace Window {
			class Texture {
				class Surface {
				public:
					struct SubSurface {
						SDL_Surface surface;
						SDL_Rect sourcerect, destinationrect;
					};
					enum BlendMode {
						NONE,
						BLEND,
						ADD,
						MOD
					};
					enum SurfaceType {
						SIMPLE,
						CLIP,
						SPRITESHEET,
						COMBINATION
					};
					SDL_Surface compleatesurface;
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
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_WINDOW_TEXTURE_SURFACE_H_