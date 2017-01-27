#include "aequus_core.hpp"
#include "aequus_headers.hpp"
#include "log_indices.hpp"
#include <pessum.h>

namespace aequus {
bool QuitState = false;
}

void aequus::InitializeAequus() {
  pessum::InitializePessumComponents(DEV_MODE);
  pessum::logging::AddLogLocation("aequus/");
  pessum::logging::AddLogLocation("aequus/framework/");
  pessum::logging::AddLogLocation("aequus/input/");
  pessum::logging::AddLogLocation("aequus/video/");
  pessum::logging::AddLogLocation("aequus/video/window/");
  pessum::logging::AddLogLocation("aequus/video/renderer/");
  pessum::logging::AddLogLocation("aequus/video/object/");
  pessum::logging::AddLogLocation("aequus/video/object/texture/");
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
