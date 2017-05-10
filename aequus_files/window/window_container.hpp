#ifndef AEQUUS_WINDOW_CONTAINER_HPP
#define AEQUUS_WINDOW_CONTAINER_HPP
#include <memory>
#include <vector>
#include "window.hpp"
namespace aequus {
  class WindowContainer {
   public:
    std::shared_ptr<aequus::Window> Find(std::string name);
    std::shared_ptr<aequus::Window> Find(int index);
    void Display();
    void Clear();
    void Push(std::shared_ptr<Window> win);
    void Pop();
    int Size();
    std::vector<std::shared_ptr<Window>> windows;

   private:
  };
}
#endif
