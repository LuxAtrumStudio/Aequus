#include <iostream>
#include <vector>
#include <ctime>
#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::video::CreateWindow("Core", 600, 600);
	aequus::video::NewObject();
	aequus::video::win->obj->CreateButton("Hello World!", "button1.png", true);
	while (aequus::video::AllClose() == false) {
		aequus::input::PollEvents();
		aequus::video::HandleEventsAll();
		for (int a = 0; a < aequus::video::output.size(); a++) {
			if (aequus::video::output[a].windowID == 0 && aequus::video::output[a].objectID == 0 && aequus::video::output[a].value == 1) {
				aequus::input::Event quitevent;
				quitevent.type = aequus::input::EventType::QUIT;
				aequus::input::events.clear();
				aequus::input::events.push_back(quitevent);
				aequus::video::HandleEventsAll();
			}
		}
		aequus::video::UpdateAll();
	}
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}