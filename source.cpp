#include <pessum.h>
#include <iostream>
#include "aequus_files/aequus_headers.hpp"

int main(int argc, char const* argv[]) {
  aequus::InitAequus();
  aequus::Window win;
  win.CreateWindow("Test", 100, 100);
  aequus::Image("resources/proj-test.png", win.SdlRenderer());
  win.Display();
  win.DeleteWindow();
  aequus::TermAequus();
  return 0;
}
