#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../../video.hpp"
#include "../texture/texture.hpp"
#include "text.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Text::Init(std::string str, std::string fontname,
                               SDL_Renderer *renderer) {
  text = str;
  textfont = fontname;
  textformat = BLEND;
  sdltextcolor.r = textcolor[0];
  sdltextcolor.g = textcolor[1];
  sdltextcolor.b = textcolor[2];
  sdltextcolor.a = textcolor[3];
  sdlbackgroundcolor.r = backgroundcolor[0];
  sdlbackgroundcolor.g = backgroundcolor[1];
  sdlbackgroundcolor.b = backgroundcolor[2];
  sdlbackgroundcolor.a = backgroundcolor[3];
  GenorateText(renderer);
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Loaded text texture",
                          AVOTEXT, "Init");
}

void aequus::video::Text::SetTextColor(std::vector<int> color) {
  if (color.size() == 0) {
    textcolor[0] = 255;
    textcolor[1] = 255;
    textcolor[2] = 255;
    textcolor[3] = 255;
  } else {
    for (int i = 0; i < color.size() && i < textcolor.size(); i++) {
      textcolor[i] = color[i];
    }
  }
  sdltextcolor.r = textcolor[0];
  sdltextcolor.g = textcolor[1];
  sdltextcolor.b = textcolor[2];
  sdltextcolor.a = textcolor[3];
  GenorateText();
}

void aequus::video::Text::SetTextColor(std::vector<double> color) {
  std::vector<int> newcolor;
  for (int i = 0; i < color.size(); i++) {
    newcolor.push_back(color[i] * 255);
  }
  SetTextColor(newcolor);
}

void aequus::video::Text::SetBackgroundColor(std::vector<int> color) {
  if (color.size() == 0) {
    backgroundcolor[0] = 255;
    backgroundcolor[1] = 255;
    backgroundcolor[2] = 255;
    backgroundcolor[3] = 255;
  } else {
    for (int i = 0; i < color.size() && i < backgroundcolor.size(); i++) {
      backgroundcolor[i] = color[i];
    }
  }
  sdlbackgroundcolor.r = backgroundcolor[0];
  sdlbackgroundcolor.g = backgroundcolor[1];
  sdlbackgroundcolor.b = backgroundcolor[2];
  sdlbackgroundcolor.a = backgroundcolor[3];
  GenorateText();
}

void aequus::video::Text::SetBackgroundColor(std::vector<double> color) {
  std::vector<int> newcolor;
  for (int i = 0; i < color.size(); i++) {
    newcolor.push_back(color[i] * 255);
  }
  SetBackgroundColor(newcolor);
}

void aequus::video::Text::UpdateString(std::string newstr) {
  text = newstr;
  GenorateText();
}

void aequus::video::Text::UpdateText() { GenorateText(); }

void aequus::video::Text::Delete() {
  DeleteTexture();
  text = "";
  textfont = "";
  textcolor.clear();
  backgroundcolor.clear();
}

void aequus::video::Text::GenorateText(SDL_Renderer *renderer) {
  SDL_Surface *textsurface;
  Font font = GetFont(textfont);
  if (textformat == SOLID) {
    textsurface =
        TTF_RenderText_Solid(font.GetFont(REGULAR), text.c_str(), sdltextcolor);
  }
  if (textformat == SHADED) {
    textsurface = TTF_RenderText_Shaded(font.GetFont(REGULAR), text.c_str(),
                                        sdltextcolor, sdlbackgroundcolor);
  }
  if (textformat == BLEND) {
    textsurface = TTF_RenderText_Blended(font.GetFont(REGULAR), text.c_str(),
                                         sdltextcolor);
  }
  if (textsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to genorate surface from text", AVOTEXT,
                            "GenorateText");
    framework::GetSdlError(framework::TTF);
  }
  InitTexture(textsurface, renderer);
}
