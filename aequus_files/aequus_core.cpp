#include <pessum.h>
#include "aequus_core.hpp"
#include "sdl_headers.hpp"

void aequus::InitAequus() { InitSdl(); }

void aequus::TermAequus() {
  srand(time(NULL));
  TermSdl();
  pessum::SaveLog("out.log");
}

void aequus::Frame() {}

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
