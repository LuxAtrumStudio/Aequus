#include <pessum.h>
#include "../aequus_core.hpp"
#include "../sdl_extention/rect.hpp"
#include "object_base.hpp"

aequus::ObjectBase::ObjectBase() {}

aequus::ObjectBase::ObjectBase(const ObjectBase& obj) {
  sdl_texture = obj.sdl_texture;
  sdl_surface = obj.sdl_surface;
  sdl_renderer = obj.sdl_renderer;
  sdl_base_size = obj.sdl_base_size;
  sdl_source_rect = obj.sdl_source_rect;
  sdl_dest_rect = obj.sdl_dest_rect;
  sdl_rotate_point = obj.sdl_rotate_point;
  rotate_angle = obj.rotate_angle;
  sdl_renderer_flip = obj.sdl_renderer_flip;
  sdl_blend_mode = obj.sdl_blend_mode;
}

aequus::ObjectBase::~ObjectBase() {
  if (sdl_texture != NULL) {
    // SDL_DestroyTexture(sdl_texture);
    // sdl_texture = NULL;
  }
  if (sdl_surface != NULL) {
    // SDL_FreeSurface(sdl_surface);
    // sdl_surface = NULL;
  }
}

int aequus::ObjectBase::Type() { return (AEQ_OBJ_NONE); }

void aequus::ObjectBase::Display() {
  if (sdl_texture != NULL) {
    if (SDL_RenderCopyEx(sdl_renderer, sdl_texture, sdl_source_rect,
                         sdl_dest_rect, rotate_angle, sdl_rotate_point,
                         sdl_renderer_flip) != 0) {
      pessum::Log(pessum::ERROR, "Failed to copy texture to renderer",
                  "aequus/ObjectBase/Display");
      SdlError(SDL);
    }
  }
}

void aequus::ObjectBase::Scale(double x, double y) {
  sdl_dest_rect = Make_Rect(sdl_dest_rect->x, sdl_dest_rect->y,
                            sdl_base_size->w * x, sdl_base_size->h * y);
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w / 2),
                                sdl_dest_rect->y + (sdl_dest_rect->h / 2));
}

void aequus::ObjectBase::Scale(double x) {
  sdl_dest_rect = Make_Rect(sdl_dest_rect->x, sdl_dest_rect->y,
                            sdl_base_size->w * x, sdl_base_size->h * x);
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w / 2),
                                sdl_dest_rect->y + (sdl_dest_rect->h / 2));
}

void aequus::ObjectBase::Scale(int x, int y) {
  sdl_dest_rect = Make_Rect(sdl_dest_rect->x, sdl_dest_rect->y, x, y);
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w / 2),
                                sdl_dest_rect->y + (sdl_dest_rect->h / 2));
}

void aequus::ObjectBase::Scale(int x, bool height) {
  if (height == false) {
    sdl_dest_rect =
        Make_Rect(sdl_dest_rect->x, sdl_dest_rect->y, x,
                  x * ((double)sdl_base_size->h / (double)sdl_base_size->w));
  } else if (height == true) {
    sdl_dest_rect =
        Make_Rect(sdl_dest_rect->x, sdl_dest_rect->y,
                  x * ((double)sdl_base_size->w / (double)sdl_base_size->h), x);
  }
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w / 2),
                                sdl_dest_rect->y + (sdl_dest_rect->h / 2));
}

void aequus::ObjectBase::Translate(int x, int y) {
  if (x != sdl_dest_rect->x && y != sdl_dest_rect->y) {
    sdl_dest_rect = Make_Rect(x, y, sdl_dest_rect->w, sdl_dest_rect->h);
    sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w / 2),
                                  sdl_dest_rect->y + (sdl_dest_rect->h / 2));
  }
}

void aequus::ObjectBase::Rotate(double angle) { rotate_angle = angle; }

void aequus::ObjectBase::SetRotatePoint(int x, int y) {
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + x, sdl_dest_rect->y + y);
}

void aequus::ObjectBase::SetRotatePoint(double x, double y) {
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w * x),
                                sdl_dest_rect->y + (sdl_dest_rect->h * y));
}

void aequus::ObjectBase::SetRotatePoint(int x) {
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + x, sdl_dest_rect->y + x);
}

void aequus::ObjectBase::SetRotatePoint(double x) {
  sdl_rotate_point = Make_Point(sdl_dest_rect->x + (sdl_dest_rect->w * x),
                                sdl_dest_rect->y + (sdl_dest_rect->h * x));
}

void aequus::ObjectBase::CreateSdlTexture() {
  if (sdl_surface == NULL) {
    pessum::Log(pessum::WARNING, "No SDL surface created",
                "aequus/ObjectBase/CreateSdlTexture");
  } else if (sdl_renderer == NULL) {
    pessum::Log(pessum::WARNING, "NO SDL renderer created",
                "aequus/ObjectBase/CreateSdlTexture");
  } else {
    if (sdl_texture != NULL) {
      SDL_DestroyTexture(sdl_texture);
      sdl_texture = NULL;
    }
    sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);
    if (sdl_texture == NULL) {
      pessum::Log(pessum::ERROR, "Failed to create texture from surface",
                  "aequus/ObjectBase/CreateSdlTexture");
      SdlError(SDL);
    } else {
      sdl_base_size = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_dest_rect = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_source_rect = Make_Rect(0, 0, sdl_surface->w, sdl_surface->h);
      sdl_rotate_point = Make_Point(sdl_surface->w / 2, sdl_surface->h / 2);
    }
  }
}
