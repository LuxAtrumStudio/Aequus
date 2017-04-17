#ifndef AEQUUS_OBJECT_HPP
#define AEQUUS_OBJECT_HPP
#include <memory>
#include "object_base.hpp"
namespace aequus {
  class Object {
   public:
    Object();
    Object(int type);
    Object(int type, SDL_Renderer* renderer);
    Object(int type, std::string str, SDL_Renderer* renderer);
    ~Object();
    int Type();
    void Display();
    std::shared_ptr<ObjectBase> ptr = NULL;

   private:
  };
}
#endif
