#ifndef AEQUUS_GEOMETRY_GEOMETRY_HPP
#define AEQUUS_GEOMETRY_GEOMETRY_HPP

#include <vector>

#include "types.hpp"

namespace aequus {
  namespace object {
    class Geometry {
     public:
      Geometry();
      ~Geometry();

      void CreateShape(std::vector<Point> verticies);

     protected:
     private:
      void InitGeometry();
      void GenerateVerticies();

      std::vector<Point> verticies_;
      int vertex_count_;

      Color color_;
    };
  }  // namespace object
}  // namespace aequus

#endif /* ifndef AEQUUS_GEOMETRY_GEOMETRY_HPP */
