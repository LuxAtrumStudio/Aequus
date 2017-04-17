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
  aequus::Window win;
  win.CreateWindow("Test", 100, 100);
  aequus::ObjectBase obj =
      aequus::Image("resources/proj-test.png", win.SdlRenderer());
  // aequus::Object obj(aequus::AEQ_OBJ_IMAGE, "resources/proj-test.png",
  //                    win.SdlRenderer());
  win.Display();
  win.DeleteWindow();
  aequus::TermAequus();
  return 0;
}
