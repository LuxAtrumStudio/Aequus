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
}

void aequus::video::window::Object::CreateTextObj(std::string text, int point, aequus::video::window::Text::FontWeight weight, bool italic, std::string fontdirectory, double color[4], SDL_Renderer * renderer)
{
	fontdirectory = resourcedir + "fonts/" + fontdirectory;
	objtext.CreateText(text, point, weight, italic, fontdirectory, color);
	if (renderer != NULL) {
		objrenderer = renderer;
	}
	objtexture.SetRenderer(objrenderer);
	objtexture.CreateTexture(objtext.textsurface);
}

void aequus::video::window::Object::DisplayObj()
{
	objtexture.Render();
}