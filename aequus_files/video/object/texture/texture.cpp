#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "texture.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Texture::Init(std::string filepath,
                                  SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  imagepath = filepath;
  sdlsurface = IMG_Load(imagepath.c_str());
  if (sdlsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to load image file: " + imagepath, AVOT,
                            "Init");
    framework::GetSdlError(framework::IMG);
  } else if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Invalid renderer", AVOT,
                            "Init");
  } else if (sdlsurface != NULL && sdlrenderer != NULL) {
    sdltexture = SDL_CreateTextureFromSurface(sdlrenderer, sdlsurface);
    if (sdltexture == NULL) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to create texture from surface", AVOT,
                              "Init");
      framework::GetSdlError(framework::SDL);
    } else {
      pessum::logging::LogLoc(pessum::logging::SUCCESS,
                              "Loaded texture from: " + imagepath, AVOT,
                              "Init");
      width = sdlsurface->w;
      height = sdlsurface->h;
      rotatepoint = new SDL_Point();
      rotatepoint->x = width / 2;
      rotatepoint->y = height / 2;
      sdlsourcerect = NULL;
      sdldestrect = NULL;
    }
  }
}

void aequus::video::Texture::Delete() {
  SDL_FreeSurface(sdlsurface);
  SDL_DestroyTexture(sdltexture);
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
  rotatex = width * x;
  rotatey = height * y;
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
    sdldestrect->x = destrect[0] + posx;
    sdldestrect->y = destrect[1] + posy;
    sdldestrect->w = destrect[2] + posx;
    sdldestrect->h = destrect[3] + posy;
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
  Scale((int)scaledwidth * width, (int)scaleheight * height);
}

void aequus::video::Texture::SetPos(int x, int y) {
  posx = x;
  posy = y;
}

void aequus::video::Texture::Display() {
  if (SDL_RenderCopyEx(sdlrenderer, sdltexture, sdlsourcerect, sdldestrect,
                       angle, rotatepoint, sdlflip) != 0) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to copy texture to renderer", AVOT,
                            "Display");
    framework::GetSdlError(framework::SDL);
  }
}
