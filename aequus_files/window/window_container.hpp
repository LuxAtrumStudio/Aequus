#ifndef AEQUUS_WINDOW_CONTAINER_HPP
#define AEQUUS_WINDOW_CONTAINER_HPP
#include <vector>
#include "window.hpp"
namespace aequus {
  class WindowContainer {
   public:
    Window* Find(std::string name);
    Window* Find(int index);
    void Display();
    void Clear();
    void Push(Window win);
    void Pop();
    int Size();
    std::vector<Window> windows;

   private:
  };
}
#endif
