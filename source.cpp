#include <pessum.h>
#include "aequus_files/aequus_headers.hpp"

int main(int argc, char const* argv[]) {
  aequus::InitAequus();
  aequus::Window win;
  win.CreateWindow("Test", 100, 100);
  for (int i = 0; i < 1000000; i++) {
    win.Display();
  }
  win.DeleteWindow();
  aequus::TermAequus();
  return 0;
}
