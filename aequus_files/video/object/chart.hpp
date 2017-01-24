#ifndef _AEQUUS_FILES_VIDEO_OBJECT_CHART_HPP
#define _AEQUUS_FILES_VIDEO_OBJECT_CHART_HPP
#include "../../sdl_headers.hpp"
namespace aequus {
namespace video {
class Chart {
public:
  enum ChartType { HISTOGRAM, BAR, PIE, LINE, AREA };
  Chart(ChartType ctype);
  virtual ~Chart();

private:
  ChartType type;
};
}
}
#endif
