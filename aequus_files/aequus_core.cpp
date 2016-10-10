#include "aequus_core.h"
#include "../pessum_files/pessum_headers.h"
#include "aequus_headers.h"
#include <ctime>
namespace aequus {
int FPS = -1;
time_t FPStimecheck;
}

void aequus::Frame() {
  aequus::audio::music::Update();
  aequus::input::PollEvents();
  aequus::video::HandleEventsAll();
  aequus::video::UpdateAll();
  time_t current;
  time(&current);
  if (current > FPStimecheck + 10) {
    FPStimecheck = current;
    double FPScalc = FPS / 10;
    if (FPScalc <= 30 && FPS != -1) {
      pessum::logging::Log(pessum::logging::LOG_WARNING,
                           "FPS < 30: " + std::to_string(FPScalc),
                           "aequus_files/aequus_core.cpp/Frame");
      pessum::logging::LogTimeStamp();
    }
    FPS = 0;
  }
  FPS++;
}
