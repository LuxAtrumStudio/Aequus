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
		class Object {
		public:
			Surface objsurface;
			Text objtext;
			Texture objtexture;
			void InitalizeObj(SDL_Renderer* renderer = NULL, int counter = 0, std::string resource = "resources/");
			void CreateImgObj(std::string filepath = "NULL.png", SDL_Renderer* renderer = NULL);
			void CreateTextObj(std::string text = "NULL", int point = 12, double red = 1, double green = 1, double blue = 1, double alpha = 1, Text::FontWeight weight = Text::REGULAR, bool italic = false, std::string fontdirectory = "Raleway/", SDL_Renderer* renderer = NULL);
			void Scale(int x = -1, int y = -1);
			void ScalePercent(double x = 1, double y = 1);
			void Translate(int x = 0, int y = 0);
			void SetPos(int x = 0, int y = 0);
			void SetColor(double red, double green, double blue, double alpha);
			void SetClipSpace(int startx, int starty, int width, int height);
			void Rotate(double angle = 0, bool degree = false, int axisx = -1, int axisy = -1);
			void DisplayObj();
		private:
			int logloc = 0;
			SDL_Renderer* objrenderer = NULL;
			int posx, posy, sizex, sizey, rotateaxisx, rotateaxisy;
			int clipx, clipy, clipsizex, clipsizey;
			double rotateangle;
			double colormod[4];
			std::string resourcedir = "resources/";
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_OBJECT_H_
