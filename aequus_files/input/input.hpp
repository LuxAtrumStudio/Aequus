#ifndef INPUT_INPUT_HPP
#define INPUT_INPUT_HPP
#include "../sdl_headers.hpp"
#include <vector>
namespace aequus {
namespace input {
enum Modual { AUIDO, FRAMEWORK, INPUT, VIDEO };
extern std::vector<SDL_Event> events;
void PollEvents();
}
}
#endif
