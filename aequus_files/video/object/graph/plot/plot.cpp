#include "../../../../framework/framework.hpp"
#include "../../../../log_indices.hpp"
#include "../../../../sdl_headers.hpp"
#include "../../../video.hpp"
#include "plot.hpp"
#include <duco.h>
#include <iostream>
#include <map>
#include <pessum.h>
#include <stdarg.h>
#include <string>

void aequus::video::Plot::Init(std::string eq) {
  ploteq = duco::equation::Equation(eq);
}

void aequus::video::Plot::GenPlot(double min, double max, double step) {
  for (double i = min; i <= max; i += step) {
    vals.push_back(std::make_pair(i, ploteq.SolveEquation(i)));
  }
}

void aequus::video::Plot::Display(SDL_Renderer *renderer) {
  for (int i = 0; i < vals.size(); i++) {
    std::cout << "(" << vals[i].first << "," << vals[i].second << ")\n";
    SDL_RenderDrawPoint(renderer, vals[i].first, vals[i].second);
  }
}

std::vector<std::pair<double, double>> aequus::video::Plot::GetPoints() {
  return (vals);
}

void aequus::video::Plot::Delete() { vals.clear(); }
