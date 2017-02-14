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

void aequus::video::Plot::SetColor(std::vector<int> color) {
  colormap.first.clear();
  colormap.second.clear();
  colormap.first = {color};
}

void aequus::video::Plot::SetColorMap(std::vector<std::vector<int>> incolormap,
                                      bool range) {
  if (range == false) {
    colormap.first = incolormap;
  } else if (range == true) {
    colormap.second = incolormap;
  }
}

void aequus::video::Plot::Display(SDL_Renderer *renderer,
                                  std::vector<double> data) {
  for (int i = 0; i < vals.size() - 1; i++) {
    // std::cout << i << "\n";
    int pixx = ((vals[i].first - data[0]) * data[2]) + data[3];
    int pixy = data[9] - (((vals[i].second - data[4]) * data[6]) + data[7]);
    int nextpixx = ((vals[i + 1].first - data[0]) * data[2]) + data[3];
    int nextpixy =
        data[9] - (((vals[i + 1].second - data[4]) * data[6]) + data[7]);
    // std::cout << "(" << vals[i].first << "," << vals[i].second << ")\n";
    int xstep = (nextpixx - pixx);
    if (xstep != 0) {
      xstep /= abs(xstep);
    }
    int ystep = (nextpixy - pixy);
    if (ystep != 0) {
      ystep /= abs(ystep);
    }
    // std::cout << "x:" << pixx << "->" << nextpixx << ":" << xstep << "\n";
    // std::cout << "y:" << pixy << "->" << nextpixy << ":" << ystep << "\n";
    while (pixx != nextpixx || pixy != nextpixy) {
      if (vals[i].first >= data[0] && vals[i].first <= data[1] &&
          vals[i].second >= data[4] && vals[i].second <= data[5]) {
        LoadColor(vals[i].first, vals[i].second, renderer, data);
        SDL_RenderDrawPoint(renderer, pixx, pixy);
      }
      if (pixx != nextpixx) {
        pixx += xstep;
      }
      if (pixy != nextpixy) {
        pixy += ystep;
      }
    }
  }
}

void aequus::video::Plot::LoadColor(double x, double y, SDL_Renderer *renderer,
                                    std::vector<double> data) {
  if (colormap.first.size() == 1 && colormap.second.size() == 0) {
    SDL_SetRenderDrawColor(renderer, colormap.first[0][0], colormap.first[0][1],
                           colormap.first[0][2], colormap.first[0][3]);
  } else {
    double maxdif = (data[1] - data[0]) / (double)(colormap.first.size() - 1);
    double red = 0, green = 0, blue = 0, alpha = 0;
    for (int i = 0; i < colormap.first.size(); i++) {
      double perc = (maxdif - fabs(x - ((maxdif * i) + data[0]))) / (maxdif);
      if (perc > 0) {
        red += (perc * colormap.first[i][0]);
        green += (perc * colormap.first[i][1]);
        blue += (perc * colormap.first[i][2]);
        alpha += (perc * colormap.first[i][3]);
      }
    }
    maxdif = (data[5] - data[4]) / (double)(colormap.second.size() - 1);
    double yred = 0, ygreen = 0, yblue = 0, yalpha = 0;
    for (int i = 0; i < colormap.second.size(); i++) {
      double perc = (maxdif - fabs(y - ((maxdif * i) + data[4]))) / (maxdif);
      if (perc > 0) {
        yred += (perc * colormap.second[i][0]);
        ygreen += (perc * colormap.second[i][1]);
        yblue += (perc * colormap.second[i][2]);
        yalpha += (perc * colormap.second[i][3]);
      }
    }
    if (colormap.second.size() != 0 && colormap.first.size() != 0) {
      red = (red * 0.5) + (yred * 0.5);
      green = (green * 0.5) + (ygreen * 0.5);
      blue = (blue * 0.5) + (yblue * 0.5);
      alpha = (alpha * 0.5) + (yalpha * 0.5);
    } else if (colormap.first.size() == 0 && colormap.second.size() != 0) {
      red = yred;
      green = ygreen;
      blue = yblue;
      alpha = yalpha;
    }
    SDL_SetRenderDrawColor(renderer, (int)red, (int)green, (int)blue,
                           (int)alpha);
  }
}

std::vector<std::pair<double, double>> aequus::video::Plot::GetPoints() {
  return (vals);
}

void aequus::video::Plot::Delete() { vals.clear(); }
