#ifndef VIDEO_OBJECT_GRAPH_PLOT_HPP
#define VIDEO_OBJECT_GRAPH_PLOT_HPP
#include "../../../sdl_headers.hpp"
#include "dimension.hpp"
#include <duco.h>
#include <string>
#include <vector>
namespace aequus {
namespace video {
enum PlotType { LINE, CONSTANT, BAR, COMB, SCATTER };
enum PointType { DOT, CIRCLE, SQUARE, DIAMOND, STAR, PLUS };
class Plot {
public:
  void Init(std::string str, bool datafile = false);

  void SetGraphData(int ingraphwidth, int ingraphheight, Dimension dom,
                    Dimension ran, std::pair<double, double> indatadomain);

  void SetResolution(int res);
  void SetStepSize(double size);
  void SetPolar(bool setting);

  void SetPlotFormat(PlotType type);
  void SetPointFormat(PointType type);
  void SetPointRadius(int r);
  void PlotBaseRange(bool setting);
  void SetBarWidth(int width);

  void GenorateData();

  void Display(SDL_Renderer *renderer, bool label = false,
               std::string fontname = "");

  void SetColorMap(std::vector<std::vector<int>> map, bool range = false);

  void Delete();

private:
  void DisplayPoint(std::pair<int, int> point, SDL_Renderer *renderer);
  void DisplayLabel(SDL_Renderer *renderer, std::string fontname);

  void DisplayScatter(SDL_Renderer *renderer, bool label, std::string fontname);
  void DisplayLine(SDL_Renderer *renderer, bool label, std::string fontname);
  void DisplayConstant(SDL_Renderer *renderer, bool label,
                       std::string fontname);
  void DisplayBar(SDL_Renderer *renderer, bool label, std::string fontname);
  void DisplayComb(SDL_Renderer *renderer, bool label, std::string fontname);

  std::pair<int, int> ConvertToPix(std::pair<double, double> pos);
  std::pair<double, double> ConvertToVal(std::pair<int, int> pix);
  void LoadColor(std::pair<double, double> point, SDL_Renderer *renderer);

  bool rangebased = false;
  bool polar = false;
  PlotType displayformat = SCATTER;
  PointType pointdisplayformat = DOT;
  int pointradius = 2;
  int graphwidth, graphheight;
  double red = 255, blue = 255, green = 255, alpha = 255;
  int resolution = 0;
  double stepsize = 0;
  int barwidth = 10;
  Dimension domain, range;
  std::pair<double, double> datadomain, rangedomain;
  std::vector<std::pair<double, double>> points;
  std::pair<std::vector<std::vector<int>>, std::vector<std::vector<int>>>
      colormap;
  duco::equation::Equation ploteq;
  std::string datasource;
};
}
}
#endif
