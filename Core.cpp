#include "aequus_files/aequus_headers.h"
#include "pessum_files/pessum_headers.h"
#include <iostream>
using namespace std;

int main(int argc, char *argv[]) {
  pessum::InitializePessumComponents();
  aequus::framework::SdlStartUp();
  aequus::video::CreateWindow("Aequus");
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::framework::TerminateSdl();
  pessum::TerminatePessumComponents();
  return (1);
}
