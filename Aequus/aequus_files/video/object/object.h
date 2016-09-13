#ifndef _AEQUUS_FILES_VIDEO_OBJECT_OBJECT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_OBJECT_H_
#include <string>
#include <vector>
#include "surface.h"
#include "text.h"
#include "texture.h"
#include "../../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace window {
			class Object {
			public:
				Surface objsurface;
				Text objtext;
				Texture objtexture;
				void InitalizeObj(SDL_Renderer* renderer = NULL, int counter = 0);
				void CreateImgObj(std::string filepath = "NULL.png", SDL_Renderer* renderer = NULL);
				void CreateTextObj(std::string text = "NULL", SDL_Renderer* renderer = NULL, int point = 12, aequus::video::window::Text::FontWeight weight = Text::REGULAR, bool italic = false, std::string fontdirectory = "/Raleway/", double color[4] = 0);
				void DisplayObj();
			private:
				int logloc = 0;
				SDL_Renderer* objrenderer = NULL;
				std::string resourcedir = "resources";
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_OBJECT_H_
