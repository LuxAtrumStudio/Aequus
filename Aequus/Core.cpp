#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_headers.h"
#include <iostream>
using namespace std;

int WinMain(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Core", 600, 600);
  std::vector<std::string> files =
      pessum::luxreader::LoadLuxListFile("resources/music/songs.lux");
  std::vector<std::string> display;
  for (unsigned a = 0; a < files.size(); a++) {
    std::string newsong = "";
    for (unsigned b = 0; b < files[a].size(); b++) {
      if (files[a][b] == '.') {
        display.push_back(newsong);
        break;
      }
      if (files[a][b] == '_') {
        newsong = newsong + ' ';
      } else {
        newsong = newsong + files[a][b];
      }
    }
    files[a] = "resources/music/" + files[a];
  }
  int posx = 10, posy = 10;
  for (unsigned a = 0; a < display.size(); a++) {
    aequus::video::NewObject();
    aequus::video::win->obj->CreateButton(display[a], "button.png", false, true,
                                          285, 50);
    aequus::video::win->obj->SetColor(0.0, 0.8, 0.8, 1.0);
    aequus::video::win->obj->SetPos(posx, posy);
    posy = posy + 59;
    if (posy >= 600) {
      posy = 10;
      posx = posx + 300;
    }
  }
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
    for (unsigned a = 0; a < aequus::video::output.size(); a++) {
      if (aequus::video::output[a].windowID = 1) {
        aequus::audio::music::LoadSong(
            files[aequus::video::output[a].objectID]);
        aequus::audio::music::PlaySong();
        aequus::video::win->objects[aequus::video::output[a].objectID].SetColor(
            0.5, 1.0, 0.5, 1.0);
      }
    }
  }
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
