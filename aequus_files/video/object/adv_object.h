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
  // Used to set points of either 2D or 3D
  struct Value {
    double x, y, z;
  };
  // Used to store single line graph data
  struct GraphData {
    std::string title;
    std::vector<Value> points;
  };
  // Initalizes Advanced object functions
  void InitializeAdvObj(Renderer renderer, int counter = 0,
                        std::string resource = "resources/");
  // Creates a graph from a data file that folows the format:
  // vector string titles (Graph Title) (x-axis name) (y-axis name)
  // vector value (x-axis name) ....
  // vector value (y-axis name) ....
  void CreateGraph(std::string datafile, int width = 100, int height = 100);
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
  // Stores the domain and range for graphs
  double minx, maxx, miny, maxy, minz, maxz;
  // The object class for the actual advanced object
  // Loads the data for 2D graphs
  void LoadGraphData(std::string datafile = "NULL");
};
}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
