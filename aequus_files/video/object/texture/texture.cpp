#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "texture.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Texture::InitTexture(SDL_Surface *surface,
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
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid surface", AVOT,
                            "CreateTexture");
    framework::GetSdlError(framework::IMG);
  } else if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid renderer", AVOT,
                            "CreateTexture");
  } else if (sdlsurface != NULL && sdlrenderer != NULL) {
    sdltexture = SDL_CreateTextureFromSurface(sdlrenderer, sdlsurface);
    if (sdltexture == NULL) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to create texture from surface", AVOT,
                              "CreateTexture");
      framework::GetSdlError(framework::SDL);
    } else {
      pessum::logging::LogLoc(pessum::logging::SUCCESS,
                              "Created texture from surface", AVOT,
                              "CreateTexture");
      width = sdlsurface->w;
      height = sdlsurface->h;
      rotatepoint = new SDL_Point();
      rotatepoint->x = width / 2;
      rotatepoint->y = height / 2;
      sdlsourcerect = NULL;
      sdldestrect = new SDL_Rect;
      sdldestrect->x = 0;
      sdldestrect->y = 0;
      sdldestrect->w = width;
      sdldestrect->h = height;
    }
  }
}

void aequus::video::Texture::DeleteTexture() {
  SDL_FreeSurface(sdlsurface);
  SDL_DestroyTexture(sdltexture);
  sdlsurface = NULL;
  sdltexture = NULL;
}

void aequus::video::Texture::SetRenderer(SDL_Renderer *renderer) {
  sdlrenderer = renderer;
}

void aequus::video::Texture::SetColorMod(std::vector<int> colors) {
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
                            "Failed to set texture colormod", AVOT,
                            "SetColorMod");
    framework::GetSdlError(framework::SDL);
  }
  if (updatea == true && SDL_SetTextureAlphaMod(sdltexture, colormod[3]) != 0) {
    pessum::logging::LogLoc(pessum::logging::WARNING,
                            "Failed to set texture alpha mod", AVOT,
                            "SetColorMod");
  }
}

void aequus::video::Texture::SetColorMod(std::vector<double> colors) {
  std::vector<int> newcolors;
  for (int i = 0; i < colors.size(); i++) {
    newcolors.push_back(colors[i] * 255);
  }
  SetColorMod(newcolors);
}

void aequus::video::Texture::SetBlendMode(BlendMode mode) {
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
    // UpdateTexture()
  }
}

void aequus::video::Texture::Rotate(double theta) { angle = theta; }

void aequus::video::Texture::Rotate(int degree) {
  angle = ((double)degree * (3.141592653) / 180.0);
}

void aequus::video::Texture::Flip(RenderFlip renderflip) {
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

void aequus::video::Texture::SetRotatePoint(int x, int y) {
  rotatex = x;
  rotatey = y;
  if (rotatex != rotatepoint->x) {
    rotatepoint->x = rotatex;
  }
  if (rotatey != rotatepoint->y) {
    rotatepoint->y = rotatey;
  }
}

void aequus::video::Texture::SetRotatePoint(double x, double y) {
  rotatex = scalewidth * x;
  rotatey = scaleheight * y;
  if (rotatex != rotatepoint->x) {
    rotatepoint->x = rotatex;
  }
  if (rotatey != rotatepoint->y) {
    rotatepoint->y = rotatey;
  }
}

void aequus::video::Texture::SetSourceRect(std::vector<int> rect) {
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

void aequus::video::Texture::SetSourceRect(std::vector<double> rect) {
  std::vector<int> newrect;
  newrect.push_back(rect[0] * width);
  newrect.push_back(rect[1] * height);
  newrect.push_back(rect[2] * width);
  newrect.push_back(rect[3] * height);
  SetSourceRect(newrect);
}

void aequus::video::Texture::SetDestRect(std::vector<int> rect) {
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

void aequus::video::Texture::SetDestRect(std::vector<double> rect) {
  std::vector<int> newrect;
  newrect.push_back(rect[0] * width);
  newrect.push_back(rect[1] * height);
  newrect.push_back(rect[2] * width);
  newrect.push_back(rect[3] * height);
  SetDestRect(newrect);
}

void aequus::video::Texture::Scale(int scaledwidth, int scaledheight) {
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

void aequus::video::Texture::Scale(double scaledwidth, double scaledheight) {
  Scale((int)(scaledwidth * width), (int)(scaledheight * height));
}

void aequus::video::Texture::SetPos(int x, int y) {
  posx = x;
  posy = y;
}

void aequus::video::Texture::UpdateTexture() {
  SDL_DestroyTexture(sdltexture);
  InitTexture();
}

void aequus::video::Texture::Display() {
  sdldestrect->x += posx;
  sdldestrect->y += posy;
  if (SDL_RenderCopyEx(sdlrenderer, sdltexture, sdlsourcerect, sdldestrect,
                       angle, rotatepoint, sdlflip) != 0) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to copy texture to renderer", AVOT,
                            "Display");
    framework::GetSdlError(framework::SDL);
  }
  sdldestrect->x -= posx;
  sdldestrect->y -= posy;
}
