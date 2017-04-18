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
  //obj.ptr->Scale(0.5);
  //obj.ptr->Scale(int(500), true);
  aequus::aequus_windows.Find("Aequus")->window_base_layout.AddObject(obj);
  double sc = 0.0;
  double angle = 0;
  bool grow = true;
  obj.ptr->Scale(0.25);
  obj.ptr->Rotate(30);
  while (aequus::aequus_quit == false) {
    //obj.ptr->Rotate(angle);
    angle += 0.1;
    if(angle >= 365){
      angle = 0;
    }
    //obj.ptr->Scale(sc);
    if(grow == true){
      sc += 0.01;
      if(sc >= 1){
        grow = false;
      }
    }else if(grow == false){
      sc -= 0.01;
      if(sc <= 0.0){
        grow = true;
      }
    }
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
