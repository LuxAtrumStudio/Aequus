#ifndef VIDEO_OBJECT_CANVAS_CANVAS_HPP
#define VIDEO_OBJECT_CANVAS_CANVAS_HPP
#include "../../../sdl_headers.hpp"
#include "../../video_enums.hpp"
#include "../object.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Canvas : public Object {
public:
  struct Shape {
    std::vector<int> color, backgroundcolor;
    std::vector<std::pair<int, int>> points;
    std::pair<int, int> origin;
    bool line, closed, filled;
  };
  void Init(int width, int height, SDL_Renderer *renderer);
  int InitShape(bool line, bool closed, bool filled);
  void SetShapeColor(std::vector<int> color, int shapeindex = -1);
  void SetShapeBackgroundColor(std::vector<int> color, int shapeindex = -1);
  void AddVertex(int x = 0, int y = 0, int shapeindex = -1);
  void SetShapeOrigin(int x, int y, int shapeindex = -1);
  void DeleteShape(int shapeindex = -1);
  void DrawArc(int x, int y, int w, int h, double thetastart, double thetaend);
  void DrawEllipse(int x, int y, int w, int h);
  void DrawLine(int x1, int y1, int x2, int y2);
  void DrawPoint(int x, int y);
  void DrawQuad(int vertexcount, ...);
  void DrawRect(int x, int y, int w, int h, int tl = -1, int tr = -1,
                int bl = -1, int br = -1);
  void DrawTriangle(int x1, int y1, int x2, int y2, int x3, int y3);
  void Update();
  void Delete();
  void Clear();

private:
  void DrawShape(int shapeindex);
  std::vector<Shape> shapes;
  std::vector<int> color = {255, 255, 255, 255};
  std::vector<int> backgroundcolor = {0, 0, 0, 255};
  SDL_Renderer *texturerenderer;
};
}
}
#endif
