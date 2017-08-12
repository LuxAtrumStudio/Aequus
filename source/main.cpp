#include <iostream>

#include "aequus.hpp"

void PessumLogHandle(std::pair<int, std::string> entry) {
  if (entry.first == aequus::log::ERROR) {
    system("setterm -fore red");
  } else if (entry.first == aequus::log::WARNING) {
    system("setterm -fore yellow");
  } else if (entry.first == aequus::log::TRACE) {
    system("setterm -fore blue");
  } else if (entry.first == aequus::log::DEBUG) {
    system("setterm -fore magenta");
  } else if (entry.first == aequus::log::SUCCESS) {
    system("setterm -fore green");
  } else if (entry.first == aequus::log::DATA) {
    system("setterm -fore cyan");
  } else if (entry.first == aequus::log::INFO) {
    system("setterm -fore white");
  }
  std::cout << entry.second << "\n";
  system("setterm -default");
}

void SetHandle(std::string entry) { std::cout << entry << "\n"; }

int main(int argc, char* argv[]) {
  aequus::log::SetLogHandle(PessumLogHandle);
  aequus::log::SetLogHandle(SetHandle);
  aequus::InitAequus();
  aequus::Color color;
  color = {0.5, 0.5, 1.0};
  aequus::window::Window win;
  win.SetRect({0, 0, 500, 500});
  win.SetFlags(aequus::window::RESIZABLE);
  win.CreateWin();
  win.SetClearColor(color);
  while (win.ShouldClose() == false) {
    win.Show();
    aequus::input::PollEvents();
    aequus::input::HandleEvent(win);
  }
  win.DeleteWin();
  aequus::TermAequus();
  aequus::log::SaveLog("out.log");
  return 0;
}
