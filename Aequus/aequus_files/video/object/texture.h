#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
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
				Text texturetext;
				Surface texturesurface;
				void CreateTextureImage(std::string filepath = "NULL");
				void CreateTextureText(std::string text = "NULL", int point = 12, Text::FontWeight weight = Text::REGULAR, std::string fontdirectory = "resources/fonts/Raleway/");
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
				bool textorigin = false;
				void LoadTexture(SDL_Surface* surface = NULL, SDL_Renderer* renderer = NULL);
				void UpdateTexture();
				void CloseTexture();
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
