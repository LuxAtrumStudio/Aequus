#include "aequus_core.hpp"
#include "framework/framework.hpp"
#include "log_indices.hpp"
#include <map>
#include <pessum.h>

void aequus::InitializeAequus() {
  pessum::InitializePessumComponents(DEV_MODE);
  pessum::logging::AddLogLocation("aequus/");
  pessum::logging::AddLogLocation("aequus/framework/");

  framework::InitializeSdl();
}

void aequus::TerminateAequus() {
  framework::TerminateSdl();
  pessum::TerminatePessumComponents();
}
