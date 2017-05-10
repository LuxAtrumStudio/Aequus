#include <pessum.h>
#include <vector>
#include "window.hpp"
#include "window_container.hpp"

std::shared_ptr<aequus::Window> aequus::WindowContainer::Find(
    std::string name) {
  std::shared_ptr<aequus::Window> win = NULL;
  bool found = false;
  for (int i = 0; i < windows.size() && found == false; i++) {
    if (windows[i]->window_name == name) {
      win = windows[i];
    }
  }
  return (win);
}

std::shared_ptr<aequus::Window> aequus::WindowContainer::Find(int index) {
  std::shared_ptr<aequus::Window> win = NULL;
  if (index > 0 && index < windows.size()) {
    win = windows[index];
  }
  return (win);
}

void aequus::WindowContainer::Display() {
  for (int i = 0; i < windows.size(); i++) {
    windows[i]->Display();
  }
}

void aequus::WindowContainer::Clear() {
  for (int i = 0; i < windows.size(); i++) {
    windows[i]->DeleteWindow();
  }
  windows.clear();
}

void aequus::WindowContainer::Push(std::shared_ptr<Window> win) {
  windows.push_back(win);
}

void aequus::WindowContainer::Pop() { windows.pop_back(); }

int aequus::WindowContainer::Size() { return (windows.size()); }
