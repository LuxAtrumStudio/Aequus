#include "../../aequus_headers.hpp"
#include "../../sdl_headers.hpp"
#include "chart.hpp"
#include <iostream>
#include <pessum.h>
#include <string>
#include <vector>

aequus::video::Chart::Chart(ChartType ctype) { type = ctype; }

aequus::video::Chart::~Chart() {}
