#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "text.h"
namespace aequus {
	namespace video {
		namespace window {
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
					NOFLIP,
					HORIZONTAL,
					VERITCAL
				};
				SDL_Texture* sdltexture;
				SDL_Renderer* sdlrenderer;
				Text texturetext;
				Surface texturesurface;
				void CreateTextureImage(std::string filepath = "NULL", SDL_Renderer* renderer = NULL);
				void CreateTextureText(std::string text = "NULL", SDL_Renderer* renderer = NULL, int point = 12, aequus::video::window::Text::FontWeight weight = Text::REGULAR, bool italic = false, std::string fontdirectory = "resources/fonts/Raleway/");
				void TerminateTexture();
				void SetRenderer(SDL_Renderer* renderer = NULL);
				void Render();
				void SetColorMod(float red, float green, float blue, float alpha);
				void SetBlendMode(BlendMode mode);
				void Rotate(double angle, bool degree = false);
				void Flip(RenderFlip flip);
				void SetRotatePoint(int x, int y);
				void SetSourceRect(int x, int y, int width, int height);
				void SetDestinationRect(int x, int y, int width, int height);
			private:
				int logloc = 0;
				int texturewidth, textureheight;
				bool textorigin = false;
				double rotateangle = 0;
				BlendMode blendmode = NONE;
				RenderFlip renderflip = NOFILP;
				int rotatex = -1, rotatey = -1;
				SDL_Rect sourcerect, destinationrect;
				double color[4];
				void LoadTexture();
				void UpdateTexture();
				void CloseTexture();
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
