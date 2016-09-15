#include "object.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::window::Object::InitalizeObj(SDL_Renderer * renderer, int counter, std::string resource)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/object.cpp[" + std::to_string(counter) + "]/");
	resourcedir = resource;
	objrenderer = renderer;
}

void aequus::video::window::Object::CreateImgObj(std::string filepath, SDL_Renderer * renderer)
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
}

void aequus::video::window::Object::CreateTextObj(std::string text, int point, double red, double green, double blue, double alpha, aequus::video::window::Text::FontWeight weight, bool italic, std::string fontdirectory, SDL_Renderer * renderer)
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
}

void aequus::video::window::Object::Scale(int x, int y)
{
	sizex = x;
	sizey = y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::window::Object::ScalePercent(double x, double y)
{
	int maxx = aequus::video::window::windows[boundwindow].sizex;
	int maxy = aequus::video::window::windows[boundwindow].sizey;
	sizex = x * maxx;
	sizey = y * maxy;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::window::Object::Translate(int x, int y)
{
	posx = posy + x;
	posy = posy + y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::window::Object::SetPos(int x, int y)
{
	posx = x;
	posy = y;
	int rect[4] = { posx, posy, sizex, sizey };
	objtexture.SetDestinationRect(rect);
}

void aequus::video::window::Object::SetColor(double red, double green, double blue, double alpha)
{
	colormod[0] = red;
	colormod[1] = green;
	colormod[2] = blue;
	colormod[3] = alpha;
	objtexture.SetColorMod(colormod);
}

void aequus::video::window::Object::SetClipSpace(int startx, int starty, int width, int height)
{
	clipx = startx;
	clipy = starty;
	clipsizex = width;
	clipsizey = height;
	int rect[4] = { clipx, clipy, clipsizex, clipsizey };
	objtexture.SetSourceRect(rect);
}

void aequus::video::window::Object::Rotate(double angle, bool degree, int axisx, int axisy)
{
	rotateangle = angle;
	if (axisx != -1 && axisy != -1) {
		rotateaxisx = axisx;
		rotateaxisy = axisy;
		objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
	}
	objtexture.Rotate(rotateangle, degree);
}

void aequus::video::window::Object::DisplayObj()
{
	objtexture.Render();
}