#include "error.hpp"

#include <string>

#include <pessum/pessum.hpp>

#include "../sdl_headers.hpp"

void aequus::error::LogSdlError() {
  pessum::Log(pessum::ERROR, "%s", "SDL", SDL_GetError());
}

void aequus::error::LogImgError() {
  pessum::Log(pessum::ERROR, "%s", "SDL IMG", IMG_GetError());
}

void aequus::error::LogTtfError() {
  pessum::Log(pessum::ERROR, "%s", "SDL TTF", TTF_GetError());
}

void aequus::error::LogMixError() {
  pessum::Log(pessum::ERROR, "%s", "SDL MIX", Mix_GetError());
}

std::string aequus::error::GetSdlError() { return SDL_GetError(); }

std::string aequus::error::GetImgError() { return IMG_GetError(); }

std::string aequus::error::GetTtfError() { return TTF_GetError(); }

std::string aequus::error::GetMixError() { return Mix_GetError(); }

