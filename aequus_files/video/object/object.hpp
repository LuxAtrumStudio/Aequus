#ifndef VIDEO_OBJECT_OBJECT_HPP
#define VIDEO_OBJECT_OBJECT_HPP
namespace aequus {
namespace video {
enum ObjectType { TEXTURE };
class Object {
public:
  class Texture;
  class Surface;
  Object();
  ~Object();
  int width, height, x, y;

private:
  ObjectType type;
};
}
}
#endif
