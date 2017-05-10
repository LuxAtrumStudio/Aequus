#ifndef AEQUUS_OBJECT_PTR_HPP
#define AEQUUS_OBJECT_PTR_HPP
#include <memory>
#include "object.hpp"
namespace aequus {
  typedef std::shared_ptr<aequus::ObjectBase> Object;
  std::shared_ptr<aequus::ObjectBase> make_object(aequus::ObjectBase obj);
}
#endif
