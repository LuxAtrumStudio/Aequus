#include <pessum.h>
#include <iostream>
#include "aequus_files/aequus_headers.hpp"

using namespace aequus;


void pessumloghandle(std::pair<int, std::string> entry) {
  if (entry.first == pessum::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == pessum::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == pessum::TRACE) {
    system("setterm -fore blue");
  } else if (entry.first == pessum::DEBUG) {
    system("setterm -fore magenta");
  } else if (entry.first == pessum::SUCCESS) {
    system("setterm -fore green");
  } else if (entry.first == pessum::DATA) {
    system("setterm -fore cyan");
  } else if (entry.first == pessum::INFO){
    system("setterm -fore white");
  }
  std::cout << entry.second << "\n";
  system("setterm -default");
}

int main(int argc, char const* argv[]) {
  pessum::SetLogHandle(pessumloghandle);
  aequus::InitAequus();
  std::shared_ptr<aequus::Window> win =
      std::make_shared<aequus::Window>(aequus::Window("Aequus", 500, 500));
  Layout lay1(AEQ_OBJ_LAY_HORIZONTAL_FORCE, 500, 500);
  Layout lay2(AEQ_OBJ_LAY_HORIZONTAL_FORCE, 500, 500);
  Layout lay3(AEQ_OBJ_LAY_HORIZONTAL_FORCE, 500, 500);
  Object obj1 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj2 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj3 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj4 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj5 = make_object(Image("resources/test.png", win->SdlRenderer()));
  Object obj6 = make_object(Image("resources/test.png", win->SdlRenderer()));
  lay1.AddObject(obj1);
  lay1.AddObject(obj2);
  lay2.AddObject(obj3);
  lay2.AddObject(obj4);
  lay3.AddObject(obj5);
  lay3.AddObject(obj6);
  win->AddObject(make_object(lay1));
  win->AddObject(make_object(lay2));
  win->AddObject(make_object(lay3));
  win->window_base_layout->SetFormat(aequus::AEQ_OBJ_LAY_VERTICAL_FORCE);
  aequus::aequus_windows.Push(win);
  while (aequus::aequus_quit == false) {
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
