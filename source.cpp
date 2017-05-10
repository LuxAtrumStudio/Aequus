#include <pessum.h>
#include <iostream>
#include "aequus_files/aequus_headers.hpp"

using namespace aequus;

void Handle(std::pair<int, std::string> entry) {
  if (entry.first == pessum::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == pessum::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == pessum::TRACE) {
    system("setterm -fore cyan");
  }
  std::cout << entry.second << "\n";
  system("printf \"\e[0m\"");
}

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(Handle);
  aequus::InitAequus();
  std::shared_ptr<aequus::Window> win =
      std::make_shared<aequus::Window>(aequus::Window("Aequus", 500, 500));
  aequus::Object obj1 = aequus::make_object(
      aequus::Image("resources/test.png", win->SdlRenderer()));
  Object obj2 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Layout SubLayout(AEQ_OBJ_LAY_HORIZONTAL_FORCE, 100, 100);
  Object obj3 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj4 = make_object(Image("resources/test.png", win->SdlRenderer()));
  win->AddObject(obj1);
  win->AddObject(obj2);
  //SubLayout.AddObject(obj3);
  //SubLayout.AddObject(obj4);
  //win->AddObject(make_object(SubLayout));
  win->window_base_layout->SetFormat(aequus::AEQ_OBJ_LAY_VERTICAL_FORCE);
  aequus::aequus_windows.Push(win);
  while (aequus::aequus_quit == false) {
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
