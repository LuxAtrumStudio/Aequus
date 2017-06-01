#ifndef AEQUUS_OBJECT_PTR_HPP
#define AEQUUS_OBJECT_PTR_HPP
#include <memory>
#include "object.hpp"
#include "layout/layout_headers.hpp"
#include "image/image_headers.hpp"
namespace aequus {
  typedef std::shared_ptr<aequus::ObjectBase> Object;
  std::shared_ptr<aequus::ObjectBase> make_object(aequus::ObjectBase obj);
  std::shared_ptr<aequus::ObjectBase> make_object(aequus::Layout obj);
  std::shared_ptr<aequus::ObjectBase> make_object(aequus::Image obj);
}
#endif
