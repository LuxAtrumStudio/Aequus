#include <iostream>

#include <pessum/pessum.hpp>

#include "aequus.hpp"

void PessumLogHandle(std::pair<int, std::string> entry) {
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
  } else if (entry.first == pessum::INFO) {
    system("setterm -fore white");
  }
  std::cout << entry.second << "\n";
  system("setterm -default");
}

int main(int argc, char* argv[]) {
  pessum::SetLogHandle(PessumLogHandle);
  aequus::InitAequus();
  aequus::window::Window win;
  win.SetRect({0, 0, 500, 500});
  win.SetFlags(aequus::window::RESIZABLE);
  win.CreateWin();
  std::string titles[] = {"A E Q U U S", " "};
  // std::string titles[] = {"A",
  // "Ae",
  // "Aeq",
  // "Aequ",
  // "Aequu",
  // "Aequus",
  // "Aequus",
  // "A equu s",
  // "A  e qu u  s",
  // "A  e  q u  u  s",
  // "A  e  q  u  u  s",
  // "A  e  q  u     s",
  // "A  e     u     s",
  // "   e     u     s",
  // "   e           s",
  // "               s",
  // ""};
  int i = 0;
  while (win.ShouldClose() == false) {
    win.SetTitle(titles[i]);
    i++;
    if (i >= 2) {
      i = 0;
    }
    win.Show();
    aequus::input::PollEvents();
    aequus::input::HandleEvent(win);
    SDL_Delay(100);
  }
  win.DeleteWin();
  aequus::TermAequus();
  pessum::SaveLog("out.log");
  return 0;
}
