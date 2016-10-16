#ifndef _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
#include "../../sdl_headers.h"
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
    int x, y, z;
    double doublex, doubley, doublez;
  };
  // Initalizes Advanced object functions
  void InitalizeAdvObj(SDL_Renderer *renderer = NULL, int counter = 0,
                       std::string resource = "resources/");
  // Creates a graph from a data file that folows the format:
  // vector string titles (Graph Title) (x-axis name) (y-axis name)
  // vector value (x-axis name) ....
  // vector value (y-axis name) ....
  void CreateGraph(std::string datafile, int width = 100, int height = 100,
                   SDL_Renderer *renderer = NULL);

private:
  // Pointer to logging locaiton
  int logloc = 0;
  // Pointer to currently set sdl renderer
  SDL_Renderer *objrenderer;
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
};
}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
