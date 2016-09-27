#ifndef _AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
namespace aequus {
	namespace video {
		//Surface class is used to define everything that is part o the
		//sdl surface library, and used to create and terminate surfaces
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
			//SDL surface pointer
			SDL_Surface* sdlsurface;
			//SDL surface rectangle pointers
			SDL_Rect* sourcerect, *destinationrect;
			//Loads the given filepath to the surface
			void LoadSurface(std::string filepath = "NULL");
			//Returns the surfaces image file path
			std::string GetSurfaceFilePath();
			//Sets the source rect.
			//x, y, width, height
			void SetSourceRectangle(int rectangle[4]);
			//Returns the source rect.
			int* GetSourceRectangle();
			//Sets the destination rect.
			//x, y, width, height
			void SetDestinationRectangle(int rectangle[4]);
			//Returns the destination rect.
			int* GetDestinationRectangle();
			//Sets the color mod of the surface
			//red, green, blue, alpha
			void SetColorMod(double color[4] = 0);
			//Returns the currently set color mod of the surface
			double* GetColorMode();
			//Sets the blend mode of the surface
			void SetBlendMode(BlendMode mode = NONE);
			//Returns the currently set blend mode of the surface
			BlendMode GetBlendMode();
			//Returns the width and height of the surface
			int* GetSize();
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
			int source[4];
			int destination[4];
			//The current color mod applied to the surface
			double colormod[4];
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
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_SURFACE_H_
