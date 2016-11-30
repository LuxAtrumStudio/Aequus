#include "../../../pessum_files/logging.h"
#include "../../aequus_headers.h"
#include "../../sdl_headers.h"
#include "object.h"
#include <string>
#include <vector>

void aequus::video::Object::InitalizeObj(SDL_Renderer *renderer, int counter,
                                         std::string resource) {
  logloc = pessum::logging::AddLogLocation(
      "aequus_files/video/object/object.cpp[" + std::to_string(counter) + "]/");
  resourcedir = resource;
  objrenderer = renderer;
}

void aequus::video::Object::CreateImgObj(std::string filepath,
                                         SDL_Renderer *renderer) {
  if (filepath != "") {
    filepath = resourcedir + "images/" + filepath;
    filepath = "resources/images/" + filepath;
    objsurface.LoadSurface(filepath);
  }
  if (renderer != NULL) {
    objrenderer = renderer;
  }
  if (objsurface.sdlsurface != NULL) {
    objtexture.SetRenderer(objrenderer);
    objtexture.CreateTexture(objsurface.sdlsurface);
  }
  posx = 0;
  posy = 0;
  if (objtexture.sdltexture != NULL) {
    sizex = objsurface.sdlsurface->w;
    sizey = objsurface.sdlsurface->h;
    rotateaxisx = sizex / 2;
    rotateaxisy = sizey / 2;
    objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
    destsizex = sizex;
    destsizey = sizey;
  }
  rotateangle = 0;
  objtype = IMAGE;
}

void aequus::video::Object::CreateTextObj(
    std::string text, int point, double red, double green, double blue,
    double alpha, aequus::video::Text::FontWeight weight, bool italic,
    std::string fontdirectory, SDL_Renderer *renderer) {
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

void aequus::video::Object::Scale(int x, int y) {
  sizex = x;
  sizey = y;
  int rect[4] = {posx, posy, sizex, sizey};
  objtexture.SetDestinationRect(rect);
  if (objtype == BUTTON) {
    UpdateButton(posx + 1, posy + 1, 0);
    UpdateButton(posx, posy, 0);
  }
}

void aequus::video::Object::ScalePercent(double x, double y) {
  destsizex = x * sizex;
  destsizey = y * sizey;
  scalex = x;
  scaley = y;
  int rect[4] = {posx, posy, destsizex, destsizey};
  objtexture.SetDestinationRect(rect);
  if (objtype == BUTTON) {
    UpdateButton(posx + 1, posy + 1, 0);
    UpdateButton(posx, posy, 0);
  }
}

void aequus::video::Object::Translate(int x, int y) {
  posx = posy + x;
  posy = posy + y;
  int rect[4] = {posx, posy, sizex, sizey};
  objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::SetPos(int x, int y) {
  posx = x;
  posy = y;
  int rect[4] = {posx, posy, sizex, sizey};
  objtexture.SetDestinationRect(rect);
}

void aequus::video::Object::SetColor(double red, double green, double blue,
                                     double alpha) {
  colormod[0] = red;
  colormod[1] = green;
  colormod[2] = blue;
  colormod[3] = alpha;
  objtexture.SetColorMod(colormod);
}

void aequus::video::Object::SetClipSpace(int startx, int starty, int width,
                                         int height) {
  if (clipx != startx || clipy != starty || clipsizex != width ||
      clipsizey != height) {
    clipx = startx;
    clipy = starty;
    clipsizex = width;
    clipsizey = height;
    destsizex = clipsizex * scalex;
    destsizey = clipsizey * scaley;
    int rect[4] = {clipx, clipy, clipsizex, clipsizey};
    int rectdest[4] = {posx, posy, destsizex, destsizey};
    objtexture.SetSourceRect(rect);
    objtexture.SetDestinationRect(rectdest);
  }
}

void aequus::video::Object::Rotate(double angle, bool degree, int axisx,
                                   int axisy) {
  rotateangle = angle;
  if (axisx != -1 && axisy != -1) {
    rotateaxisx = axisx;
    rotateaxisy = axisy;
    objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
  }
  objtexture.Rotate(rotateangle, degree);
}

void aequus::video::Object::DisplayObj() { objtexture.Render(); }

void aequus::video::Object::CreateButton(std::string text,
                                         std::string imagepath, bool whitetext,
                                         bool clipbutton, bool imagebutton,
                                         int width, int height,
                                         SDL_Renderer *renderer) {
  imagepath = resourcedir + "images/" + imagepath;
  int surfaceheight = 0, textheight = 0;
  int surfacewidth = 0, textwidth = 0;
  scalex = 1;
  scaley = 1;
  int pt = 12;
  bool sizing = true, shrink = false, grow = false;
  objsurface.LoadSurface(imagepath);
  if (width != -1 || height != -1) {
    if (width == -1) {
      width = objsurface.sdlsurface->w;
    }
    if (height == -1) {
      height = objsurface.sdlsurface->h;
    }
    if (clipbutton == true) {
      objsurface.ScaleSurface(width, height * 4);
    } else if (clipbutton == false) {
      objsurface.ScaleSurface(width, height);
    }
  }
  surfacewidth = objsurface.sdlsurface->w;
  surfaceheight = objsurface.sdlsurface->h;
  if (clipbutton == true) {
    surfaceheight = surfaceheight / 4;
  }
  if (text.size() != 0 && imagebutton == false) {
    objtext.CreateFont();
    if (whitetext == true) {
      double color[4] = {1, 1, 1, 1};
      objtext.SetColor(color);
    }
    while (sizing == true) {
      objtext.SetPoint(pt);
      objtext.FindSize(&textwidth, &textheight, text);
      if (textwidth > surfacewidth - 10 || textheight > surfaceheight - 10) {
        pt--;
        shrink = true;
        if (grow == true) {
          sizing = false;
        }
      } else if (textwidth < (float)surfacewidth / 0.9 &&
                 textheight < (float)surfaceheight / 0.9) {
        pt++;
        grow = true;
        if (shrink == true) {
          sizing = false;
        }
      } else {
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
    SDL_BlitScaled(objtext.textsurface, &recttext, objsurface.sdlsurface,
                   &rectsurface);
    if (clipbutton == true) {
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y =
          ((surfaceheight - objtext.textsurface->h) / 2) + surfaceheight;
      SDL_BlitScaled(objtext.textsurface, &recttext, objsurface.sdlsurface,
                     &rectsurface);
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y =
          ((surfaceheight - objtext.textsurface->h) / 2) + (2 * surfaceheight);
      SDL_BlitScaled(objtext.textsurface, &recttext, objsurface.sdlsurface,
                     &rectsurface);
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y =
          ((surfaceheight - objtext.textsurface->h) / 2) + (3 * surfaceheight);
      SDL_BlitScaled(objtext.textsurface, &recttext, objsurface.sdlsurface,
                     &rectsurface);
    }
  }
  if (imagebutton == true) {
    Surface imagesurface;
    text = resourcedir + "images/" + text;
    imagesurface.LoadSurface(text);
    SDL_Rect rectimage;
    if (imagesurface.sdlsurface->w > surfacewidth ||
        imagesurface.sdlsurface->h > surfaceheight) {
      rectimage.w = imagesurface.sdlsurface->w;
      rectimage.h = imagesurface.sdlsurface->h;
    } else {
      rectimage.w = surfacewidth;
      rectimage.h = surfaceheight;
    }
    rectimage.x = 0;
    rectimage.y = 0;
    SDL_Rect rectsurface;
    rectsurface.h = surfaceheight;
    rectsurface.w = surfacewidth;
    rectsurface.x = (surfacewidth - imagesurface.sdlsurface->w) / 2;
    rectsurface.y = (surfaceheight - imagesurface.sdlsurface->h) / 2;
    if (rectsurface.x < 0) {
      rectsurface.x = 0;
    }
    if (rectsurface.y < 0) {
      rectsurface.y = 0;
    }
    SDL_BlitScaled(imagesurface.sdlsurface, &rectimage, objsurface.sdlsurface,
                   &rectsurface);
    if (clipbutton == true) {
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y =
          ((surfaceheight - imagesurface.sdlsurface->h) / 2) + surfaceheight;
      if (rectsurface.y < surfaceheight) {
        rectsurface.y = surfaceheight;
      }
      SDL_BlitScaled(imagesurface.sdlsurface, &rectimage, objsurface.sdlsurface,
                     &rectsurface);
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y = ((surfaceheight - imagesurface.sdlsurface->h) / 2) +
                      (2 * surfaceheight);
      if (rectsurface.y < surfaceheight * 2) {
        rectsurface.y = surfaceheight * 2;
      }
      SDL_BlitScaled(imagesurface.sdlsurface, &rectimage, objsurface.sdlsurface,
                     &rectsurface);
      rectsurface.h = surfaceheight;
      rectsurface.w = surfacewidth;
      rectsurface.y = ((surfaceheight - imagesurface.sdlsurface->h) / 2) +
                      (3 * surfaceheight);
      if (rectsurface.y < surfaceheight * 3) {
        rectsurface.y = surfaceheight * 3;
      }
      SDL_BlitScaled(imagesurface.sdlsurface, &rectimage, objsurface.sdlsurface,
                     &rectsurface);
    }
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
    SetClipSpace(0, 0, surfacewidth, surfaceheight);
  }
  for (int a = 0; a < 4; a++) {
    savedcolormod[a] = 1;
  }
}

bool aequus::video::Object::UpdateButton(int mousex, int mousey,
                                         int mousestate) {
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
      } else {
        SetColor(savedcolormod[0], savedcolormod[1], savedcolormod[2],
                 savedcolormod[3]);
      }
    } else {
      SetColor(savedcolormod[0], savedcolormod[1], savedcolormod[2],
               savedcolormod[3]);
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
      } else {
        SetClipSpace(0, 0, sizex, sizey / 4);
      }
    } else {
      SetClipSpace(0, 0, sizex, sizey / 4);
    }
  }
  return (clicked);
}

void aequus::video::Object::LoadDefaults(int width, int height) {
  posx = 0;
  posy = 0;
  if (objtexture.sdltexture != NULL) {
    if (width == -1) {
      sizex = objsurface.sdlsurface->w;
    } else if (width != -1) {
      sizex = width;
    }
    if (height == -1) {
      sizey = objsurface.sdlsurface->h;
    } else if (height != -1) {
      sizey = height;
    }
    rotateaxisx = sizex / 2;
    rotateaxisy = sizey / 2;
    objtexture.SetRotatePoint(rotateaxisx, rotateaxisy);
    destsizex = sizex;
    destsizey = sizey;
  }
  rotateangle = 0;
  objtype = IMAGE;
}
