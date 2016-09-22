#include "object.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::Object::InitalizeObj(SDL_Renderer * renderer, int counter, std::string resource)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/object.cpp[" + std::to_string(counter) + "]/");
	resourcedir = resource;
	objrenderer = renderer;
}

void aequus::video::Object::CreateImgObj(std::string filepath, SDL_Renderer * renderer)
{
	filepath = resourcedir + "images/" + filepath;
	objsurface.LoadSurface(filepath);
	if (renderer != NULL) {
		objrenderer = renderer;
	}
	objtexture.SetRenderer(objrenderer);
	objtexture.CreateTexture(objsurface.sdlsurface);
	posx = 0;
	posy = 0;
	sizex = objsurface.sdlsurface->w;
	sizey = objsurface.sdlsurface->h;
	rotateaxisx = sizex / 2;
	rotateaxisy = sizey / 2;
	objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
	rotateangle = 0;
	objtype = IMAGE;
}

void aequus::video::Object::CreateTextObj(std::string text, int point, double red, double green, double blue, double alpha, aequus::video::Text::FontWeight weight, bool italic, std::string fontdirectory, SDL_Renderer * renderer)
{
	colormod[0] = red;
	colormod[1] = green;
	colormod[2] = blue;
	colormod[3] = alpha;
	fontdirectory = resourcedir + "fonts/" + fontdirectory;
	objtext.CreateText(text, point, weight, italic, fontdirectory, colormod);
	if (renderer != NULL) {
		objrenderer = renderer;
	}
	objtexture.SetRenderer(objrenderer);
	objtexture.CreateTexture(objtext.textsurface);
	objtype = TEXT;
}

void aequus::video::Object::Scale(int x, int y)
{
	sizex = x;
	sizey = y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::ScalePercent(double x, double y)
{
	destsizex = x * sizex;
	destsizey = y * sizey;
	scalex = x;
	scaley = y;
	int rect[4] = { posx, posy, destsizex, destsizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::Translate(int x, int y)
{
	posx = posy + x;
	posy = posy + y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::SetPos(int x, int y)
{
	posx = x;
	posy = y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::SetColor(double red, double green, double blue, double alpha)
{
	colormod[0] = red;
	colormod[1] = green;
	colormod[2] = blue;
	colormod[3] = alpha;
	objtexture.SetColorMod(colormod);
}

void aequus::video::Object::SetClipSpace(int startx, int starty, int width, int height)
{
	if (clipx != startx || clipy != starty || clipsizex != width || clipsizey != height) {
		clipx = startx;
		clipy = starty;
		clipsizex = width;
		clipsizey = height;
		destsizex = clipsizex * scalex;
		destsizey = clipsizey * scaley;
		int rect[4] = { clipx, clipy, clipsizex, clipsizey };
		int rectdest[4] = { posx, posy, destsizex, destsizey };
		objtexture.SetSourceRect(rect);
		objtexture.SetDestinationRect(rectdest);
	}
}

void aequus::video::Object::Rotate(double angle, bool degree, int axisx, int axisy)
{
	rotateangle = angle;
	if (axisx != -1 && axisy != -1) {
		rotateaxisx = axisx;
		rotateaxisy = axisy;
		objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
	}
	objtexture.Rotate(rotateangle, degree);
}

void aequus::video::Object::DisplayObj()
{
	objtexture.Render();
}

void aequus::video::Object::CreateButton(std::string text, std::string imagepath, bool whitetext, bool clipbutton, SDL_Renderer * renderer)
{
	imagepath = resourcedir + "images/" + imagepath;
	int surfaceheight = 0, textheight = 0;
	int surfacewidth = 0, textwidth = 0;
	int pt = 12;
	bool sizing = true, shrink = false, grow = false;
	objsurface.LoadSurface(imagepath);
	surfacewidth = objsurface.sdlsurface->w;
	surfaceheight = objsurface.sdlsurface->h;
	if (text.size() != 0) {
		objtext.CreateFont();
		if (whitetext == true) {
			double color[4] = { 1, 1, 1, 1 };
			objtext.SetColor(color);
		}
		while (sizing == true) {
			objtext.SetPoint(pt);
			objtext.FindSize(&textwidth, &textheight, text);
			if (textwidth > surfacewidth || textheight > surfaceheight) {
				pt--;
				shrink = true;
				if (grow == true) {
					sizing = false;
				}
			}
			else if (textwidth < (float)surfacewidth / 0.9 && textheight < (float)surfaceheight / 0.9) {
				pt++;
				grow = true;
				if (shrink == true) {
					sizing = false;
				}
			}
			else {
				sizing = false;
			}
			if (pt > 100) {
				sizing = false;
			}
		}
		objtext.RenderText(text);
		SDL_Rect recttext;
		recttext.h = surfaceheight;
		recttext.w = surfacewidth;
		recttext.x = 0;
		recttext.y = 0;
		SDL_Rect rectsurface;
		rectsurface.h = surfaceheight;
		rectsurface.w = surfacewidth;
		rectsurface.x = (surfacewidth - objtext.textsurface->w) / 2;
		rectsurface.y = (surfaceheight - objtext.textsurface->h) / 2;
		SDL_BlitScaled(objtext.textsurface, &recttext, objsurface.sdlsurface, &rectsurface);
	}
	objtexture.SetRenderer(objrenderer);
	objtexture.CreateTexture(objsurface.sdlsurface);
	posx = 0;
	posy = 0;
	sizex = objsurface.sdlsurface->w;
	sizey = objsurface.sdlsurface->h;
	rotateaxisx = sizex / 2;
	rotateaxisy = sizey / 2;
	objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
	rotateangle = 0;
	objtype = BUTTON;
	buttonclip = clipbutton;
	if (buttonclip == true) {
		SetClipSpace(0, 0, sizex, sizey / 4);
	}
	destsizex = surfacewidth * scalex;
	destsizey = surfaceheight * scaley;
	for (int a = 0; a < 4; a++) {
		savedcolormod[a] = 1;
	}
}

bool aequus::video::Object::UpdateButton(int mousex, int mousey, int mousestate)
{
	bool clicked = false, update = false;
	if (buttonclip == false) {
		if (mousex < destsizex + posx && mousex > posx) {
			if (mousey < destsizey + posy && mousey > posy) {
				if (mousestate == 0) {
					for (int a = 0; a < 4; a++) {
						if (colormod[a] != savedcolormod[a] + mouseovercolormod[a]) {
							update = true;
						}
					}
					if (update == true) {
						for (int a = 0; a < 4; a++) {
							colormod[a] = savedcolormod[a] + mouseovercolormod[a];
						}
						objtexture.SetColorMod(colormod);
					}
				}
				if (mousestate == 1) {
					for (int a = 0; a < 4; a++) {
						if (colormod[a] != savedcolormod[a] + mousepresscolormod[a]) {
							update = true;
						}
					}
					if (update == true) {
						for (int a = 0; a < 4; a++) {
							colormod[a] = savedcolormod[a] + mousepresscolormod[a];
						}
						objtexture.SetColorMod(colormod);
					}
				}
				if (mousestate == 2) {
					for (int a = 0; a < 4; a++) {
						colormod[a] = savedcolormod[a] + mouseovercolormod[a];
					}
					objtexture.SetColorMod(colormod);
					clicked = true;
				}
			}
			else {
				SetColor(savedcolormod[0], savedcolormod[1], savedcolormod[2], savedcolormod[3]);
			}
		}
		else {
			SetColor(savedcolormod[0], savedcolormod[1], savedcolormod[2], savedcolormod[3]);
		}
	}
	if (buttonclip == true) {
		if (mousex < destsizex + posx && mousex > posx) {
			if (mousey < destsizey + posy && mousey > posy) {
				if (mousestate == 0) {
					SetClipSpace(0, sizey / 4, sizex, sizey / 4);
				}
				if (mousestate == 1) {
					SetClipSpace(0, sizey / 2, sizex, sizey / 4);
				}
				if (mousestate == 2) {
					SetClipSpace(0, 3 * (sizey / 4), sizex, sizey / 4);
					clicked = true;
				}
			}
			else {
				SetClipSpace(0, 0, sizex, sizey / 4);
			}
		}
		else {
			SetClipSpace(0, 0, sizex, sizey / 4);
		}
	}
	return(clicked);
}