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
  win.CreateWin();
  while (win.ShouldClose() == false) {
    win.Show();
    aequus::input::PollEvents();
    aequus::input::HandleEvent(win);
  }
  win.DeleteWin();
  aequus::TermAequus();
  pessum::SaveLog("out.log");
  return 0;
}