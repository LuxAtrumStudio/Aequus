#include "../log_indices.hpp"
#include "../sdl_headers.hpp"
#include "framework.hpp"
#include <pessum.h>
#include <string>

bool aequus::framework::InitializeSdl() {
  bool goodinit = true;
  // Sets rand to seed off of the current start time
  srand(time(NULL));
  // Initializes SDL componenets
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to initialize SDL",
                            LOG_AEQ_FRA, "InitializeSdl");
    GetSdlError(SDL);
    goodinit = false;
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized SDL",
                            LOG_AEQ_FRA, "InitializeSdl");
  }
  // Initializes SDL IMG library
  int imgflags = IMG_INIT_PNG;
  if (!IMG_Init(imgflags) || imgflags == 0) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to initialize SDL IMG", LOG_AEQ_FRA,
                            "InitializeSdl");
    GetSdlError(IMG);
    goodinit = false;
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized SDL IMG",
                            LOG_AEQ_FRA, "InitializeSdl");
  }
  // Initializes SDL TTF library
  if (TTF_Init() == -1) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to initialize SDL TTG", LOG_AEQ_FRA,
                            "InitializeSdl");
    GetSdlError(TTF);
    goodinit = false;
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized SDL TTG",
                            LOG_AEQ_FRA, "InitializeSdl");
  }
  // Initializes SDL Mixer library
  if (Mix_Init(MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG) ==
      0) {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Failed to initialize SDL Mixer", LOG_AEQ_FRA,
                            "InitializeSdl");
    GetSdlError(MIX);
    goodinit = false;
  } else {
    pessum::logging::LogLoc(pessum::logging::SUCCESS, "Initialized SDL Mixer",
                            LOG_AEQ_FRA, "InitializeSdl");
  }
  // Checks if the compiled version of SDL matches the runtime version of SDL
  SDL_version compiled, linked;
  SDL_VERSION(&compiled);
  SDL_GetVersion(&linked);
  if (compiled.major == linked.major && compiled.minor == linked.minor &&
      compiled.patch == linked.patch) {
    pessum::logging::LogLoc(pessum::logging::SUCCESS,
                            "SDL versions are the same", LOG_AEQ_FRA,
                            "InitializeSdl");
    pessum::logging::LogLoc(pessum::logging::DATA,
                            "SDL versions: " + std::to_string(compiled.major) +
                                "." + std::to_string(compiled.minor) + "." +
                                std::to_string(compiled.patch),
                            LOG_AEQ_FRA, "InitializeSdl");
  } else {
    pessum::logging::LogLoc(pessum::logging::WARNING,
                            "SDL versions do not match", LOG_AEQ_FRA,
                            "InitializeSdl");
    pessum::logging::LogLoc(pessum::logging::DATA,
                            "Compiled version: " +
                                std::to_string(compiled.major) + "." +
                                std::to_string(compiled.minor) + "." +
                                std::to_string(compiled.patch),
                            LOG_AEQ_FRA, "InitializeSdl");
    pessum::logging::LogLoc(pessum::logging::DATA,
                            "Linked version: " + std::to_string(linked.major) +
                                "." + std::to_string(linked.minor) + "." +
                                std::to_string(linked.patch),
                            LOG_AEQ_FRA, "InitializeSdl");
  }
  return (goodinit);
}

void aequus::framework::TerminateSdl() {
  Mix_Quit();
  TTF_Quit();
  IMG_Quit();
  SDL_Quit();
  pessum::logging::LogLoc(pessum::logging::SUCCESS,
                          "Terminated all SDL systems", LOG_AEQ_FRA,
                          "TerminateSdl");
}

std::string aequus::framework::GetSdlError(Module mod) {
  std::string errorstring = "";
  const char *error = "";
  if (mod == SDL) {
    error = SDL_GetError();
  } else if (mod == IMG) {
    error = IMG_GetError();
  } else if (mod == TTF) {
    error = TTF_GetError();
  } else if (mod == MIX) {
    error = Mix_GetError();
  }
  if (*error) {
    errorstring = error;
  }
  pessum::logging::Log(pessum::logging::ERROR, errorstring, "SDL");
  return (errorstring);
}
