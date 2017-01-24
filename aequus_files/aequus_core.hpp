#ifndef _AEQUUS_FILES_AEQUUS_CORE_H_
#define _AEQUUS_FILES_AEQUUS_CORE_H_
#include <ctime>
namespace aequus {
namespace framework {}
namespace video {}
namespace input {}
namespace audio {}
namespace fileio {}
struct ValueGroup {
  float x, y, z;
  float r, g, b, a;
  float w, h;
};
extern int FPS;
extern time_t FPStimecheck;
void Frame();
}
#endif // !_AEQUUS_AEQUUS_CORE_H_
