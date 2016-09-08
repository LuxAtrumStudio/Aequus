#include "object\texture.h"
#include "../aequus_headers.h"
#include "../../pessum_files/logging.h"

void aequus::video::window::Texture::LoadSurface(std::string filepath, SurfaceType type)
{
	SDL_Surface* loadedsurface = IMG_Load(filepath.c_str());
	if (loadedsurface == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load image", logloc, "LoadSurface");
		framework::GetError(2);
	}
	SubSurface newsurface;
	newsurface.surface = *loadedsurface;
	currentsurface = subsurfaces.size();
	subsurfaces.push_back(newsurface);
	surfacetype = type;
	if (type == SIMPLE) {
		CompileTexture();
	}
}

void aequus::video::window::Texture::SetSurfaceSourceRect(int x, int y, int width, int height, int pointer)
{
	if (pointer == -1) {
		pointer = currentsurface;
	}
	subsurfaces[pointer].sourcerect = { x, y, width, height };
}

void aequus::video::window::Texture::SetSurfaceDestinationRect(int x, int y, int width, int height, int pointer)
{
	if (pointer == -1) {
		pointer = currentsurface;
	}
	subsurfaces[pointer].destinationrect = { x, y, width, height };
}

void aequus::video::window::Texture::SetSurfaceColorMod(float red, float green, float blue, float alpha, int pointer)
{
	if (pointer == -1) {
		pointer = currentsurface;
	}
	SDL_SetSurfaceColorMod(&subsurfaces[pointer].surface, red * 255, green * 255, blue * 255);
	SDL_SetSurfaceAlphaMod(&subsurfaces[pointer].surface, alpha * 255);
}

void aequus::video::window::Texture::SetSurfaceBlendMode(BlendMode mode, int pointer)
{
	if (pointer == -1) {
		pointer = currentsurface;
	}
	SDL_BlendMode blendmode = SDL_BLENDMODE_NONE;
	if (mode == BLEND) {
		blendmode = SDL_BLENDMODE_BLEND;
	}
	else if (mode == ADD) {
		blendmode = SDL_BLENDMODE_ADD;
	}
	else if (mode == MOD) {
		blendmode = SDL_BLENDMODE_MOD;
	}
	SDL_SetSurfaceBlendMode(&subsurfaces[pointer].surface, blendmode);
}

void aequus::video::window::Texture::FreeSurface(int pointer)
{
	if (pointer == -1) {
		pointer = currentsurface;
	}
	SDL_FreeSurface(&subsurfaces[pointer].surface);
}

void aequus::video::window::Texture::CompileTexture()
{
	if (surfacetype == SIMPLE) {
		sdlsurface = subsurfaces[0].surface;
	}
	else if (surfacetype == CLIP || surfacetype == SPRITESHEET) {
		int width = subsurfaces[0].surface.w, height = subsurfaces[0].surface.h;
		sdlsurface = *SDL_CreateRGBSurface(0, width, height, 16, 0, 0, 0, 0);
		SDL_BlitSurface(&subsurfaces[0].surface, &subsurfaces[0].sourcerect, &sdlsurface, &subsurfaces[0].destinationrect);
	}
	else if (surfacetype == COMBINATION) {
	}
	if (sdltexture != NULL) {
		DestroyTexture();
	}
	sdltexture = SDL_CreateTextureFromSurface(sldrenderer, &sdlsurface);
	if (sdltexture == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to create texture from surface", logloc, "CompileTexture");
		framework::GetError();
	}
	for (unsigned a = 0; a < subsurfaces.size(); a++) {
		FreeSurface(a);
	}
	//SDL_FreeSurface(&sdlsurface);
}

void aequus::video::window::Texture::CreateTexture(std::string filepath, std::string windowtitle, SDL_Renderer* renderer, bool simple)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" + windowtitle + "]/texutre[" + filepath + "]/");
	sldrenderer = renderer;
	if (simple == true) {
		LoadSurface(filepath, SIMPLE);
	}
}

void aequus::video::window::Texture::SetRenderer(SDL_Renderer * renderer)
{
	sldrenderer = renderer;
}

void aequus::video::window::Texture::Render()
{
	SDL_Point rotatepoint = { rotatex, rotatey };
	SDL_RendererFlip sdlflip = SDL_FLIP_NONE;
	if (renderflip == HORIZONTAL) {
		sdlflip = SDL_FLIP_HORIZONTAL;
	}
	else if (renderflip == VERITCAL) {
		sdlflip = SDL_FLIP_VERTICAL;
	}
	SDL_Rect* sdlsource = NULL;
	SDL_Rect* sdldestination = NULL;
	if (source.h == 0 && source.w == 0) {
		sdlsource = NULL;
	}
	else {
		sdlsource = &source;
	}
	if (destination.h == 0 && destination.w == 0) {
		if (sdlsource != NULL) {
			sdldestination = sdlsource;
		}
		else {
			destination.x = 0;
			destination.y = 0;
			destination.w = sdlsurface.w;
			destination.h = sdlsurface.h;
			sdldestination = &destination;
		}
	}
	else {
		sdldestination = &destination;
	}
	if (SDL_RenderCopyEx(sldrenderer, sdltexture, sdlsource, sdldestination, rotateangle, &rotatepoint, sdlflip) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to copy texture to renderer", logloc, "Render");
		framework::GetError();
	}
}

void aequus::video::window::Texture::DestroyTexture()
{
	SDL_DestroyTexture(sdltexture);
}

void aequus::video::window::Texture::SetColorMod(float red, float green, float blue, float alpha)
{
	if (SDL_SetTextureColorMod(sdltexture, red * 255, green * 255, blue * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture color mod", logloc, "SetColorMod");
		framework::GetError();
	}
	if (SDL_SetTextureAlphaMod(sdltexture, alpha * 255) != 0) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Filed to set texture alpha mod", logloc, "SetColorMod");
		framework::GetError();
	}
}

void aequus::video::window::Texture::SetBlendMode(BlendMode mode)
{
	blendmode = mode;
	SDL_BlendMode sdlblendmode = SDL_BLENDMODE_NONE;
	if (mode == BLEND) {
		sdlblendmode = SDL_BLENDMODE_BLEND;
	}
	else if (mode == ADD) {
		sdlblendmode = SDL_BLENDMODE_ADD;
	}
	else if (mode == MOD) {
		sdlblendmode = SDL_BLENDMODE_MOD;
	}
	SDL_SetTextureBlendMode(sdltexture, sdlblendmode);
}

void aequus::video::window::Texture::Rotate(double angle, bool degree)
{
	if (degree == false) {
		angle = angle * (double)180 / (double) 3.1415926535;
	}
	rotateangle = angle;
}

void aequus::video::window::Texture::Flip(RenderFlip flip)
{
	renderflip = flip;
}

void aequus::video::window::Texture::SetRotatePoint(int x, int y)
{
	rotatex = x;
	rotatey = y;
}

void aequus::video::window::Texture::SetSourceRect(int x, int y, int width, int height)
{
	source.x = x;
	source.y = y;
	source.w = width;
	source.h = height;
}

void aequus::video::window::Texture::SetDestinationRect(int x, int y, int width, int height)
{
	destination.x = x;
	destination.y = y;
	destination.w = width;
	destination.h = height;
}

void aequus::video::window::Texture::LoadFont(int pt, std::string fontdirectory, FontWeight weight, bool italic, float red, float green, float blue, float alpha)
{
	font.fontdirectory = fontdirectory;
	font.weight = weight;
	font.italic = italic;
	font.pt = pt;
	font.red = red;
	font.green = green;
	font.blue = blue;
	font.alpha = alpha;
	GenorateFontFileDirectory();
	if (logloc == 0) {
		logloc = pessum::logging::AddLogLocation("aequus_files/video/window[UNKNOWN]/texutre[" + font.fontname + "]/");
	}
	std::string totaldirectory = font.fontdirectory + font.fontfile;
	font.ttffont = TTF_OpenFont(totaldirectory.c_str(), font.pt);
	if (font.ttffont == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load font file: " + totaldirectory, logloc, "LoadFont");
	}
}

void aequus::video::window::Texture::UpdateFont()
{
	CloseFont();
	GenorateFontFileDirectory();
	std::string totaldirectory = font.fontdirectory + font.fontfile;
	font.ttffont = TTF_OpenFont(totaldirectory.c_str(), font.pt);
	if (font.ttffont == NULL) {
		pessum::logging::LogLoc(pessum::logging::LOG_ERROR, "Failed to load font file: " + totaldirectory, logloc, "UpdateFont");
	}
	if (sdltexture != NULL) {
		RenderText(textstr, textrendermode);
	}
}

void aequus::video::window::Texture::CloseFont()
{
	TTF_CloseFont(font.ttffont);
}

void aequus::video::window::Texture::TerminateFont()
{
	CloseFont();
	font.fontdirectory = "NULL";
	font.fontfile = "NULL";
	font.fontname = "NULL";
	font.weight = REGULAR;
	font.pt = 12;
	font.red = 0;
	font.green = 0;
	font.blue = 0;
	font.alpha = 1;
}

void aequus::video::window::Texture::SetFontPt(int pt)
{
	font.pt = pt;
	UpdateFont();
}

void aequus::video::window::Texture::SetFontWeight(FontWeight weight)
{
	font.weight = weight;
	UpdateFont();
}

void aequus::video::window::Texture::SetFontItalic(bool setting)
{
	font.italic = setting;
	UpdateFont();
}

void aequus::video::window::Texture::SetFontColor(float red, float green, float blue, float alpha)
{
	font.red = red;
	font.green = green;
	font.blue = blue;
	font.alpha = alpha;
	UpdateFont();
}

void aequus::video::window::Texture::SetFontBgColor(float red, float green, float blue, float alpha)
{
	font.redbg = red;
	font.greenbg = green;
	font.bluebg = blue;
	font.alphabg = alpha;
}

void aequus::video::window::Texture::SetFontOutline(int outline)
{
	TTF_SetFontOutline(font.ttffont, outline);
}

void aequus::video::window::Texture::SetFontHinting(FontHinting hinting)
{
	TTF_SetFontHinting(font.ttffont, hinting);
}

void aequus::video::window::Texture::SetFontKerning(int kerning)
{
	TTF_SetFontKerning(font.ttffont, kerning);
}

void aequus::video::window::Texture::RenderText(std::string text, FontRenderMode mode)
{
	textrendermode = mode;
	textstr = text;
	SDL_Color sdlcolor;
	sdlcolor.r = font.red * 255;
	sdlcolor.g = font.green * 255;
	sdlcolor.b = font.blue * 255;
	sdlcolor.a = font.alpha * 255;
	surfacetype = TEXT;
	if (mode == SOLIDTEXT) {
		sdlsurface = *TTF_RenderText_Solid(font.ttffont, text.c_str(), sdlcolor);
	}
	if (mode == SHADEDTEXT) {
		SDL_Color sdlcolorbg;
		sdlcolorbg.r = font.redbg * 255;
		sdlcolorbg.g = font.greenbg * 255;
		sdlcolorbg.b = font.bluebg * 255;
		sdlcolorbg.a = font.alphabg * 255;
		sdlsurface = *TTF_RenderText_Shaded(font.ttffont, text.c_str(), sdlcolor, sdlcolorbg);
	}
	if (mode == BLENDTEXT) {
		sdlsurface = *TTF_RenderText_Blended(font.ttffont, text.c_str(), sdlcolor);
	}
	CompileTexture();
}

void aequus::video::window::Texture::GenorateFontFileDirectory()
{
	std::string fontfile = "";
	for (unsigned a = font.fontdirectory.size() - 2; a > 0 && font.fontdirectory[a] != '/'; a--) {
		fontfile = font.fontdirectory[a] + fontfile;
	}
	font.fontname = fontfile;
	fontfile = fontfile + "-";
	if (font.weight == THIN) {
		fontfile = fontfile + "Thin";
	}
	else if (font.weight == EXTRALIGHT) {
		fontfile = fontfile + "ExtraLight";
	}
	else if (font.weight == LIGHT) {
		fontfile = fontfile + "Light";
	}
	else if (font.weight == REGULAR && font.italic == false) {
		fontfile = fontfile + "Regular";
	}
	else if (font.weight == MEDIUM) {
		fontfile = fontfile + "Medium";
	}
	else if (font.weight == SEMIBOLD) {
		fontfile = fontfile + "SemiBold";
	}
	else if (font.weight == BOLD) {
		fontfile = fontfile + "Bold";
	}
	else if (font.weight == EXTRABOLD) {
		fontfile = fontfile + "ExtraBold";
	}
	else if (font.weight == BLACK) {
		fontfile = fontfile + "Black";
	}
	if (font.italic == true) {
		fontfile = fontfile + "Italic";
	}
	fontfile = fontfile + ".ttf";
	font.fontfile = fontfile;
}

void aequus::video::window::Texture::CreateText(std::string text, int pt)
{
	LoadFont(pt);
	RenderText(text);
}