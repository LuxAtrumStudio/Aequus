#ifndef VIDEO_OBJECT_GRAPH_PLOT_PLOT_HPP
#define VIDEO_OBJECT_GRAPH_PLOT_PLOT_HPP
#include "../../../sdl_headers.hpp"
#include <duco.h>
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Plot {
public:
  // void Init(std::string str, bool datafile = false);
  // void SetGraphData(int graphwidth, int graphheight, double domainminm,
  //                   double domainmax, double rangemin, double rangemax,
  //                   int domainstartpix, int rangestartpix, double
  //                   domaintopix,
  //                   double rangetopix);
  // void Display();

private:
  // int graphwidth, graphheight, domainstartpix, rangestartpix;
  // double domainmin, domainmax;

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