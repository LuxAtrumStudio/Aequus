#include "aequus.h"
#include <iostream>
#include <pessum.h>

void release() { aequus::video::DeleteWindows(); }

int main(int argc, char *argv[]) {
  aequus::InitializeAequus();
  aequus::video::NewWindow("Aequus", 500, 500);
  aequus::video::LoadFont("resources/Roboto");
  aequus::video::fontmap["Roboto"].ScaleFont("1", 80, 80);
  SDL_Renderer *renderer =
      aequus::video::windows[0].windowrenderer.GetRenderer();

  // aequus::video::win->NewButtonObj("Quit", "Roboto", "resources/Button.png");
  // aequus::video::win->objects[0]->SetStateCase(RELEASE, release);
  aequus::video::Button bt1, bt2, bt3, bt4, bt5, bt6, bt7, bt8, bt9;
  bt1.Init("1", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt2.Init("2", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt3.Init("3", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt4.Init("4", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt5.Init("5", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt6.Init("6", "Roboto", "resources/Button.png", renderer, 200, 100);
  bt7.Init("7", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt8.Init("8", "Roboto", "resources/Button.png", renderer, 100, 100);
  bt9.Init("9", "Roboto", "resources/Button.png", renderer, 100, 100);
  aequus::video::Spacer sp;
  sp.Init(10, 10);
  bt1.SetStateCase(RELEASE, release);
  bt2.SetStateCase(RELEASE, release);
  bt3.SetStateCase(RELEASE, release);
  bt4.SetStateCase(RELEASE, release);
  bt5.SetStateCase(RELEASE, release);
  bt6.SetStateCase(RELEASE, release);
  bt7.SetStateCase(RELEASE, release);
  bt8.SetStateCase(RELEASE, release);
  bt9.SetStateCase(RELEASE, release);

  aequus::video::Layout lay1, lay2, lay3, mainlay;
  lay1.Init(HORIZONTALLAYOUT);
  lay1.AddObject(&bt1);
  lay1.AddObject(&bt2);
  lay1.AddObject(&bt3);
  lay2.Init(HORIZONTALLAYOUT);
  lay2.AddObject(&bt4);
  lay2.AddObject(&bt5);
  lay2.AddObject(&bt6);
  lay3.Init(HORIZONTALLAYOUT);
  lay3.AddObject(&bt7);
  lay3.AddObject(&bt8);
  lay3.AddObject(&bt9);
  mainlay.Init(VERTICALLAYOUT);
  mainlay.AddLayout(&lay1);
  mainlay.AddLayout(&lay2);
  mainlay.AddLayout(&lay3);
  aequus::video::win->SetLayout(&mainlay);
  // aequus::video::win->SetLayout(&lay2);
  while (aequus::video::AllClose() == false) {
    aequus::Frame();
  }
  aequus::TerminateAequus();
  return (1);
}
