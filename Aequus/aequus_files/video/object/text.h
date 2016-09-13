#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
namespace aequus {
	namespace video {
		namespace window {
			class Text {
			public:
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
				enum FontRenderMode {
					SOLIDTEXT,
					SHADEDTEXT,
					BLENDTEXT
				};
				//Used a a set of four numbers declairing red, green, blue, alpha
				struct Color
				{
					double red, green, blue, alpha;
				};
				SDL_Surface* textsurface;
				SDL_Rect* sourcerect, *destinationrect;
				void CreateFont(std::string directory = "resources/fonts/Raleway/", int point = 12, FontWeight weight = REGULAR, bool italic = false);
				void TerminateFont();
				void SetPoint(int point = 12);
				void SetWeight(FontWeight weight = REGULAR);
				void SetItalic(bool italic = false);
				void SetColor(double colors[4] = 0);
				void SetBackgroundColor(double colors[4] = 0);
				void RenderText(std::string str = "NULL", FontRenderMode mode = BLENDTEXT);
				void CreateText(std::string str = "NULL", int point = 12, FontWeight weight = REGULAR, bool italic = false, std::string direcory = "resources/fonts/Raleway/", double colors[4] = 0);
			private:
				int logloc;
				std::string folderpath, fontname, filepath;
				std::string text;
				FontWeight fontweight;
				bool fontitalic;
				int fontpoint = 12;
				double textcolor[4];
				double backgroundcolor[4];
				TTF_Font* ttffont;
				void LoadFont();
				void UpdateFont();
				void CloseFont();
				void GenFilePath();
			};
		}
	}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_TEXT_H_
