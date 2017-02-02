#include "aequus_core.hpp"
#include "aequus_headers.hpp"
#include "log_indices.hpp"
#include <pessum.h>

namespace aequus {
bool QuitState = false;
}

void aequus::InitializeAequus() {
  pessum::InitializePessumComponents(DEV_MODE);
  std::vector<std::string> locations = {"aequus/",
                                        "aequus/audio/",
                                        "aequus/framework/",
                                        "aequus/input/",
                                        "aequus/video/",
                                        "aequus/video/layout/",
                                        "aequus/video/object/",
                                        "aequus/video/object/button/",
                                        "aequus/video/object/image/",
                                        "aequus/video/object/text/",
                                        "aequus/video/object/font/",
                                        "aequus/video/renderer/",
                                        "aequus/video/window/"};
  for (int i = 0; i < locations.size(); i++) {
    pessum::logging::AddLogLocation(locations[i]);
  }
  QuitState = false;
  framework::InitializeSdl();
}

void aequus::TerminateAequus() {
  framework::TerminateSdl();
  pessum::TerminatePessumComponents();
}

void aequus::Frame() {
  input::PollEvents();
  if (QuitState == true) {
    video::DeleteWindows();
  }
  video::HandleEvents();
  video::UpdateAll();
}
