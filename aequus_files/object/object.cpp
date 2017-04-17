#include "object.hpp"
#include "object_base.hpp"

aequus::Object::Object() {}

aequus::Object::~Object() { ptr = NULL; }

int aequus::Object::Type() { return (ptr->Type()); }

void aequus::Object::Display() { ptr->Display(); }
