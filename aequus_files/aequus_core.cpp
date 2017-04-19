#include <pessum.h>
#include "aequus_core.hpp"
#include "input/input.hpp"
#include "sdl_headers.hpp"
#include "window/window_container.hpp"

namespace aequus {
  WindowContainer aequus_windows;
  bool aequus_quit = false;
}

void aequus::InitAequus() {
  InitSdl();
  int major = 0, minor = 0, patch = 0;
  GetVersion(major, minor, patch);
  pessum::Log(pessum::INFO, "Aequus version: %i.%i.%i", "aequus/InitAequus",
              major, minor, patch);
}

void aequus::TermAequus() {
  srand(time(NULL));
  TermSdl();
  pessum::SaveLog("out.log");
}

void aequus::Frame() {
  PollEvents();
  aequus_windows.Display();
  if (GetEvent(SDL_QUIT).type == 256) {
    aequus_quit = true;
    aequus_windows.Clear();
  } else if (aequus_windows.Size() == 0) {
    aequus_quit = true;
  }
}

bool aequus::InitSdl() {
  bool good_init = true;
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL", "aequus/InitSdl");
    SdlError(SDL);
    good_init = false;
  }
  int img_flags = IMG_INIT_PNG;
  if (!IMG_Init(img_flags) || img_flags == 0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL-IMG",
                "aequus/InitSdl");
    SdlError(IMG);
    good_init = false;
  }
  if (TTF_Init() == -1) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL-TTF",
                "aequus/InitSdl");
    SdlError(TTF);
    good_init = false;
  }
  if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) ==
      0) {
    pessum::Log(pessum::ERROR, "Failed to initialize SDL-Mixer",
                "aequus/InitSdl");
    SdlError(MIX);
    good_init = false;
  }
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  if (compiled.major == linked.major && compiled.minor == linked.minor &&
      compiled.patch == linked.patch) {
    pessum::Log(pessum::INFO, "SDL versions: %i.%i.%i", "aequus/InitSdl",
                compiled.major, compiled.minor, compiled.patch);
  } else {
    pessum::Log(pessum::ERROR, "SDL versions do not match", "aequus/InitSdl");
    pessum::Log(pessum::INFO, "Compiled version: %i.%i.%i", "aequus/InitSdl",
                compiled.major, compiled.minor, compiled.patch);
    pessum::Log(pessum::INFO, "Linked version: %i.%i.%i", "aequus/InitSdl",
                linked.major, linked.minor, linked.patch);
    good_init = false;
  }
  return (good_init);
}

void aequus::TermSdl() {
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
}

void aequus::GetVersion(int& major, int& minor, int& patch) {
  major = AEQUUS_MAJOR;
  minor = AEQUUS_MINOR;
  patch = AEQUUS_PATCH;
}

void aequus::SdlError(int type) {
  std::string err_str = "";
  if (type == SDL) {
    err_str = SDL_GetError();
  } else if (type == IMG) {
    err_str = IMG_GetError();
  } else if (type == TTF) {
    err_str = TTF_GetError();
  } else if (type == MIX) {
    err_str = Mix_GetError();
  }
  if (err_str != "") {
    pessum::Log(pessum::ERROR, err_str, "SDL");
  }
}
