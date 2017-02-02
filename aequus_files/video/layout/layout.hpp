#ifndef VIDEO_LAYOUT_LAYOUT_HPP
#define VIDEO_LAYOUT_LAYOUT_HPP
#include "../../sdl_headers.hpp"
#include "../object/object.hpp"
#include "../video_enums.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Layout {
public:
  void Init(LayoutFormat format);
  void Display();
  void AddObject(Object obj);
  void AddLayout(Layout lay);
  void Delete();
  void SetSize(int newwidth, int newheight);
  void SetPos(int x, int y);

private:
  void ReSize();
  int width = 0, height = 0;
  int layoutx = 0, layouty = 0;
  LayoutFormat layoutformat;
  enum LayoutObjectType { OBJ, LAY };
  std::vector<LayoutObjectType> parts;
  std::vector<Object *> objects;
  std::vector<Layout *> sublayouts;
};
}
}
#endif
