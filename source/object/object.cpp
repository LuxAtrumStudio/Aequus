#include <iostream>

#include "object/object.hpp"

#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"
#include "types.hpp"

aequus::object::Object::Object() {}

aequus::object::Object::Object(const Object& copy) {}

aequus::object::Object::Object(std::shared_ptr<SDL_Renderer*> renderer)
    : sdl_renderer_(renderer) {}

aequus::object::Object::~Object() {}

void aequus::object::Object::Display() {
  if (sdl_texture_ != NULL) {
    if (SDL_RenderCopyEx(*sdl_renderer_, *sdl_texture_, &dest_rect_,
                         &dest_rect_, rotate_angle_, &rotate_point_,
                         sdl_render_flip_) != 0) {
      log::Log(log::ERROR, "Failed to copy texture to renderer",
               "aequus::object::Object::Display");
      error::LogSdlError();
    }
  }
}

void aequus::object::Object::Scale(double w, double h) {
  dest_rect_.w *= w;
  dest_rect_.h *= h;
}

void aequus::object::Object::ScaleWidth(double w) { dest_rect_.w *= w; }

void aequus::object::Object::ScaleHeight(double h) { dest_rect_.h *= h; }

void aequus::object::Object::SetSize(int w, int h) {
  dest_rect_.w = w;
  dest_rect_.h = h;
}

void aequus::object::Object::SetWidth(int w) { dest_rect_.w = w; }

void aequus::object::Object::SetHeight(int h) { dest_rect_.h = h; }

void aequus::object::Object::Translate(int x, int y) {
  dest_rect_.x += x;
  dest_rect_.y += y;
}

void aequus::object::Object::TranslateX(int x) { dest_rect_.x += x; }

void aequus::object::Object::TranslateY(int y) { dest_rect_.y += y; }

void aequus::object::Object::SetPosition(int x, int y) {
  dest_rect_.x = x;
  dest_rect_.y = y;
}

void aequus::object::Object::SetPosX(int x) { dest_rect_.x = x; }

void aequus::object::Object::SetPosY(int y) { dest_rect_.y = y; }

void aequus::object::Object::ScaleSource(double w, double h) {
  source_rect_.w *= w;
  source_rect_.h *= h;
}

void aequus::object::Object::ScaleSourceWidth(double w) { source_rect_.w *= w; }

void aequus::object::Object::ScaleSourceHeight(double h) {
  source_rect_.h *= h;
}

void aequus::object::Object::SetSourceSize(int w, int h) {
  source_rect_.w = w;
  source_rect_.h = h;
}

void aequus::object::Object::SetSourceWidth(int w) { source_rect_.w = w; }

void aequus::object::Object::SetSourceHeight(int h) { source_rect_.h = h; }

void aequus::object::Object::TranslateSource(int x, int y) {
  source_rect_.x += x;
  source_rect_.y += y;
}

void aequus::object::Object::TranslateSourceX(int x) { source_rect_.x += x; }

void aequus::object::Object::TranslateSourceY(int y) { source_rect_.y += y; }

void aequus::object::Object::SetSourcePosition(int x, int y) {
  source_rect_.x = x;
  source_rect_.y = y;
}

void aequus::object::Object::SetSourcePosX(int x) { source_rect_.x = x; }

void aequus::object::Object::SetSourcePosY(int y) { source_rect_.y = y; }

void aequus::object::Object::SetRect(Rect rect) { dest_rect_ = rect; }

void aequus::object::Object::SetRect(int x, int y, int w, int h) {
  dest_rect_ = {x, y, w, h};
}

void aequus::object::Object::SetSourceRect(Rect rect) { source_rect_ = rect; }

void aequus::object::Object::SetSourceRect(int x, int y, int w, int h) {
  source_rect_ = {x, y, w, h};
}

void aequus::object::Object::Rotate(double angle) { rotate_angle_ += angle; }

void aequus::object::Object::SetRotation(double angle) {
  rotate_angle_ = angle;
}

void aequus::object::Object::SetBlendMode(unsigned int blend_mode) {
  if (blend_mode_ != blend_mode) {
    blend_mode_ = blend_mode;
    SDL_BlendMode sdl_blend_mode;
    if (blend_mode_ == BLENDMODE_NONE) {
      sdl_blend_mode = SDL_BLENDMODE_NONE;
    } else if (blend_mode_ == BLENDMODE_BLEND) {
      sdl_blend_mode = SDL_BLENDMODE_BLEND;
    } else if (blend_mode_ == BLENDMODE_ADD) {
      sdl_blend_mode = SDL_BLENDMODE_ADD;
    } else if (blend_mode_ == BLENDMODE_MOD) {
      sdl_blend_mode = SDL_BLENDMODE_MOD;
    }
    if (sdl_texture_ != NULL &&
        SDL_SetTextureBlendMode(*sdl_texture_, sdl_blend_mode) != 0) {
      log::Log(log::ERROR, "Failed to set texture blend mode",
               "aequus::object::Object::SetBlendMode");
      error::LogSdlError();
    }
  }
}

void aequus::object::Object::SetRenderFlip(unsigned int render_flip) {
  if (render_flip_ != render_flip) {
    render_flip_ = render_flip;
    if (render_flip_ == FLIP_NONE) {
      sdl_render_flip_ = SDL_FLIP_NONE;
    } else if (render_flip_ == FLIP_HORIZONTAL) {
      sdl_render_flip_ = SDL_FLIP_HORIZONTAL;
    } else if (render_flip_ == FLIP_VERTICAL) {
      sdl_render_flip_ = SDL_FLIP_VERTICAL;
    }
  }
}

aequus::Rect aequus::object::Object::GetRect() { return dest_rect_; }

aequus::Rect aequus::object::Object::GetSourceRect() { return source_rect_; }

void aequus::object::Object::CreateTexture() {
  if (*sdl_surface_ == NULL) {
    log::Log(log::ERROR, "No SDL surface defined",
             "aequus::object::Object::CreateTexture");
  } else if (*sdl_renderer_ == NULL) {
    log::Log(log::ERROR, "No SDL renderer defined",
             "aequus::object::Object::CreateTexture");
  } else {
    if (sdl_texture_ != NULL) {
      DestroyTexture();
    }
    sdl_texture_ = std::make_shared<SDL_Texture*>(
        SDL_CreateTextureFromSurface(*sdl_renderer_, *sdl_surface_));
    if (*sdl_texture_ == NULL) {
      log::Log(log::ERROR, "Failed to create texture from surface",
               "aequus::object::Object::CreateTexture");
      error::LogSdlError();
    } else {
      source_rect_ = {0, 0, (*sdl_surface_)->w, (*sdl_surface_)->h};
      dest_rect_ = source_rect_;
      rotate_point_ = {(*sdl_surface_)->w / 2, (*sdl_surface_)->h / 2};
      SetBlendMode(blend_mode_);
    }
  }
}

void aequus::object::Object::DestroyTexture() {
  if (sdl_texture_.use_count() == 1) {
    SDL_DestroyTexture(*sdl_texture_);
  }
  sdl_texture_ = NULL;
}
