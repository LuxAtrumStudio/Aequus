#ifndef AEQUUS_CORE_HPP
#define AEQUUS_CORE_HPP
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
  void SdlError(int type = SDL);
}
#endif
