#ifndef VIDEO_OBJECT_GRAPH_PLOT_HPP
#define VIDEO_OBJECT_GRAPH_PLOT_HPP
#include "../../../sdl_headers.hpp"
#include "dimension.hpp"
#include <duco.h>
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Plot {
public:
  void Init(std::string str, bool datafile = false);
  void SetGraphData(int graphwidth, int graphheight,
                    std::vector<Dimension> dims);
  void GenorateData();
  void Display();
  void Delete();

private:
  int graphwidth, graphheight;
  std::vector<Dimension> dimensions;

  //   void Init(std::string eq);
  //   void GenPlot(double min, double max, double step);
  //   void SetColor(std::vector<int> color);
  //   void SetColorMap(std::vector<std::vector<int>> incolormap, bool range);
  //   void Display(SDL_Renderer *renderer, int graphwidth, int graphheight,
  //                double domainmin, double domainmax, double rangemin,
  //                double rangemax, int domainstartpix, int rangestartpix,
  //                double domaintopix, double rangetopix);
  //   void LoadColor(double x, double y, SDL_Renderer *renderer,
  //                  std::vector<double> data);
  //   std::vector<std::pair<double, double>> GetPoints();
  //   virtual void Delete();
  //
  // private:
  //   std::vector<std::pair<double, double>> vals;
  //   std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
  //       colormap;
  //   duco::equation::Equation ploteq;
};
}
}
#endif
