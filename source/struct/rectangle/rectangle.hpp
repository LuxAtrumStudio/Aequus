#ifndef AEQUUS_STRUCT_RECTANGLE_RECTANGLE_HPP
#define AEQUUS_STRUCT_RECTANGLE_RECTANGLE_HPP

#include <experimental/optional>

#include "../point/point.hpp"

namespace aequus {
  struct Rectangle {
   public:
    Rectangle();
    Rectangle(int x_, int y_);
    Rectangle(int x_, int y_, int w_, int h_);
    ~Rectangle();

    void SetAttr(std::string name, int value_0);
    void SetAttr(std::string name, int value_0, int value_1);
    void SetAttr(std::string name, Point value);
    int GetAttr(std::string name);
    Point GetAttrPair(std::string name);

    int x = 0, y = 0, w = 0, h = 0;

   private:
  };
}  // namespace aequus

#endif /* ifndef AEQUUS_STRUCT_RECTANGLE_RECTANGLE_HPP */
