#include "text.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/pessum_headers.h"

void aequus::video::Text::CreateFont(std::string directory, int point, FontWeight weight, bool italic)
{
	folderpath = directory;
	SetPoint(point);
	SetWeight(weight);
	SetItalic(italic);
	GenFilePath();
	LoadFont();
}

void aequus::video::Text::TerminateFont()
{
	CloseFont();
	folderpath = "NULL";
	fontname = "NULL";
	filepath = "NULL";
	fontweight = REGULAR;
	fontpoint = 1;
	fontitalic = false;
	textcolor[0] = 0;
	textcolor[1] = 0;
	textcolor[2] = 0;
	textcolor[3] = 1;
	backgroundcolor[0] = 0;
	backgroundcolor[1] = 0;
	backgroundcolor[2] = 0;
	backgroundcolor[3] = 1;
	text = "NULL";
}

void aequus::video::Text::SetPoint(int point)
{
	fontpoint = point;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::Text::SetWeight(FontWeight weight)
{
	fontweight = weight;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::Text::SetItalic(bool italic)
{
	fontitalic = italic;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::Text::SetColor(double colors[4])
{
	if (colors != NULL) {
		if (colors[0] != 0 || colors[1] != 0 || colors[2] != 0 || colors[3] != 0) {
			for (int a = 0; a < 4; a++) {
				textcolor[a] = colors[a];
			}
		}
	}
}

void aequus::video::Text::SetBackgroundColor(double colors[4])
{
	for (int a = 0; a < 4; a++) {
		backgroundcolor[a] = colors[a];
	}
}

void aequus::video::Text::RenderText(std::string str, FontRenderMode mode)
{
	text = str;
	SDL_Color sdlcolor;
	sdlcolor.r = textcolor[0] * 255;
	sdlcolor.g = textcolor[1] * 255;
	sdlcolor.b = textcolor[2] * 255;
	sdlcolor.a = textcolor[3] * 255;
	if (mode == SOLIDTEXT) {
		textsurface = TTF_RenderText_Solid(ttffont, text.c_str(), sdlcolor);
	}
	if (mode == SHADEDTEXT) {
		SDL_Color sdlcolorbg;
		sdlcolorbg.r = backgroundcolor[0] * 255;
		sdlcolorbg.g = backgroundcolor[1] * 255;
		sdlcolorbg.b = backgroundcolor[2] * 255;
		sdlcolorbg.a = backgroundcolor[3] * 255;
		textsurface = TTF_RenderText_Shaded(ttffont, text.c_str(), sdlcolor, sdlcolorbg);
	}
	if (mode == BLENDTEXT) {
		textsurface = TTF_RenderText_Blended(ttffont, text.c_str(), sdlcolor);
	}
	sourcerect = { 0 , 0, 0, 0 };
	sourcerect.h = textsurface->h;
	sourcerect.w = textsurface->w;
	sourcerect.x = 0;
	sourcerect.y = 0;
	destinationrect = sourcerect;
}

void aequus::video::Text::CreateText(std::string str, int point, FontWeight weight, bool italic, std::string direcory, double colors[4])
{
	SetColor(colors);
	CreateFont(direcory, point, weight, italic);
	if (ttffont != NULL) {
		RenderText(str);
	}
}

void aequus::video::Text::FindSize(int *x, int *y, std::string str)
{
	if (ttffont == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Cannot estimate size, font is undeclaired", logloc, "FindSize");
	}
	TTF_SizeText(ttffont, str.c_str(), x, y);
}

void aequus::video::Text::LoadFont()
{
	if (filepath == "NULL") {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "File path not declaired", logloc, "LoadFont");
	}
	else {
		std::string dir = folderpath + filepath;
		ttffont = TTF_OpenFont(dir.c_str(), fontpoint);
		if (ttffont == NULL) {
			pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load font file: " + filepath, logloc, "LoadFont");
		}
		else{
			pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Loaded font file: " + filepath, logloc, "LoadFont");
		}
	}
}

void aequus::video::Text::UpdateFont()
{
	CloseFont();
	GenFilePath();
	std::string dir = folderpath + filepath;
	ttffont = TTF_OpenFont(dir.c_str(), fontpoint);
	if (ttffont == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load font file: " + filepath, logloc, "UpdateFont");
	}
}

void aequus::video::Text::CloseFont()
{
	TTF_CloseFont(ttffont);
}

void aequus::video::Text::GenFilePath()
{
	std::string fontfile = "";
	for (unsigned a = folderpath.size() - 2; a > 0 && folderpath[a] != '/'; a--) {
		fontfile = folderpath[a] + fontfile;
	}
	fontname = fontfile;
	fontfile = fontfile + "-";
	if (fontweight == THIN) {
		fontfile = fontfile + "Thin";
	}
	else if (fontweight == EXTRALIGHT) {
		fontfile = fontfile + "ExtraLight";
	}
	else if (fontweight == LIGHT) {
		fontfile = fontfile + "Light";
	}
	else if (fontweight == REGULAR && fontitalic == false) {
		fontfile = fontfile + "Regular";
	}
	else if (fontweight == MEDIUM) {
		fontfile = fontfile + "Medium";
	}
	else if (fontweight == SEMIBOLD) {
		fontfile = fontfile + "SemiBold";
	}
	else if (fontweight == BOLD) {
		fontfile = fontfile + "Bold";
	}
	else if (fontweight == EXTRABOLD) {
		fontfile = fontfile + "ExtraBold";
	}
	else if (fontweight == BLACK) {
		fontfile = fontfile + "Black";
	}
	if (fontitalic == true) {
		fontfile = fontfile + "Italic";
	}
	fontfile = fontfile + ".ttf";
	filepath = fontfile;
}
