#ifndef VIDEO_OBJECT_TEXTURE_TEXTURE_HPP
#define VIDEO_OBJECT_TEXTURE_TEXTURE_HPP
#include "../object.hpp"
namespace aequus {
namespace video {
class Object::Texture : public Object {
public:
  Texture(Surface);

private:
};
}
}
#endif
