#include "aequus.h"
#include <iostream>
#include <pessum.h>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus");
  while (aequus::video::AllClose() == true) {
    aequus::video::UpdateAll();
  }
  aequus::TerminateAequus();
  return (1);
}
