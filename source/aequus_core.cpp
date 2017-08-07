#include "aequus_core.hpp"

#include <pessum/pessum.hpp>

#include "error/error.hpp"
#include "sdl_headers.hpp"

namespace aequus {
  bool aequus_quit_ = false;
}  // namespace aequus

bool aequus::InitAequus() {
  pessum::Log(pessum::INFO, "Aequus Version: %i.%i.%i", "aequus::InitAequus",
              AEQUUS_VERSION_MAJOR, AEQUUS_VERSION_MINOR, AEQUUS_VERSION_PATCH);
  if (InitSdl() == false) {
    return false;
  }
  if (InitImage() == false) {
    return false;
  }
  if (InitTtf() == false) {
    return false;
  }
  if (InitMix() == false) {
    return false;
  }
  int major = 0, minor = 0, patch = 0;
  SdlVersion(major, minor, patch);
  pessum::Log(pessum::INFO, "SDL Version: %i.%i.%i", "aequus::InitAequus",
              major, minor, patch);
  return true;
}

bool aequus::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL", "aequus::InitSdl");
    error::LogSdlError();
    return false;
  }
  return true;
}

bool aequus::InitImage() {
  int img_flags = IMG_INIT_PNG;
  if (IMG_Init(img_flags) == false || img_flags == 0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL Image",
                "aequus::InitImage");
    error::LogImgError();
    return false;
  }
  return true;
}

bool aequus::InitTtf() {
  if (TTF_Init() == -1) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL TTF",
                "aequus::InitTtf");
    error::LogTtfError();
    return false;
  }
  return true;
}

bool aequus::InitMix() {
  if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) ==
      0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL Mixer",
                "aequus::InitMix");
    error::LogMixError();
    return false;
  }
  return true;
}

void aequus::TermAequus() {
  TermMix();
  TermTtf();
  TermImage();
  TermSdl();
}

void aequus::TermSdl() { SDL_Quit(); }

void aequus::TermImage() { IMG_Quit(); }

void aequus::TermTtf() { TTF_Quit(); }

void aequus::TermMix() { Mix_Quit(); }

void aequus::SdlVersion(int& major, int& minor, int& patch) {
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  if (compiled.major == linked.major && compiled.minor == linked.minor &&
      compiled.patch == linked.patch) {
  } else {
    pessum::Log(pessum::ERROR, "SDL versions do not match",
                "aequus::SdlVersion");
    pessum::Log(pessum::INFO, "Compiled Version: %i.%i.%i", "SDL",
                compiled.major, compiled.minor, compiled.patch);
    pessum::Log(pessum::INFO, "Linked VersionL: %i.%i.%i", "SDL", linked.major,
                linked.minor, linked.patch);
  }
  major = linked.major;
  minor = linked.minor;
  patch = linked.patch;
}
