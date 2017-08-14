#ifndef AEQUUS_CORE_HPP
#define AEQUUS_CORE_HPP

#define AEQUUS_VERSION_MAJOR 0
#define AEQUUS_VERSION_MINOR 0
#define AEQUUS_VERSION_PATCH 10

namespace aequus {
  extern bool aequus_quit_;
  bool InitAequus();
  bool InitSdl();
  bool InitImage();
  bool InitTtf();
  bool InitMix();
  void TermAequus();
  void TermSdl();
  void TermImage();
  void TermTtf();
  void TermMix();
  void SdlVersion(int& major, int& minor, int& patch);
  void GetVersion(int& major, int& minor, int& patch);
}  // namespace aequus

#endif /* ifndef AEQUUS_CORE_HPP */
