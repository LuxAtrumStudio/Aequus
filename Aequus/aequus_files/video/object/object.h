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
		//Object class is used to manage everything to do with visual objects
		//Used to create an manipulates image texture or text textures
		class Object {
		public:
			enum ObjectType {
				IMAGE,
				TEXT,
				BUTTON
			};
			//Storage to Surface class assosiated with the object
			Surface objsurface;
			//Storage to Text class assosiated with the object
			Text objtext;
			//Storage to Texture class assosiated with the object
			Texture objtexture;
			ObjectType objtype = IMAGE;
			//Sets the base initialization requiered for a new object
			void InitalizeObj(SDL_Renderer* renderer = NULL, int counter = 0, std::string resource = "resources/");
			//Creates a new image object, based off of the given file path
			//Creates a new surface and links it to the texture
			void CreateImgObj(std::string filepath = "NULL.png", SDL_Renderer* renderer = NULL);
			//Creates a new text object, based off of the given text and other parameters
			//Creates a new text and links it to the texture
			void CreateTextObj(std::string text = "NULL", int point = 12, double red = 1, double green = 1, double blue = 1, double alpha = 1, Text::FontWeight weight = Text::REGULAR, bool italic = false, std::string fontdirectory = "Raleway/", SDL_Renderer* renderer = NULL);
			//Scales the object to be a raw x by y size
			void Scale(int x = -1, int y = -1);
			//Scales the object relative to the percent of the total window size
			void ScalePercent(double x = 1, double y = 1);
			//Moves the object by adding the x and y to the current position vector for the object
			void Translate(int x = 0, int y = 0);
			//Sets the objects position vector to x and y
			void SetPos(int x = 0, int y = 0);
			//Alters the color modification for the texture
			void SetColor(double red, double green, double blue, double alpha);
			//Selects a specific portion of the object to copy to the renderer
			//The final appearence is always at the correct scale, causing the clip to be
			//streached as needed
			void SetClipSpace(int startx, int starty, int width, int height);
			//Rotates the object around a set point
			void Rotate(double angle = 0, bool degree = false, int axisx = -1, int axisy = -1);
			//Renders a copy of the object to the currently set renderer
			void DisplayObj();
			//Creates a button that returns the button id
			void CreateButton(std::string text = "NULL", std::string imagepath = "NULL.png", bool whitetext = false, bool clipbutton = false, SDL_Renderer* renderer = NULL);
			bool UpdateButton(int mousex = 0, int mousey = 0, int mousestate = 0);
		private:
			//Pointer to logging locaiton
			int logloc = 0;
			//Pointer to currently set sdl renderer
			SDL_Renderer* objrenderer = NULL;
			//Position, size, and point of rotation data for the object
			int posx, posy, sizex, sizey, rotateaxisx, rotateaxisy;
			//Clipping locaiton and size data fo the object
			int clipx, clipy, clipsizex, clipsizey;
			//The angle of rotation applied to the object
			double rotateangle;
			//The color modification data for the object
			//[0] red, [1] green, [2] blue, [3] alpha
			double colormod[4];
			double savedcolormod[4] = { 0, 0, 0, 0 };
			//Standard directory for all resources
			//Image files are stored in "images/"
			//Font files are stored in "fonts/"
			std::string resourcedir = "resources/";
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_OBJECT_H_
