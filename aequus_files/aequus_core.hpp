#ifndef AEQUUS_CORE_HPP
#define AEQUUS_CORE_HPP
#define DEV_MODE true
namespace aequus {
  enum TYPE { SDL, IMG, TTF, MIX };
  void InitAequus();
  void TermAequus();
  void Frame();
  bool InitSdl();
  void TermSdl();
  void SdlError(int type = SDL);
}
#endif
