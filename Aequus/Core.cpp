#include <iostream>
#include <vector>
#include <ctime>
#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::video::window::CreateWindow("Core", 600, 600);
	for (int a = 0; a < 10000; a++) {
		aequus::video::window::UpdateAll();
	}
	aequus::video::window::TerminateWindow();
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}