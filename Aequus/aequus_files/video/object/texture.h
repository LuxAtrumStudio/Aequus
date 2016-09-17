#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "text.h"
namespace aequus {
	namespace video {
		class Texture {
		public:
			enum BlendMode
			{
				NONE = SDL_BLENDMODE_NONE,
				BLEND = SDL_BLENDMODE_BLEND,
				ADD = SDL_BLENDMODE_ADD,
				MOD = SDL_BLENDMODE_MOD
			};
			enum RenderFlip {
				NOFLIP = 0,
				HORIZONTAL = 1,
				VERITCAL = 2
			};
			SDL_Texture* sdltexture;
			SDL_Renderer* sdlrenderer;
			SDL_Surface* sdlsurface;
			void CreateTexture(SDL_Surface* surface);
			void TerminateTexture();
			void SetRenderer(SDL_Renderer* renderer = NULL);
			void Render();
			void SetColorMod(double colormod[4] = 0);
			void SetBlendMode(BlendMode mode);
			void Rotate(double angle, bool degree = false);
			void Flip(RenderFlip flip);
			void SetRotatePoint(int x, int y);
			void SetSourceRect(int rect[4] = 0);
			void SetDestinationRect(int rect[4] = 0);
		private:
			int logloc = 0;
			int texturewidth, textureheight;
			bool textorigin = false;
			double rotateangle = 0;
			BlendMode blendmode = NONE;
			RenderFlip renderflip = RenderFlip::NOFLIP;
			int rotatex = -1, rotatey = -1;
			SDL_Rect sourcerect, destinationrect;
			double color[4];
			void LoadTexture();
			void UpdateTexture();
			void CloseTexture();
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
