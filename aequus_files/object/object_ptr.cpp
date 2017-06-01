#include <pessum.h>
#include <memory>
#include "object.hpp"
#include "object_ptr.hpp"
#include "layout/layout_headers.hpp"
#include "image/image_headers.hpp"

std::shared_ptr<aequus::ObjectBase> aequus::make_object(
    aequus::ObjectBase obj) {
  return (std::make_shared<aequus::ObjectBase>(obj));
}

std::shared_ptr<aequus::ObjectBase> aequus::make_object(aequus::Layout obj){
  return(std::make_shared<aequus::Layout>(obj));
}

std::shared_ptr<aequus::ObjectBase> aequus::make_object(aequus::Image obj){
  return(std::make_shared<aequus::Image>(obj));
}
