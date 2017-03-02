#include "aequus_core.hpp"
#include "aequus_headers.hpp"
#include "log_indices.hpp"
#include <duco.h>
#include <map>
#include <pessum.h>

#include <iostream>
namespace aequus {
bool QuitState = false;
std::map<std::string, int> logmap;
}

void aequus::InitializeAequus() {
<<<<<<< HEAD
  pessum::InitializePessum(DEV_MODE);
=======
  pessum::InitializePessum(DEV_MODE, true);
>>>>>>> c58e86abbe86a423729a57e650a7c3afbf4fb516
  duco::LoadOperMap();
  std::vector<std::string> locations = {"aequus",
                                        "aequus/audio",
                                        "aequus/audio/chunk",
                                        "aequus/audio/music",
                                        "aequus/audio/music/song",
                                        "aequus/framework",
                                        "aequus/input",
                                        "aequus/video",
                                        "aequus/video/layout",
                                        "aequus/video/object",
                                        "aequus/video/object/button",
                                        "aequus/video/object/canvas",
                                        "aequus/video/object/graph",
                                        "aequus/video/object/plot",
                                        "aequus/video/object/image",
                                        "aequus/video/object/spacer",
                                        "aequus/video/object/text",
                                        "aequus/video/object/font",
                                        "aequus/video/renderer",
                                        "aequus/video/window"};
  for (int i = 0; i < locations.size(); i++) {
    pessum::logging::AddLogLocation(locations[i]);
  }
  QuitState = false;
  framework::InitializeSdl();
  audio::InitDevice(16);
}

void aequus::TerminateAequus() {
  audio::DeleteDevice();
  framework::TerminateSdl();
  pessum::TerminatePessum();
}

void aequus::Frame() {
  input::PollEvents();
  if (QuitState == true) {
    video::DeleteWindows();
  }
  video::HandleEvents();
  video::UpdateAll();
}
