#include "../object.hpp"
#include "../object_base.hpp"
#include "layout.hpp"

aequus::Layout::Layout() {}

aequus::Layout::Layout(int type) { format = type; }

aequus::Layout::~Layout() {}

void aequus::Layout::SetFormat(int type) { format = type; }

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  for (int i = 0; i < sub_objects.size(); i++) {
    sub_objects[i].Display();
  }
}

void aequus::Layout::AddSubObject(Object obj) { sub_objects.push_back(obj); }

int aequus::Layout::GetFormat() { return (format); }
