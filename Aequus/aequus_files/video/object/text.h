#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
namespace aequus {
	namespace video {
		//Text class is used to modify any and all data points in relation to the use
		//of text for objects
		class Text {
		public:
			//Used for setting the differnet font weights that are posible
			enum FontWeight {
				THIN = 0,
				EXTRALIGHT = 1,
				LIGHT = 2,
				REGULAR = 3,
				MEDIUM = 4,
				SEMIBOLD = 5,
				BOLD = 6,
				EXTRABOLD = 7,
				BLACK = 8
			};
			//Changes the quality ofthe font rendering mode
			enum FontRenderMode {
				SOLIDTEXT,
				SHADEDTEXT,
				BLENDTEXT
			};
			//Pointer to sdl surface for the text object
			SDL_Surface* textsurface;
			//Sdl rectange structures for the source and destinaation rectangles
			SDL_Rect* sourcerect, *destinationrect;
			//Loads a new font based off of directory, size, weight, and italics
			void CreateFont(std::string directory = "resources/fonts/Raleway/", int point = 12, FontWeight weight = REGULAR, bool italic = false);
			//Terminates the ttf font pointer
			void TerminateFont();
			//Sets the size of the font to be loaded
			void SetPoint(int point = 12);
			//Sets the weight of the font to be loaded
			void SetWeight(FontWeight weight = REGULAR);
			//Sets the italics of the font to be loaded
			void SetItalic(bool italic = false);
			//Sets the primary color of the font to be loaded
			//red, green, blue, alpha
			void SetColor(double colors[4] = 0);
			//Sets the secondary color of the font to be loaded
			//red, green, blue, alpha
			void SetBackgroundColor(double colors[4] = 0);
			//Renders out the text for given text with the currently loaded font file
			void RenderText(std::string str = "NULL", FontRenderMode mode = BLENDTEXT);
			//Loads a new font with given paramaters
			//Renders text from the given text, and the currently loaded font
			void CreateText(std::string str = "NULL", int point = 12, FontWeight weight = REGULAR, bool italic = false, std::string direcory = "resources/fonts/Raleway/", double colors[4] = 0);
		private:
			//Stores the log location index
			int logloc;
			//Stores the font folder, name, and file path
			std::string folderpath, fontname, filepath;
			//Stores the currently set text that is to be rendered
			std::string text;
			//Stores the current weight of the font
			FontWeight fontweight;
			//Stores the current italcis of the font
			bool fontitalic;
			//Stores the current size of the font
			int fontpoint = 12;
			//Stores the text color
			double textcolor[4];
			//Stores the background color
			double backgroundcolor[4];
			//Pointer to ttf font structure
			TTF_Font* ttffont;
			//Loads the ttf font from all loaded data
			void LoadFont();
			//Termiantes the ttf font pointer, and creates a new one based uppon the current data
			void UpdateFont();
			//Termiantes the ttf font pointer
			void CloseFont();
			//Creates the file path for the font file for font loading
			void GenFilePath();
		};
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
