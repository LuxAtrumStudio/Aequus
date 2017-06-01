#ifndef AEQUUS_CORE_HPP
#define AEQUUS_CORE_HPP
#define AEQUUS_MAJOR 0
#define AEQUUS_MINOR 0
#define AEQUUS_PATCH 17
#include "window/window_container.hpp"
namespace aequus {
  enum TYPE { SDL, IMG, TTF, MIX };
  extern WindowContainer aequus_windows;
  extern bool aequus_quit;
  void InitAequus();
  void TermAequus();
  void Frame();
  bool InitSdl();
  void TermSdl();
  void GetVersion(int& major, int& minor, int& patch);
  void SdlError(int type = SDL);
}
#endif
