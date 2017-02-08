#include "aequus_core.hpp"
#include "aequus_headers.hpp"
#include "log_indices.hpp"
#include <map>
#include <pessum.h>

#include <iostream>
namespace aequus {
bool QuitState = false;
std::map<std::string, int> logmap;
}

void aequus::InitializeAequus() {
  pessum::InitializePessumComponents(DEV_MODE);
  std::vector<std::string> locations = {
      "aequus/", "aequus/audio/", "aequus/audio/chunk/", "aequus/audio/music/",
      "aequus/audio/music/song/"
      "aequus/framework/",
      "aequus/input/", "aequus/video/", "aequus/video/layout/",
      "aequus/video/object/", "aequus/video/object/button/",
      "aequus/video/object/image/", "aequus/video/object/spacer/",
      "aequus/video/object/text/", "aequus/video/object/font/",
      "aequus/video/renderer/", "aequus/video/window/"};
  for (int i = 0; i < locations.size(); i++) {
    std::string key = "";
    int add = 3;
    for (int j = 0; j < locations[i].size(); j++) {
      if (add > 0) {
        key += char(int(locations[i][j]) - 32);
        add--;
      }
      if (locations[i][j] == '/' && j != locations[i].size() - 1) {
        key += '_';
        add = 3;
      }
    }
    logmap[key] = pessum::logging::AddLogLocation(locations[i]);
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
