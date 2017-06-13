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
  aequus::aequus_windows.Push(win);
  while (aequus::aequus_quit == false) {
    aequus::Frame();
  }
  aequus::TermAequus();
  return 0;
}
