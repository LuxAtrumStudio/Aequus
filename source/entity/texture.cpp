#include "entity/texture.hpp"

#include "entity/surface.hpp"
#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"
#include "types.hpp"

aequus::entity::Texture::Texture() {}

aequus::entity::Texture::Texture(Surface surface_) : surface(surface_) {
  GenerateTexture();
}

aequus::entity::Texture::Texture(const Texture& copy)
    : surface(copy.surface),
      blend_mode_(copy.blend_mode_),
      color_mod_(copy.color_mod_),
      sdl_texture_(copy.sdl_texture_) {}

aequus::entity::Texture::~Texture() { DestroyTexture(); }

void aequus::entity::Texture::SetSurface(Surface surface_) {
  surface = surface_;
}

void aequus::entity::Texture::CreateTexture() { GenerateTexture(); }

void aequus::entity::Texture::DeleteTexture() { DestroyTexture(); }

void aequus::entity::Texture::SetBlendMode(unsigned int blend_mode) {
  if (blend_mode_ != blend_mode) {
    blend_mode_ = blend_mode;
    SDL_BlendMode sdl_blend;
    if (blend_mode_ == BLENDMODE_NONE) {
      sdl_blend = SDL_BLENDMODE_NONE;
    } else if (blend_mode_ == BLENDMODE_BLEND) {
      sdl_blend = SDL_BLENDMODE_BLEND;
    } else if (blend_mode_ == BLENDMODE_ADD) {
      sdl_blend = SDL_BLENDMODE_ADD;
    } else if (blend_mode_ == BLENDMODE_MOD) {
      sdl_blend = SDL_BLENDMODE_MOD;
    }
    if (IsValid() == true &&
        SDL_SetTextureBlendMode(*sdl_texture_, sdl_blend) != 0) {
      log::Log(log::ERROR, "Failed to set texture blend mode",
               "aequus::entity::Texture::SetBlendMode");
      error::LogSdlError();
    }
  }
}

void aequus::entity::Texture::SetColorMod(Color color_mod) {
  if (color_mod_ != color_mod) {
    color_mod_ = color_mod;
    if (IsValid() == true) {
      if (SDL_SetTextureColorMod(*sdl_texture_, color_mod_.r, color_mod_.g,
                                 color_mod_.b) != 0) {
        log::Log(log::ERROR, "Failed to set texture color mod",
                 "aequus::entity::Texture::SetColorMod");
        error::LogSdlError();
      }
      if (SDL_SetTextureAlphaMod(*sdl_texture_, color_mod_.a) != 0) {
        log::Log(log::ERROR, "Failed to set texture alpha mod",
                 "aequus::entity::Texture::SetColorMod");
        error::LogSdlError();
      }
    }
  }
}

bool aequus::entity::Texture::IsValid() {
  if (sdl_texture_ != NULL && *sdl_texture_ != NULL) {
    return true;
  } else {
    return false;
  }
}

SDL_Texture* aequus::entity::Texture::SdlTexture() {
  if (IsValid() == true) {
    return *sdl_texture_;
  } else {
    return NULL;
  }
}

void aequus::entity::Texture::GenerateTexture() {
  if (surface.IsValid() == true) {
    log::Log(log::ERROR, "SDL surface not defined",
             "aequus::entity::Texture::GenerateTexture");
  } else {
    SDL_Renderer* renderer = SDL_CreateSoftwareRenderer(surface.SdlSurface());
    if (renderer == NULL) {
      log::Log(log::ERROR, "Failed to create renderer from surface",
               "aequus::entity::Texture::GenerateTexture");
    } else {
      sdl_texture_ = std::make_shared<SDL_Texture*>(
          SDL_CreateTextureFromSurface(renderer, surface.SdlSurface()));
      if (*sdl_texture_ == NULL) {
        log::Log(log::ERROR, "Failed to create texture form surface",
                 "aequus::entity::Texture::GenerateTexture");
      }
    }
  }
}

void aequus::entity::Texture::DestroyTexture() {
  if (sdl_texture_.use_count() == 1) {
    if (*sdl_texture_ != NULL) {
      SDL_DestroyTexture(*sdl_texture_);
    }
  }
  sdl_texture_ = NULL;
}
