#include <pessum.h>
#include <memory>
#include "object.hpp"
#include "object_ptr.hpp"

std::shared_ptr<aequus::ObjectBase> aequus::make_object(
    aequus::ObjectBase obj) {
  return (std::make_shared<aequus::ObjectBase>(obj));
}
