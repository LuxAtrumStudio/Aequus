#include "../object.hpp"
#include "../object_base.hpp"
#include "layout.hpp"

aequus::Layout::Layout() {}

aequus::Layout::~Layout() {}

int aequus::Layout::Type() { return (AEQ_OBJ_LAYOUT); }

void aequus::Layout::Display() {
  for (int i = 0; i < sub_objects.size(); i++) {
    sub_objects[i].Display();
  }
}
