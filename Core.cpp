#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::audio::InitDevice(16);
  aequus::audio::PlayChunk("resources/test.wav", 1);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::audio::DeleteDevice();
  aequus::TerminateAequus();
  return (1);
}
