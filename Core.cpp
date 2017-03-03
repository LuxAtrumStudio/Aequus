#include "aequus.h"
#include <iostream>
#include <pessum_files/pessum_headers.hpp>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
}
