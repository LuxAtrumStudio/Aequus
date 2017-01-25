#ifndef VIDEO_VIDEO_HPP
#define VIDEO_VIDEO_HPP
#include "window/window.hpp"
#include <map>
namespace aequus {
namespace video {
extern std::map<std::string, Window> windowmap;
extern std::map<std::string, Window>::iterator winiterator;
bool AllClose();
void NewWindow(std::string title = "", int width = 200, int height = 200,
               WindowPositionFlags x = CENTERED,
               WindowPositionFlags y = CENTERED, Uint32 flags = WINDOWED);
void UpdateAll();
void HandleEvents();
}
}
#endif
