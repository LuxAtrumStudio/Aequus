#include <iostream>
#include <vector>
#include <ctime>
#include "aequus_files\aequus_headers.h"
#include "pessum_files\pessum_core.h"
using namespace std;

int main(int argc, char* argv[]) {

	int windowsize = 1000;
	int half = windowsize / 2;

	pessum::InitializePessumComponents();
	aequus::framework::SdlStartUp();
	aequus::video::CreateWindow("Core", 1000, 1000);
	aequus::audio::music::InitalizeMusic();
	aequus::audio::music::LoadPlaylist("resources/music");
	aequus::audio::music::SetAutoPlay(true);
	aequus::audio::music::SetShuffle(true);
	aequus::audio::music::PlaySong(100, -1, 120.0);
	std::vector<vector<int>> points;
	std::vector<int*> ppoints;
	for (int a = 0; a < 1000; a++) {
		std::vector<int> point;
		point.push_back(half);
		point.push_back(half);
		points.push_back(point);
	}
	aequus::video::draw::InitializeDraw(aequus::video::win->windowrenderer.sdlrenderer);
	aequus::video::draw::SetColor(1, 1, 1, 1);
	while (aequus::video::AllClose() == false) {
		ppoints.clear();
		for (int a = 0; a < points.size(); a++) {
			int* ppoint = &points[a][0];
			ppoints.push_back(ppoint);
		}
		aequus::video::draw::Lines(ppoints);
		for (int a = 0; a < points.size(); a+=2) {
			int randval = (rand() % half) + half / 2;
			if (randval < (points[a][0] - half) || -randval > (points[a][0] - half)) {
				points[a][0] = half;
				points[a][1] = half;
			}
			else {
				if (rand() % 100 < 25) {
					points[a][0]-=5;
				}
				if (rand() % 100 > 75) {
					points[a][0]+=5;
				}
			}
			int randvaly = (rand() % half) + half / 2;
			if (randvaly < (points[a][1] - half) || -randvaly >(points[a][1] - half)) {
				points[a][0] = half;
				points[a][1] = half;
			}
			else {
				if (rand() % 100 < 25) {
					points[a][1]-=5;
				}
				if (rand() % 100 > 75) {
					points[a][1]+=5;
				}
			}
		}
		if (rand() % 2 == 0) {
			aequus::video::draw::drawcolor[0] -= 0.01;
		}
		else {
			aequus::video::draw::drawcolor[0] += 0.01;
		}
		if (rand() % 2 == 0) {
			aequus::video::draw::drawcolor[1] -= 0.01;
		}
		else {
			aequus::video::draw::drawcolor[1] += 0.01;
		}
		if (rand() % 2 == 0) {
			aequus::video::draw::drawcolor[2] -= 0.01;
		}
		else {
			aequus::video::draw::drawcolor[2] += 0.01;
		}
		aequus::audio::music::Update();
		aequus::input::PollEvents();
		aequus::video::HandleEventsAll();
		aequus::video::UpdateAll();
	}
	aequus::framework::TerminateSdl();
	pessum::TerminatePessumComponents();
	return(1);
}