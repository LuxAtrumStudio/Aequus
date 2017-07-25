#ifndef AEQUUS_STRUCT_POINT_POINT_HPP
#define AEQUUS_STRUCT_POINT_POINT_HPP

namespace aequus {
  class Point {
   public:
    Point();
    Point(int x_, int y_);
    ~Point();
    int x = 0, y = 0;

   private:
  };
}  // namespace aequus

#endif /* ifndef AEQUUS_STRUCT_POINT_POINT_HPP */
