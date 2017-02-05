#include "../../framework/framework.hpp"
#include "../../log_indices.hpp"
#include "../../sdl_headers.hpp"
#include "../video_enums.hpp"
#include "image/image.hpp"
#include "object.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Object::SetRenderer(SDL_Renderer *renderer) {
  sdlrenderer = renderer;
}

void aequus::video::Object::SetColorMod(std::vector<int> colors) {
  bool updatec = false, updatea = false;
  for (int i = 0; i < colormod.size() && i < colors.size(); i++) {
    if (colormod[i] != colors[i]) {
      if (i != 3) {
        updatec = true;
      } else {
        updatea = true;
      }
      colormod[i] = colors[i];
    }
  }
  if (updatec == true &&
      SDL_SetTextureColorMod(sdltexture, colormod[0], colormod[1],
                             colormod[2]) != 0) {
    pessum::logging::LogLoc(pessum::logging::WARNING,
                            "Failed to set texture colormod", LOG_AEQ_VID_OBJ,
                            "SetColorMod");
    framework::GetSdlError(framework::SDL);
  }
  if (updatea == true && SDL_SetTextureAlphaMod(sdltexture, colormod[3]) != 0) {
    pessum::logging::LogLoc(pessum::logging::WARNING,
                            "Failed to set texture alpha mod", LOG_AEQ_VID_OBJ,
                            "SetColorMod");
  }
}

void aequus::video::Object::SetColorMod(std::vector<double> colors) {
  std::vector<int> newcolors;
  for (int i = 0; i < colors.size(); i++) {
    newcolors.push_back(colors[i] * 255);
  }
  SetColorMod(newcolors);
}

void aequus::video::Object::SetBlendMode(BlendMode mode) {
  if (mode != blend) {
    blend = mode;
    if (blend == NONE) {
      sdlblend = SDL_BLENDMODE_NONE;
    } else if (blend == BLEND) {
      sdlblend = SDL_BLENDMODE_BLEND;
    } else if (blend == ADD) {
      sdlblend = SDL_BLENDMODE_ADD;
    } else if (blend == MOD) {
      sdlblend = SDL_BLENDMODE_MOD;
    }
    SDL_SetTextureBlendMode(sdltexture, sdlblend);
    UpdateTexture();
  }
}

void aequus::video::Object::Rotate(double theta) { angle = theta; }

void aequus::video::Object::Rotate(int degree) {
  angle = ((double)degree * (3.141592653) / 180.0);
}

void aequus::video::Object::Flip(RenderFlip renderflip) {
  if (flip != renderflip) {
    flip = renderflip;
    if (flip == NOFLIP) {
      sdlflip = SDL_FLIP_NONE;
    } else if (flip == HORIZONTAL) {
      sdlflip = SDL_FLIP_HORIZONTAL;
    } else if (flip == VERITCAL) {
      sdlflip = SDL_FLIP_VERTICAL;
    }
  }
}

void aequus::video::Object::SetRotatePoint(int x, int y) {
  rotatex = x;
  rotatey = y;
  if (rotatex != sdlrotate->x) {
    sdlrotate->x = rotatex;
  }
  if (rotatey != sdlrotate->y) {
    sdlrotate->y = rotatey;
  }
}

void aequus::video::Object::SetRotatePoint(double x, double y) {
  rotatex = scalewidth * x;
  rotatey = scaleheight * y;
  if (rotatex != sdlrotate->x) {
    sdlrotate->x = rotatex;
  }
  if (rotatey != sdlrotate->y) {
    sdlrotate->y = rotatey;
  }
}

void aequus::video::Object::SetSourceRect(std::vector<int> rect) {
  sourcerect = rect;
  if (sourcerect.size() == 4) {
    sdlsourcerect->x = sourcerect[0];
    sdlsourcerect->y = sourcerect[1];
    sdlsourcerect->w = sourcerect[2];
    sdlsourcerect->h = sourcerect[3];
  } else {
    sdlsourcerect = NULL;
  }
}

void aequus::video::Object::SetSourceRect(std::vector<double> rect) {
  std::vector<int> newrect;
  newrect.push_back(rect[0] * width);
  newrect.push_back(rect[1] * height);
  newrect.push_back(rect[2] * width);
  newrect.push_back(rect[3] * height);
  SetSourceRect(newrect);
}

void aequus::video::Object::SetDestRect(std::vector<int> rect) {
  destrect = rect;
  if (destrect.size() == 4) {
    sdldestrect->x = destrect[0];
    sdldestrect->y = destrect[1];
    sdldestrect->w = destrect[2];
    sdldestrect->h = destrect[3];
  } else {
    sdldestrect = NULL;
  }
}

void aequus::video::Object::SetDestRect(std::vector<double> rect) {
  std::vector<int> newrect;
  newrect.push_back(rect[0] * width);
  newrect.push_back(rect[1] * height);
  newrect.push_back(rect[2] * width);
  newrect.push_back(rect[3] * height);
  SetDestRect(newrect);
}

void aequus::video::Object::Scale(int scaledwidth, int scaledheight) {
  if (scaledwidth == -1) {
    scaledwidth = width;
  }
  if (scaledheight == -1) {
    scaledheight = height;
  }
  scalewidth = scaledwidth;
  scaleheight = scaledheight;
  SetDestRect(std::vector<int>{0, 0, scaledwidth, scaledheight});
}

void aequus::video::Object::Scale(double scaledwidth, double scaledheight) {
  Scale((int)(scaledwidth * width), (int)(scaledheight * height));
}

void aequus::video::Object::SetPos(int x, int y) {
  posx = x;
  posy = y;
}

void aequus::video::Object::UpdateTexture() {
  // SDL_DestroyTexture(sdltexture);
  InitTexture();
}

std::pair<int, int> aequus::video::Object::GetSize() {
  return (std::pair<int, int>(scalewidth, scaleheight));
}

void aequus::video::Object::Display() {
  if (sdltexture != NULL) {
    sdldestrect->x += posx;
    sdldestrect->y += posy;
    if (SDL_RenderCopyEx(sdlrenderer, sdltexture, sdlsourcerect, sdldestrect,
                         angle, sdlrotate, sdlflip) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to copy texture to renderer",
                              LOG_AEQ_VID_OBJ, "Display");
      framework::GetSdlError(framework::SDL);
    }
    sdldestrect->x -= posx;
    sdldestrect->y -= posy;
  }
}

void aequus::video::Object::InitTexture(SDL_Surface *surface,
                                        SDL_Renderer *renderer) {
  if (surface == NULL) {
    surface = sdlsurface;
  }
  if (renderer == NULL) {
    renderer = sdlrenderer;
  }
  if (sdlsurface != NULL) {
    DeleteTexture();
  }
  sdlsurface = surface;
  sdlrenderer = renderer;
  if (sdlsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid surface",
                            LOG_AEQ_VID_OBJ, "CreateTexture");
    framework::GetSdlError(framework::IMG);
  } else if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid renderer",
                            LOG_AEQ_VID_OBJ, "CreateTexture");
  } else if (sdlsurface != NULL && sdlrenderer != NULL) {
    sdltexture = SDL_CreateTextureFromSurface(sdlrenderer, sdlsurface);
    if (sdltexture == NULL) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to create texture from surface",
                              LOG_AEQ_VID_OBJ, "CreateTexture");
      framework::GetSdlError(framework::SDL);
    } else {
      pessum::logging::LogLoc(pessum::logging::SUCCESS,
                              "Created texture from surface", LOG_AEQ_VID_OBJ,
                              "CreateTexture");
      width = sdlsurface->w;
      height = sdlsurface->h;
      scalewidth = width;
      scaleheight = height;
      sdlrotate = new SDL_Point();
      sdlrotate->x = width / 2;
      sdlrotate->y = height / 2;
      sdlsourcerect = NULL;
      sdldestrect = new SDL_Rect;
      sdldestrect->x = 0;
      sdldestrect->y = 0;
      sdldestrect->w = width;
      sdldestrect->h = height;
    }
  }
}

void aequus::video::Object::DeleteTexture() {
  if (sdlsurface != NULL) {
    // SDL_FreeSurface(sdlsurface);
  }
  if (sdltexture != NULL) {
    SDL_DestroyTexture(sdltexture);
  }
  sdlsurface = NULL;
  sdltexture = NULL;
}

void aequus::video::Object::Delete() {}
