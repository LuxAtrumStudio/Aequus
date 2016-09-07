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
				enum SurfaceType {
					SIMPLE,
					CLIP,
					SPRITESHEET,
					COMBINATION,
					TEXT
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
				enum FontWeight {
					THIN,
					EXTRALIGHT,
					LIGHT,
					REGULAR,
					MEDIUM,
					SEMIBOLD,
					BOLD,
					EXTRABOLD,
					BLACK
				};
				enum FontHinting {
					NORMALHINTING = 0,
					LIGHTHINTING = 1,
					MONOHINTING = 2,
					NOHINTING = 3
				};
				enum FontRenderMode {
					SOLIDTEXT,
					SHADEDTEXT,
					BLENDTEXT
				};
				struct SubSurface {
					SDL_Surface surface;
					SDL_Rect sourcerect, destinationrect;
				};
				struct FontData {
					std::string fontdirectory = "NULL", fontfile = "NULL", fontname = "NULL";
					FontWeight weight = REGULAR;
					bool italic = false;
					TTF_Font* ttffont = NULL;
					int pt = 12;
					float red = 0, green = 0, blue = 0, alpha = 1;
					float redbg = 1, greenbg = 1, bluebg = 1, alphabg = 1;
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
				//Advanced Textures
				//Text
				void LoadFont(int pt = 12, std::string fontdirectory = "resources/fonts/Raleway/", FontWeight weight = REGULAR, bool italic = false, float red = 0, float green = 0, float blue = 0, float alpha = 1);
				void UpdateFont();
				void CloseFont();
				void TerminateFont();
				void SetFontPt(int pt = 12);
				void SetFontWeight(FontWeight weight = REGULAR);
				void SetFontItalic(bool setting = false);
				void SetFontColor(float red = 0, float green = 0, float blue = 0, float alpha = 1);
				void SetFontBgColor(float red = 0, float green = 0, float blue = 0, float alpha = 1);
				void SetFontOutline(int outline = 0);
				void SetFontHinting(FontHinting hinting = NORMALHINTING);
				void SetFontKerning(int kerning = 1);
				void RenderText(std::string text, FontRenderMode mode = BLENDTEXT);
				void GenorateFontFileDirectory();
				void CreateText(std::string text, int pt);
			private:
				FontData font;
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
				int texturewidth, textureheight;
				std::string textstr;
				FontRenderMode textrendermode;
			};
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_TEXTURE_H_