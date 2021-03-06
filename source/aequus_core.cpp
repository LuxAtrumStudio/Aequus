#include "aequus_core.hpp"

#include "error/error.hpp"
#include "log/log.hpp"
#include "sdl_headers.hpp"

namespace aequus {
  bool aequus_quit_ = false;
}  // namespace aequus

bool aequus::InitAequus() {
  log::Log(log::INFO, "Aequus Version: %i.%i.%i", "aequus::InitAequus",
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
  log::Log(log::INFO, "SDL Version: %i.%i.%i", "aequus::InitAequus", major,
           minor, patch);
  return true;
}

bool aequus::InitSdl() {
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    log::Log(log::ERROR, "Failed to initialize SDL", "aequus::InitSdl");
    error::LogSdlError();
    return false;
  }
  return true;
}

bool aequus::InitImage() {
  int img_flags = IMG_INIT_PNG;
  if (IMG_Init(img_flags) == false || img_flags == 0) {
    log::Log(log::ERROR, "Failed to initialize SDL Image", "aequus::InitImage");
    error::LogImgError();
    return false;
  }
  return true;
}

bool aequus::InitTtf() {
  if (TTF_Init() == -1) {
    log::Log(log::ERROR, "Failed to initialize SDL TTF", "aequus::InitTtf");
    error::LogTtfError();
    return false;
  }
  return true;
}

bool aequus::InitMix() {
  if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) ==
      0) {
    log::Log(log::ERROR, "Failed to initialize SDL Mixer", "aequus::InitMix");
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
    log::Log(log::ERROR, "SDL versions do not match", "aequus::SdlVersion");
    log::Log(log::INFO, "Compiled Version: %i.%i.%i", "SDL", compiled.major,
             compiled.minor, compiled.patch);
    log::Log(log::INFO, "Linked VersionL: %i.%i.%i", "SDL", linked.major,
             linked.minor, linked.patch);
  }
  major = linked.major;
  minor = linked.minor;
  patch = linked.patch;
}

void aequus::GetVersion(int& major, int& minor, int& patch) {
  major = AEQUUS_VERSION_MAJOR;
  minor = AEQUUS_VERSION_MINOR;
  patch = AEQUUS_VERSION_PATCH;
}
