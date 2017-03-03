#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "textinput.hpp"
#include <pessum.h>
#include <string>

void aequus::video::Spacer::Init(int w, int h) {}

void aequus::video::Spacer::Delete() { width = 0, height = 0; }
