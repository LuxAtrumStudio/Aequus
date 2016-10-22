#ifndef _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#include "../../sdl_headers.h"
#include "object.h";
#include "surface.h"
#include "text.h"
#include "texture.h"
#include <string>
#include <vector>
namespace aequus {
namespace video {
// Advanced Object class is used to create complex objects that utilize many sub
// objects
class AdvObject {
public:
  // Used to define what type of advanced object is being used
  enum AdvType { GRAPH, MODEL, DGRAPH };
  // Used to define what graph type
  enum GraphType { LINE, BAR, SCATTER, PIE, PLOT };
  // Used to store single line graph data
  struct GraphData {
    std::string title;
    std::vector<aequus::ValueGroup> points;
  };
  // Initalizes Advanced object functions
  void InitializeAdvObj(Renderer renderer, int counter = 0,
                        std::string resource = "resources/");
  // Creates a graph from a data file that folows the format:
  // vector string titles (Graph Title) (x-axis name) (y-axis name)
  // vector value (x-axis name) ....
  // vector value (y-axis name) ....
  void CreateGraph(std::string datafile, GraphType graphtype,
                   int graphwidth = 100, int graphheight = 100,
                   bool graphbackground = false, bool graphaxis = false,
                   bool graphgrid = false, bool graphvalues = false,
                   bool graphlables = false, bool graphtitle = false,
                   double xstart = 0, double xend = 0, double ystart = 0,
                   double yend = 0);
  // Displays the advanced object
  void Display();
  Object globalobj;

private:
  // Pointer to logging locaiton
  int logloc = 0;
  // The advanced object count for the window
  int advobjcount = 0;
  // Pointer to currently set sdl renderer
  Renderer objrenderer;
  // Standard directory for all resources
  // Image files are stored in "images/"
  // Font files are stored in "fonts/"
  std::string resourcedir = "resources/";
  // Storage for position and size values of the advanced object
  int posx, posy, width, height;
  // The color modification data for the object
  //[0] red, [1] green, [2] blue, [3] alpha
  double colormod[4];
  // Used to define advanced object type
  AdvType objtype;
  // Titles for graphs
  std::string graphtitle;
  std::vector<std::string> titles;
  // Storage for graph points in either 2D or 3D
  std::vector<GraphData> graphs;
  // Stores the colors for differnt graphs
  std::vector<ValueGroup> colors;
  // Stores the domain and range for graphs
  double minx, maxx, miny, maxy, minz, maxz, stepx, stepy, stepz;
  // The object class for the actual advanced object
  bool axis, values, lables, title, grid, background;
  // Stores the background color for the graphs
  ValueGroup backgroundcolor;
  // Loads the data for 2D graphs
  void LoadGraphData(std::string datafile = "NULL");
  // Computes the values for the plot graphs
  void ComputeDataPoints(std::string funciton = "y = x");
  // Draws the line graphs to the object
  void DrawLineGraph();
  // Draws the background for grapns
  void DrawBackground(int colorjump = 0);
  // Draws the axis for graphs
  void DrawAxis();
  // Draws the coordinate grid for graphs
  void DrawGrid();
};
}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
