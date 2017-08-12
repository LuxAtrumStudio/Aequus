#include "error/error.hpp"

#include <string>

#include "log/log.hpp"
#include "sdl_headers.hpp"

void aequus::error::LogSdlError() {
  log::Log(log::ERROR, "%s", "SDL", SDL_GetError());
}

void aequus::error::LogImgError() {
  log::Log(log::ERROR, "%s", "SDL IMG", IMG_GetError());
}

void aequus::error::LogTtfError() {
  log::Log(log::ERROR, "%s", "SDL TTF", TTF_GetError());
}

void aequus::error::LogMixError() {
  log::Log(log::ERROR, "%s", "SDL MIX", Mix_GetError());
}

std::string aequus::error::GetSdlError() { return SDL_GetError(); }

std::string aequus::error::GetImgError() { return IMG_GetError(); }

std::string aequus::error::GetTtfError() { return TTF_GetError(); }

std::string aequus::error::GetMixError() { return Mix_GetError(); }
