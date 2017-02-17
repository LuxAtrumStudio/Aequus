#ifndef VIDEO_OBJECT_GRAPH_GRAPH_HPP
#define VIDEO_OBJECT_GRAPH_GRAPH_HPP
#include "../../../sdl_headers.hpp"
#include "../object_headers.hpp"
#include "dimension.hpp"
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
enum GraphCoordinate { CARTESIAN, POLAR, CYLINDRICAL, SPHERICAL, CUSTOM };
class Graph : public Object {
public:
  std::vector<Plot> plots;

  void Init(int width, int height, SDL_Renderer *renderer);
  void Init(int width, int height, bool axis, bool grid, bool label, bool title,
            SDL_Renderer *renderer);

  void SetDrawAxis(bool setting);
  void SetDrawGrid(bool setting);
  void SetDrawLabel(bool setting);
  void SetDrawTitle(bool setting);
  void SetDrawEquation(bool setting);
  void ToggleDrawAxis();
  void ToggleDrawGrid();
  void ToggleDrawLabel();
  void ToggleDrawTitle();
  void ToggleDrawEquation();

  void SetColor(std::string name, std::vector<int> color);
  void SetColor(std::string name, std::vector<double> color);
  void SetColor(std::string name, int red, int green, int blue, int alpha);
  void SetColor(std::string name, double red, double green, double blue,
                double alpha);

  void SetGrid(int dim, int major, int minor);

  void SetRange(int dim, double min, double max);
  void SetAxisTitle(int dim, std::string title);
  void SetGraphTitle(std::string title);

  void SetFont(std::string name);
  void SetTitleFont(std::string name);
  void SetLabelFont(std::string name);

  std::vector<int> GetColor(std::string name);

  void AddPlot(Plot newplot);

  void Update();

  void Delete();

private:
  int graphwidth = 0, graphheight = 0;
  std::string fontname = "", titlefont = "", labelfont = "";
  SDL_Renderer *texturerenderer = NULL;

  bool dispaxis = false, dispgrid = false, displabel = false, disptitle = false,
       dispeqs = false;
  std::string graphtitle = "";
  std::map<std::string, std::vector<int>> colormap;
  Dimension domain, range;

  void DisplayGraph();
  void ClearGraph();
  void DisplayPlots();
  void DisplayAxis();
  // BUG on altered range
  void DisplayGrid();
  void DisplayLabel();
  void DisplayTitle();

  void CalculatePix();
  void LoadColor(std::string color);

  std::string ShortenDouble(double val);
  std::pair<int, int> ConvertToPix(std::vector<double> vals);
  // public:
  //   void Init(int w, int h, SDL_Renderer *renderer);
  //
  //   void SetColor(std::string name, std::vector<int> color);
  //   std::vector<int> GetColor(std::string name);
  //
  //   void AddPlot(Plot newplot);
  //
  //   void SetDrawAxis(bool draw);
  //   void SetDrawGrid(bool draw);
  //   void SetDrawLabel(bool draw);
  //   void SetDrawTitle(bool draw);
  //
  //   void SetDomainGridLines(int major, int minor);
  //   void SetRangeGridLines(int major, int minor);
  //
  //   void SetDomain(std::pair<double, double> newdomain);
  //   void SetRange(std::pair<double, double> newrange);
  //   void SetAxisTitle(std::pair<std::string, std::string> newtitle);
  //
  //   void Update();
  //   void Delete();
  //   void Clear();
  //
  // private:
  //   void DrawAll();
  //   void DrawPlots();
  //   void DrawAxis();
  //   void DrawGrid();
  //   void CalcValToPix();
  //   void LoadColor(std::string comp);
  //   int ConvertToPix(double val, bool isrange = false);
  //   std::string ShrinkString(std::string str);
  //   std::string textfontname = "";
  //   int width, height;
  //   int domainmajormarkcount = 0, domainminormarkcount = 0;
  //   int rangemajormarkcount = 0, rangeminormarkcount = 0;
  //   int domainoffset, rangeoffset, domainmax, rangemax;
  //   bool drawaxis = false, drawgrid = false, drawlabel = false, drawtitle =
  //   false;
  //   double dvaltopix = 0, rvaltopix = 0;
  //   std::vector<Plot> plots;
  //   std::pair<double, double> domain, range;
  //   std::pair<std::string, std::string> axistitles;
  //   std::map<std::string, std::vector<int>> colors;
  //   SDL_Renderer *texturerenderer;
};
}
}
#endif
