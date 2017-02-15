#ifndef VIDEO_OBJECT_GRAPH_DIMENSION_HPP
#define VIDEO_OBJECT_GRAPH_DIMENSION_HPP
#include <string>
namespace aequus {
namespace video {
struct Dimension {
  std::string title = "LABEL";
  int majormarks = 0, minormarks = 0;
  double min = -10, max = 10;
  int pixelstart = 0, pixelend = 0;
  double valtopixel = 0;
};
}
}
#endif
