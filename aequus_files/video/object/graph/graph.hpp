#ifndef VIDEO_OBJECT_GRAPH_GRAPH_HPP
#define VIDEO_OBJECT_GRAPH_GRAPH_HPP
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "plot/plot_headers.hpp"
#include <map>
#include <string>
#include <vector>
namespace aequus {
namespace video {

// [ ]Linear Plots
// [ ]Smooth Plots
// [ ]Constant Plots
// [ ]Bar Plots
// [ ]Histograms
// [ ]Box Plots
// [ ]Comb Plots
// [ ]Arrow Plots
// [ ]Stacked Plots
// [ ]Area Plots
// [ ]Scatter Plots
// [ ]Polar Coords

class Graph : public Object {
public:
  void Init(int w, int h, SDL_Renderer *renderer);
  void LoadColorMap(std::string file);
  void AddColorSetting(std::vector<double> color);
  void AddPlot(Plot *newplot);
  void Update();
  void Delete();
  void Clear();

private:
  void DrawPlots();
  void DrawAxis();
  void DrawGrid();
  void CalcValToPix();
  void LoadColor(std::string comp);
  std::string textfontname = "";
  int width, height;
  int domainmajormarkecount = 10, domainminormarkcount = 1;
  int rangemajormarkcount = 10, rangeminormarkcount = 1;
  int domainoffset, rangeoffset, domainmax, rangemax;
  double dvaltopix = 0, rvaltopix = 0;
  std::vector<Plot *> plots;
  std::pair<double, double> domain, range;
  std::pair<std::string, std::string> axistitles;
  std::vector<std::vector<double>> colormap;
  std::map<std::string, std::vector<double>> colors;
  SDL_Renderer *texturerenderer;
};
}
}
#endif