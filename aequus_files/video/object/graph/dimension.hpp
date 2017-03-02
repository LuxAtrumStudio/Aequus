#ifndef VIDEO_OBJECT_GRAPH_DIMENSION_HPP
#define VIDEO_OBJECT_GRAPH_DIMENSION_HPP
#include <string>
namespace aequus {
namespace video {
struct Dimension {
  std::string title = "";
  int majormarks = 0, minormarks = 0;
  double min = -10, max = 10;
  int pixelstart = 0, pixelend = 0;
  double valtopixel = 0;
  bool Log = false;
  double logbase = 10;
};
}
}
#endif
