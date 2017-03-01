#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../../video.hpp"
#include "../object.hpp"
#include "button.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Button::Init(std::string text, std::string font,
                                 std::string img, SDL_Renderer *renderer,
                                 int inwidth, int inheight) {
  buttonwidth = inwidth;
  buttonheight = inheight;
  filepath = img;
  buttontext = text;
  textfontname = font;
  sdltextcolor.r = textcolor[0];
  sdltextcolor.g = textcolor[1];
  sdltextcolor.b = textcolor[2];
  sdltextcolor.a = textcolor[3];
  GenorateButton(renderer);
  type = 3;
  pessum::logging::Log("SUCCESS", "Loaded button texture", "aeq/vid/obj/but",
                       "Init");
}

void aequus::video::Button::UpdateFile(std::string img) { GenorateButton(); }

void aequus::video::Button::SetTextColor(std::vector<int> color) {
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
  GenorateButton();
}

void aequus::video::Button::SetTextColor(std::vector<double> color) {
  std::vector<int> newcolor;
  for (int i = 0; i < color.size(); i++) {
    newcolor.push_back(color[i] * 255);
  }
  SetTextColor(newcolor);
}

void aequus::video::Button::UpdateString(std::string newstr) {
  buttontext = newstr;
  GenorateButton();
}

void aequus::video::Button::EventCheck(SDL_Event event) {
  if ((event.motion.x >= posx && event.motion.x <= posx + width &&
       event.motion.y >= posy && event.motion.y <= posy + height) ||
      (event.button.x >= posx && event.button.x <= posx + width &&
       event.button.y >= posy && event.button.y <= posy + height)) {
    if (event.type == SDL_MOUSEMOTION) {
      if (currentstate != HOVER) {
        currentstate = HOVER;
        if (hoverstate == COLOR) {
          ColorStateChange();
        } else if (hoverstate == CLIP) {
          ClipStateChange();
        } else if (hoverstate == CUSTOM) {
          hoverfunction();
        }
      }
    } else if (event.type == SDL_MOUSEBUTTONDOWN) {
      if (currentstate != PRESS) {
        currentstate = PRESS;
        if (pressstate == COLOR) {
          ColorStateChange();
        } else if (pressstate == CLIP) {
          ClipStateChange();
        } else if (pressstate == CUSTOM) {
          pressfunction();
        }
      }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
      if (currentstate != RELEASE) {
        currentstate = RELEASE;
        if (releasestate == CUSTOM) {
          releasefunction();
        }
        if (hoverstate == COLOR) {
          ColorStateChange();
        } else if (hoverstate == CLIP) {
          ClipStateChange();
        } else if (hoverstate == CUSTOM) {
          hoverfunction();
        }
      }
    }
  } else {
    if (currentstate != NORMAL) {
      currentstate = NORMAL;
      if (normalstate == COLOR) {
        ColorStateChange();
      } else if (normalstate == CLIP) {
        ClipStateChange();
      } else if (normalstate == CUSTOM) {
        normalfunction();
      }
    }
  }
}

void aequus::video::Button::SetStateCase(ButtonState state, Cases setting) {
  if (state == NORMAL) {
    normalstate = setting;
  }
  if (state == HOVER) {
    normalstate = setting;
  }
  if (state == PRESS) {
    normalstate = setting;
  }
  if (state == RELEASE) {
    normalstate = setting;
  }
}

void aequus::video::Button::SetStateCase(ButtonState state,
                                         void (*function)(void)) {
  if (state == NORMAL) {
    normalstate = CUSTOM;
    normalfunction = function;
  }
  if (state == HOVER) {
    hoverstate = CUSTOM;
    hoverfunction = function;
  }
  if (state == PRESS) {
    pressstate = CUSTOM;
    pressfunction = function;
  }
  if (state == RELEASE) {
    releasestate = CUSTOM;
    releasefunction = function;
  }
}

void aequus::video::Button::SetSize(int newwidth, int newheight) {
  buttonwidth = newwidth;
  buttonheight = newheight;
  GenorateButton();
}

void aequus::video::Button::Delete() {
  DeleteTexture();
  filepath = "";
  buttontext = "";
  textfontname = "";
  textcolor.clear();
}

void aequus::video::Button::GenorateButton(SDL_Renderer *renderer) {
  SDL_Surface *textsurface;
  Font textfont = GetFont(textfontname);
  textsurface = TTF_RenderText_Blended(textfont.GetFont(fontoption),
                                       buttontext.c_str(), sdltextcolor);
  if (textsurface == NULL) {
    pessum::logging::Log("ERROR", "Failed to genorate surface from text",
                         "aeq/vid/obj/but", "GenorateText");
    framework::GetSdlError(framework::TTF);
  }
  SDL_Surface *imgsurface = IMG_Load(filepath.c_str());
  if (imgsurface == NULL) {
    pessum::logging::Log("ERROR", "Failed to load image file: " + filepath,
                         "aeq/vid/obj/but", "Init");
    framework::GetSdlError(framework::IMG);
  }
  int twidth = buttonwidth, theight = buttonheight;
  if (buttonwidth != -1 || buttonheight != -1) {
    if (buttonwidth == -1) {
      twidth = imgsurface->w;
    }
    if (buttonheight == -1) {
      theight = imgsurface->w;
    }
    SDL_Surface *newsurface = NULL;
    newsurface = SDL_CreateRGBSurface(0, twidth, theight, 32, 0, 0, 0, 0);
    SDL_SetSurfaceBlendMode(newsurface, SDL_BLENDMODE_BLEND);
    if (newsurface == NULL) {
      pessum::logging::Log("ERROR", "Failed to genorate scaled surface",
                           "aeq/vid/obj/but", "ScaleSurface");
    }
    SDL_BlitScaled(imgsurface, NULL, newsurface, NULL);
    if (newsurface != NULL) {
      imgsurface = newsurface;
    }
    SDL_FreeSurface(newsurface);
  }

  SDL_Rect recttext;
  recttext.h = textsurface->h;
  recttext.w = textsurface->w;
  recttext.x = 0;
  recttext.y = 0;
  SDL_Rect rectsurface;
  rectsurface.h = textsurface->h;
  rectsurface.w = textsurface->w;
  rectsurface.x = (imgsurface->w - textsurface->w) / 2;
  rectsurface.y = (imgsurface->h - textsurface->h) / 2;
  SDL_BlitScaled(textsurface, &recttext, imgsurface, &rectsurface);
  InitTexture(imgsurface, renderer);
  SDL_FreeSurface(textsurface);
  SDL_FreeSurface(imgsurface);
}

void aequus::video::Button::ColorStateChange() {
  if (currentstate == NORMAL) {
    SetColorMod(std::vector<int>{255, 255, 255});
  }
  if (currentstate == HOVER) {
    SetColorMod(std::vector<int>{59, 237, 186});
  }
  if (currentstate == PRESS) {
    SetColorMod(std::vector<int>{37, 168, 131});
  }
}

void aequus::video::Button::ClipStateChange() {}
