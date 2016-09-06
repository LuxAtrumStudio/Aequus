#include <iostream>
#include <vector>
#include <ctime>
#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::video::window::CreateWindow("Core", 1280, 1024);
	aequus::video::window::NewTexture("Test.png");
	aequus::video::window::Update();
	for (int a = 0; a < 50000; a++) {
		aequus::video::window::Update();
	}
	aequus::video::window::TerminateWindow();
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}