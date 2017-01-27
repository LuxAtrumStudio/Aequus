#ifndef VIDEO_VIDEO_HPP
#define VIDEO_VIDEO_HPP
#include "window/window.hpp"
#include <map>
#include <vector>
namespace aequus {
namespace video {
extern std::vector<Window> windows;
extern Window *win;
extern int winindex;
bool AllClose();
void NewWindow(std::string title = "", int width = 200, int height = 200,
               WindowPositionFlags x = CENTERED,
               WindowPositionFlags y = CENTERED, Uint32 flags = WINDOWED);
void UpdateAll();
void HandleEvents();
void DeleteWindows();
int GetIndex(std::string name);
}
}
#endif
