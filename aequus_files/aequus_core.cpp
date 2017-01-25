#include "aequus_core.hpp"
#include "framework/framework.hpp"
#include "log_indices.hpp"
#include <pessum.h>

void aequus::InitializeAequus() {
  pessum::InitializePessumComponents(DEV_MODE);
  pessum::logging::AddLogLocation("aequus/");
  pessum::logging::AddLogLocation("aequus/framework/");
  pessum::logging::AddLogLocation("aequus/video/");
  pessum::logging::AddLogLocation("aequus/video/window/");
  pessum::logging::AddLogLocation("aequus/video/renderer/");

  framework::InitializeSdl();
}

void aequus::TerminateAequus() {
  framework::TerminateSdl();
  pessum::TerminatePessumComponents();
}

void aequus::Frame() {}
