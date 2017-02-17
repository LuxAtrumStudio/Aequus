#ifndef VIDEO_OBJECT_GRAPH_PLOT_HPP
#define VIDEO_OBJECT_GRAPH_PLOT_HPP
#include "../../../sdl_headers.hpp"
#include "dimension.hpp"
#include <duco.h>
#include <string>
#include <vector>
namespace aequus {
namespace video {
enum PlotType { LINE, CONSTANT, BAR, ARROW, AREA, SCATTER };
class Plot {
public:
  void Init(std::string str, bool datafile = false);

  void SetGraphData(int ingraphwidth, int ingraphheight, Dimension dom,
                    Dimension ran, std::pair<double, double> indatadomain);
  void GenorateData();

  void Display(SDL_Renderer *renderer, bool label = false,
               std::string fontname = "");

  void SetColorMap(std::vector<std::vector<int>> map, bool range = false);

  void Delete();

private:
  void SubGen(int index, std::vector<std::pair<std::string, double>> variable);
  std::pair<int, int> ConvertToPix(std::pair<double, double> pos);
  void LoadColor(std::pair<double, double> point, SDL_Renderer *renderer);

  bool polar = true;
  PlotType displayformat = LINE;
  int graphwidth, graphheight;
  double red = 255, blue = 255, green = 255, alpha = 255;
  Dimension domain, range;
  std::pair<double, double> datadomain;
  std::vector<std::pair<double, double>> points;
  std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
      colormap;
  duco::equation::Equation ploteq;
  std::string datasource;
};
}
}
#endif
