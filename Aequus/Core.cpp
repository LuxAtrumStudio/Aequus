#include <iostream>
#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_core.h"
#include "pessum_files\logging.h"
using namespace std;

int main(int argc, char* argv[]) {
	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::video::CreateWindow("Core", 600, 600);
	aequus::video::SetIcon("resources/icon/sun.png");
	aequus::video::SetTitle("Aequus Framework Stress Test");
	bool music = false, sound = false;
	bool messagebox = false;
	bool drect = false, dpoint = false, dline = false, dfill = false;
	bool otext = false, otexture = false, obutton = false;
	double r, g, b, angle = 0;
	int textobj = 0, textureobj = 0;
	while (aequus::video::AllClose() == false) {
		r = rand() % 255 / (double)255;
		g = rand() % 255 / (double)255;
		b = rand() % 255 / (double)255;
		aequus::video::draw::SetColor(r, g, b, 1.0);
		for (unsigned a = 0; a < aequus::input::events.size(); a++) {
			if (aequus::input::events[a].type == aequus::input::EventType::KEYBOARD) {
				if (aequus::input::events[a].key == int('q') && music == false) {
					music = true;
					aequus::audio::music::LoadPlaylist("resources/music");
					aequus::audio::music::SetAutoPlay(true);
					aequus::audio::music::SetShuffle(true);
					aequus::audio::music::PlaySong(5000);
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked music", "Core");
				}
				if (aequus::input::events[a].key == int('w') && messagebox == false) {
					messagebox = true;
					//TODO[Arden]:Find and Fix bug
					aequus::video::MessageBox newbox;
					newbox.NewMessageBox(aequus::video::MessageBox::MessageBoxFlags::INFORMATION, aequus::video::win->sdlwindow, "Message Box", "This is a Message Box");
					newbox.RunMessageBox();
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked message box", "Core");
				}
				if (aequus::input::events[a].key == int('e') && drect == false) {
					drect = true;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked draw rectangle", "Core");
				}
				if (aequus::input::events[a].key == int('r') && dpoint == false) {
					dpoint = true;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked draw point", "Core");
				}
				if (aequus::input::events[a].key == int('t') && dline == false) {
					dline = true;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked draw line", "Core");
				}
				if (aequus::input::events[a].key == int('y') && dfill == false) {
					dfill = true;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked draw fill rectangle", "Core");
				}
				if (aequus::input::events[a].key == int('u') && sound == false) {
					//TODO[Arden]:Find and Fix bug
					sound = true;
					aequus::audio::ChannelVolume(1);
					aequus::audio::PlaySound("resouces/audio/sample1.wav");
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked sound", "Core");
				}
				if (aequus::input::events[a].key == int('i') && otext == false) {
					otext = true;
					aequus::video::NewObject();
					aequus::video::win->obj->CreateTextObj("Hello World!!!", 40, 1, 1, 1, 1.0);
					textobj = aequus::video::win->objects.size() - 1;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked text", "Core");
				}
				if (aequus::input::events[a].key == int('o') && otexture == false) {
					otexture = true;
					aequus::video::NewObject();
					aequus::video::win->obj->CreateImgObj("sun.png");
					textureobj = aequus::video::win->objects.size() - 1;
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked image", "Core");
				}
				if (aequus::input::events[a].key == int('p') && obutton == false) {
					//TODO[Arden]:Find and Fix bug
					obutton = true;
					aequus::video::NewObject();
					aequus::video::win->obj->CreateButton("Test Button!!!", "button4.png", false, true);
					pessum::logging::Log(pessum::logging::LOG_DEVELOPMENT_CHECK, "Checked button", "Core");
				}
			}
		}

		if (drect == true) {
			int rect[4] = { 10, 10, 100, 100 };
			aequus::video::draw::Rect(rect);
		}
		if (dpoint == true) {
			int point[2] = { 170, 60 };
			aequus::video::draw::Point(point);
		}
		if (dline == true) {
			int pointa[2] = { 220, 10 };
			int pointb[2] = { 320, 110 };
			aequus::video::draw::Line(pointa, pointb);
		}
		if (dfill == true) {
			int rect[4] = { 330, 10, 100, 100 };
			aequus::video::draw::FillRect(rect);
		}
		if (otext == true) {
			aequus::video::win->objects[textobj].SetColor(r, g, b, 1.0);
		}
		if (otexture == true) {
			aequus::video::win->objects[textureobj].Rotate(angle, true);
			angle+=0.01;
			if (angle == 360) {
				angle = 0;
			}
		}

		aequus::Frame();
	}
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}