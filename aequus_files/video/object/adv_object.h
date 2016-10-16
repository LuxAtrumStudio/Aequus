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
class Adv_Object {
public:
  enum AdvType { GRAPH, MODEL, 3DGRAPH };
  void CreateGraph(std::string datafile, SDL_Renderer * = NULL);
}
}
}
#endif // !_AEQUUS_FILES_VIDEO_OBJECT_ADV_OBJECT_H_
