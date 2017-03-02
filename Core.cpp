#include "aequus.h"
#include <iostream>
#include <pessum_files/pessum_headers.hpp>

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::TerminateWindow(0);
  aequus::TerminateAequus(); 
}
