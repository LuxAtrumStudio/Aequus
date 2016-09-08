#ifndef _AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace window {
			class Surface {
			public:
				//Used to set the different blend modes for the surface
				enum BlendMode
				{
					NONE = SDL_BLENDMODE_NONE,
					BLEND = SDL_BLENDMODE_BLEND,
					ADD = SDL_BLENDMODE_ADD,
					MOD = SDL_BLENDMODE_MOD
				};
				//Used to declare rectangles, for sdl
				struct Rectangle
				{
					double x, y, width, height;
				};
				//Used as a set pair of numbers
				struct Pair
				{
					double valuea, valueb;
				};
				//Used a a set of four numbers declairing red, green, blue, alpha
				struct Color
				{
					double red, green, blue, alpha;
				};
				//SDL surface pointer
				SDL_Surface* sdlsurface;
				//SDL surface rectangle pointers
				SDL_Rect* sourcerect, *destinationrect;
				//Loads the given filepath to the surface
				void LoadSurface(std::string filepath = "NULL");
				//Returns the surfaces image file path
				std::string GetSurfaceFilePath();
				//Sets the source rect.
				void SetSourceRectangle(Rectangle srcrect);
				//Returns the source rect.
				Rectangle GetSourceRectangle();
				//Sets the destination rect.
				void SetDestinationRectangle(Rectangle destrect);
				//Returns the destination rect.
				Rectangle GetDestinationRectangle();
				//Sets the color mod of the surface
				void SetColorMod(Color mod);
				//Returns the currently set color mod of the surface
				Color GetColorMode();
				//Sets the blend mode of the surface
				void SetBlendMode(BlendMode mode = NONE);
				//Returns the currently set blend mode of the surface
				BlendMode GetBlendMode();
				//Returns the width and height of the surface
				Pair GetSize();
				//Terminates the surface, and frees the SDL pointer from memory
				void Terminate();
			private:
				//Stores the log location index
				int logloc = 0;
				//The width and height of the surface
				int width, height;
				//The file path of the surfaces image
				std::string surfacefilepath;
				//The bounding source and destination rectangles
				Rectangle source, destination;
				//The current color mod applied to the surface
				Color colormod;
				//The current blend mode applied to the surface
				BlendMode blendmode;
				//Converts from internal Rectangle struct to SDL_Rect struct
				void ConvertRectangles();
				//Sets the surfaces color from the colormod
				void SetSurfaceColor();
				//Sets the surfaces blend mode from the blendmode
				void SetSurfaceBlend();
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
