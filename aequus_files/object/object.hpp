#ifndef AEQUUS_OBJECT_HPP
#define AEQUUS_OBJECT_HPP
#include <memory>
#include "object_base.hpp"
namespace aequus {
  class Object {
   public:
    Object();
    ~Object();
    int Type();
    void Display();

   private:
    std::shared_ptr<ObjectBase> ptr = NULL;
  };
}
#endif
