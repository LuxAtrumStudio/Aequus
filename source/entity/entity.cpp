#include "entity/entity.hpp"

#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"
#include "types.hpp"

aequus::entity::Object::Object() {}

aequus::entity::Object::Object(const Object& copy) {}

aequus::entity::Object::Object(std::shared_ptr<SDL_Renderer*> renderer)
    : sdl_renderer_(renderer) {}

aequus::entity::Object::~Object() {}

void aequus::entity::Object::Display() {
  if (texture_.IsValid()) {
    if (SDL_RenderCopyEx(*sdl_renderer_, texture_.SdlTexture(), &source_rect_,
                         &dest_rect_, rotate_angle_, &rotate_point_,
                         sdl_render_flip_) != 0) {
      log::Log(log::ERROR, "Failed to copy texture to renderer",
               "aequus::entity::Object::Display");
      error::LogSdlError();
    }
  }
}

void aequus::entity::Object::Scale(double w, double h) {
  dest_rect_.w *= w;
  dest_rect_.h *= h;
}

void aequus::entity::Object::ScaleWidth(double w) { dest_rect_.w *= w; }

void aequus::entity::Object::ScaleHeight(double h) { dest_rect_.h *= h; }

void aequus::entity::Object::SetSize(int w, int h) {
  dest_rect_.w = w;
  dest_rect_.h = h;
}

void aequus::entity::Object::SetWidth(int w) { dest_rect_.w = w; }

void aequus::entity::Object::SetHeight(int h) { dest_rect_.h = h; }

void aequus::entity::Object::Translate(int x, int y) {
  dest_rect_.x += x;
  dest_rect_.y += y;
}

void aequus::entity::Object::TranslateX(int x) { dest_rect_.x += x; }

void aequus::entity::Object::TranslateY(int y) { dest_rect_.y += y; }

void aequus::entity::Object::SetPosition(int x, int y) {
  dest_rect_.x = x;
  dest_rect_.y = y;
}

void aequus::entity::Object::SetPosX(int x) { dest_rect_.x = x; }

void aequus::entity::Object::SetPosY(int y) { dest_rect_.y = y; }

void aequus::entity::Object::ScaleSource(double w, double h) {
  source_rect_.w *= w;
  source_rect_.h *= h;
}

void aequus::entity::Object::ScaleSourceWidth(double w) { source_rect_.w *= w; }

void aequus::entity::Object::ScaleSourceHeight(double h) {
  source_rect_.h *= h;
}

void aequus::entity::Object::SetSourceSize(int w, int h) {
  source_rect_.w = w;
  source_rect_.h = h;
}

void aequus::entity::Object::SetSourceWidth(int w) { source_rect_.w = w; }

void aequus::entity::Object::SetSourceHeight(int h) { source_rect_.h = h; }

void aequus::entity::Object::TranslateSource(int x, int y) {
  source_rect_.x += x;
  source_rect_.y += y;
}

void aequus::entity::Object::TranslateSourceX(int x) { source_rect_.x += x; }

void aequus::entity::Object::TranslateSourceY(int y) { source_rect_.y += y; }

void aequus::entity::Object::SetSourcePosition(int x, int y) {
  source_rect_.x = x;
  source_rect_.y = y;
}

void aequus::entity::Object::SetSourcePosX(int x) { source_rect_.x = x; }

void aequus::entity::Object::SetSourcePosY(int y) { source_rect_.y = y; }

void aequus::entity::Object::SetRect(Rect rect) { dest_rect_ = rect; }

void aequus::entity::Object::SetRect(int x, int y, int w, int h) {
  dest_rect_ = {x, y, w, h};
}

void aequus::entity::Object::SetSourceRect(Rect rect) { source_rect_ = rect; }

void aequus::entity::Object::SetSourceRect(int x, int y, int w, int h) {
  source_rect_ = {x, y, w, h};
}

void aequus::entity::Object::Rotate(double angle) { rotate_angle_ += angle; }

void aequus::entity::Object::SetRotation(double angle) {
  rotate_angle_ = angle;
}

void aequus::entity::Object::SetRotatePoint(Point rotate_point) {
  rotate_point_ = rotate_point;
}

void aequus::entity::Object::SetRenderFlip(unsigned int render_flip) {
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

aequus::Rect aequus::entity::Object::GetRect() { return dest_rect_; }

aequus::Rect aequus::entity::Object::GetSourceRect() { return source_rect_; }
