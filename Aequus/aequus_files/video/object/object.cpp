#include "object.h"
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "../../aequus_headers.h"
#include "../../../pessum_files/logging.h"

void aequus::video::window::Object::InitalizeObj(SDL_Renderer * renderer, int counter)
{
	logloc = pessum::logging::AddLogLocation("aequus_files/video/object/object.cpp[" + std::to_string(counter) + "]/");
	objrenderer = renderer;
}

void aequus::video::window::Object::CreateImgObj(std::string filepath, SDL_Renderer * renderer)
{
	objsurface.LoadSurface(filepath);
	objtexture.SetRenderer(renderer);
	objtexture.CreateTexture(objsurface.sdlsurface);
}

void aequus::video::window::Object::CreateTextObj(std::string text, SDL_Renderer * renderer, int point, aequus::video::window::Text::FontWeight weight, bool italic, std::string fontdirectory, double color[4])
{
	objtext.CreateText(text, point, weight, italic, fontdirectory, color);
	objtexture.SetRenderer(renderer);
	objtexture.CreateTexture(objtext.textsurface);
}

void aequus::video::window::Object::DisplayObj()
{
	objtexture.Render();
}