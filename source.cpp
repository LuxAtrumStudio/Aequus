#include <pessum.h>
#include <iostream>
#include "aequus_files/aequus_headers.hpp"

void Handle(std::pair<int, std::string> entry) {
  if (entry.first == pessum::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == pessum::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == pessum::TRACE) {
    system("setterm -fore cyan");
  }
  std::cout << entry.second << "\n";
  system("setterm -fore white");
}

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(Handle);
  aequus::InitAequus();
  aequus::aequus_windows.Push(aequus::Window("Aequus", 500, 500));
  aequus::Object obj(aequus::AEQ_OBJ_IMAGE, "resources/test.png",
                     aequus::aequus_windows.Find("Aequus")->SdlRenderer());
  aequus::Object obj_2(aequus::AEQ_OBJ_IMAGE, "resources/test.png",
                       aequus::aequus_windows.Find("Aequus")->SdlRenderer());
  aequus::aequus_windows.Find("Aequus")->window_base_layout.AddObject(obj);
  aequus::aequus_windows.Find("Aequus")->window_base_layout.AddObject(obj_2);
  aequus::aequus_windows.Find("Aequus")->window_base_layout.SetFormat(
      aequus::AEQ_OBJ_LAY_VERTICAL_FORCE);
  while (aequus::aequus_quit == false) {
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
