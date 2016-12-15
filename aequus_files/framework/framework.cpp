#include <ctime>
#include <string>
#include "../../pessum_files/logging.h"
#include "../aequus_headers.h"
#include "../sdl_headers.h"
#include "framework.h"

namespace aequus {
namespace framework {
int logloc = 0;
clock_t timmerstart = 0;
}
}

void aequus::framework::SdlStartUp() {
  srand(time(NULL));
  InitializeSdl(EVERYTHING);
  InitalizeImg();
  InitializeTtf();
  InitializeMixer();
  CheckSdlVersions();
}

void aequus::framework::InitializeSdl(Uint32 flags) {
  logloc = pessum::logging::AddLogLocation("aequus_files/framework/");
  if (SDL_Init(flags) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to initialize SDL", logloc,
                            "InitializeSdl");
    SdlError();
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Initialized SDL",
                            logloc, "InitializeSdl");
  }
}

void aequus::framework::TerminateSdl() {
  audio::music::TerminateMusic();
  SDL_Quit();
  IMG_Quit();
  TTF_Quit();
  Mix_Quit();
  pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS,
                          "Terminated all SDL systems", logloc, "TermianteSdl");
}

void aequus::framework::SetMain() { SDL_SetMainReady(); }

std::string aequus::framework::SdlError() {
  std::string errorstring = "";
  const char *error = SDL_GetError();
  if (*error) {
    errorstring = error;
    SDL_ClearError();
  }
  pessum::logging::Log(pessum::logging::LOG_ERROR, "SDL Error: " + errorstring,
                       "AEQUUS SDL ERROR");
  return (errorstring);
}

std::string aequus::framework::GetError(int errortype) {
  std::string errorstring = "";
  if (errortype == 1) {
    const char *error = SDL_GetError();
    if (*error) {
      errorstring = error;
      SDL_ClearError();
    }
  } else if (errortype == 2) {
    const char *error = IMG_GetError();
    if (*error) {
      errorstring = error;
    }
  } else if (errortype == 3) {
    const char *error = TTF_GetError();
    if (*error) {
      errorstring = error;
    }
  } else if (errortype == 4) {
    const char *error = Mix_GetError();
    if (*error) {
      errorstring = error;
    }
  }
  pessum::logging::Log(pessum::logging::LOG_ERROR, "SDL Error: " + errorstring,
                       "AEQUUS SDL ERROR");
  return (errorstring);
}

void aequus::framework::CheckSdlVersions() {
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  if (compiled.major == linked.major && compiled.minor == linked.minor &&
      compiled.patch == linked.patch) {
    pessum::logging::LogLoc(pessum::logging::LOG_DATA,
                            "SDL versions match: " +
                                std::to_string(compiled.major) + "." +
                                std::to_string(compiled.minor) + "." +
                                std::to_string(compiled.patch),
                            logloc, "CheckSdlVersions");
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_WARNING,
                            "SDL versions do not match", logloc,
                            "CheckSdlversons");
    pessum::logging::LogLoc(pessum::logging::LOG_DATA,
                            "Compiled version: " +
                                std::to_string(compiled.major) + "." +
                                std::to_string(compiled.minor) + "." +
                                std::to_string(compiled.patch),
                            logloc, "CheckSdlVersions");
    pessum::logging::LogLoc(pessum::logging::LOG_DATA,
                            "Linked version: " + std::to_string(linked.major) +
                                "." + std::to_string(linked.minor) + "." +
                                std::to_string(linked.patch),
                            logloc, "CheckSdlVersions");
  }
}

void aequus::framework::InitalizeImg() {
  int imgFlags = IMG_INIT_PNG;
  if (IMG_Init(imgFlags) && imgFlags != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to initialize SDL IMG", logloc,
                            "InitalizeImg");
    GetError(2);
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Initialized SDL IMG",
                            logloc, "InitalizeImg");
  }
}

void aequus::framework::InitializeTtf() {
  if (TTF_Init() == -1) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to initialize SDL TTG", logloc,
                            "InitializeTtf");
    GetError(3);
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Initialized SDL TTG",
                            logloc, "InitializeTtf");
  }
}

void aequus::framework::InitializeMixer() {
  if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) ==
      0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to initialize SDL Mixer", logloc,
                            "InitializeMixer");
    GetError(4);
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS,
                            "Initialized SDL Mixer", logloc, "InitializeMixer");
    aequus::audio::InitializeAudio();
  }
}

double aequus::framework::Timmer(bool start) {
  double elapsed = 0;
  if (start == true) {
    timmerstart = clock();
  } else if (start == false) {
    clock_t end = clock();
    elapsed = (end - timmerstart) / (double)CLOCKS_PER_SEC;
  }
  return (elapsed);
}
