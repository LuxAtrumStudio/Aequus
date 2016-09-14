#include "text.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::window::Text::CreateFont(std::string directory, int point, FontWeight weight, bool italic)
{
	folderpath = directory;
	SetPoint(point);
	SetWeight(weight);
	SetItalic(italic);
	GenFilePath();
	LoadFont();
}

void aequus::video::window::Text::TerminateFont()
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

void aequus::video::window::Text::SetPoint(int point)
{
	fontpoint = point;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::window::Text::SetWeight(FontWeight weight)
{
	fontweight = weight;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::window::Text::SetItalic(bool italic)
{
	fontitalic = italic;
	if (ttffont != NULL) {
		UpdateFont();
	}
}

void aequus::video::window::Text::SetColor(double colors[4])
{
	for (int a = 0; a < 4; a++) {
		textcolor[a] = colors[a];
	}
}

void aequus::video::window::Text::SetBackgroundColor(double colors[4])
{
	for (int a = 0; a < 4; a++) {
		backgroundcolor[a] = colors[a];
	}
}

void aequus::video::window::Text::RenderText(std::string str, FontRenderMode mode)
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
	if (sourcerect == NULL) {
		SDL_Rect null;
		null = { 0 , 0, 0, 0 };
		sourcerect = &null;
	}
	sourcerect->h = textsurface->h;
	sourcerect->w = textsurface->w;
	sourcerect->x = 0;
	sourcerect->y = 0;
	destinationrect = sourcerect;
}

void aequus::video::window::Text::CreateText(std::string str, int point, FontWeight weight, bool italic, std::string direcory, double colors[4])
{
	SetColor(colors);
	SetPoint(point);
	SetWeight(weight);
	SetItalic(italic);
	CreateFont(direcory, point, weight, italic);
	if (ttffont != NULL) {
		RenderText(str);
	}
}

void aequus::video::window::Text::LoadFont()
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
	}
}

void aequus::video::window::Text::UpdateFont()
{
	CloseFont();
	GenFilePath();
	std::string dir = folderpath + filepath;
	ttffont = TTF_OpenFont(dir.c_str(), fontpoint);
	if (ttffont == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load font file: " + filepath, logloc, "UpdateFont");
	}
}

void aequus::video::window::Text::CloseFont()
{
	TTF_CloseFont(ttffont);
}

void aequus::video::window::Text::GenFilePath()
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