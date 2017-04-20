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
  aequus::Object obj(aequus::AEQ_OBJ_IMAGE, "resources/proj-test.png",
                     aequus::aequus_windows.Find("Aequus")->SdlRenderer());
  aequus::aequus_windows.Find("Aequus")->window_base_layout.AddObject(obj);
  obj.ptr->Scale(0.25);
  while (aequus::aequus_quit == false) {
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
