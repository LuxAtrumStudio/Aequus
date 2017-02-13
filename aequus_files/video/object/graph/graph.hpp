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
  void AddColorSetting(std::vector<int> color);
  void AddPlot(Plot *newplot);
  void AddPlot(std::string ploteq);
  void Update();
  void Delete();
  void Clear();

private:
  void DrawPlots();
  void DrawAxis();
  void DrawGrid();
  void CalcValToPix();
  void LoadColor(std::string comp);
  int ConvertToPix(double val, bool isrange = false);
  std::string textfontname = "";
  int width, height;
  int domainmajormarkecount = 0, domainminormarkcount = 0;
  int rangemajormarkcount = 0, rangeminormarkcount = 0;
  int domainoffset, rangeoffset, domainmax, rangemax;
  double dvaltopix = 0, rvaltopix = 0;
  std::vector<Plot *> plots;
  std::pair<double, double> domain, range;
  std::pair<std::string, std::string> axistitles;
  std::vector<std::vector<int>> colormap;
  std::map<std::string, std::vector<int>> colors;
  SDL_Renderer *texturerenderer;
};
}
}
#endif
