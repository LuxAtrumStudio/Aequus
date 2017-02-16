#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../../video.hpp"
#include "../object_headers.hpp"
#include "plot.hpp"
#include <duco.h>
#include <pessum.h>
#include <string>

void aequus::video::Plot::Init(std::string str, bool datafile) {
  if (datafile == false) {
    ploteq = duco::equation::Equation(str);
  }
}

void aequus::video::Plot::SetGraphData(int ingraphwidth, int ingraphheight,
                                       Dimension dom, Dimension ran) {
  graphwidth = ingraphwidth;
  graphheight = ingraphheight;
  domain = dom;
  range = ran;
}

void aequus::video::Plot::GenorateData() {
  points.clear();
  for (double i = domain.min; i <= domain.max;
       i += (domain.max - domain.min) / (double)graphwidth) {
    points.push_back(std::make_pair(i, ploteq.SolveEquation(i)));
  }
}

void aequus::video::Plot::Display(SDL_Renderer *renderer) {
  std::pair<int, int> pix, nextpix, step;
  for (int i = 0; i < points.size() - 1; i++) {
    pix = ConvertToPix(points[i]);
    nextpix = ConvertToPix(points[i + 1]);
    step.first = nextpix.first - pix.first;
    if (step.first != 0) {
      step.first /= abs(step.first);
    }
    step.second = nextpix.second - pix.second;
    if (step.second != 0) {
      step.second /= abs(step.second);
    }
    while (pix.first != nextpix.first || pix.second != nextpix.second) {
      if (pix.first < graphwidth && pix.first >= 0 &&
          pix.second < graphheight && pix.second >= 0) {
        LoadColor(points[i], renderer);
        SDL_RenderDrawPoint(renderer, pix.first, pix.second);
      }
      if (pix.first != nextpix.first) {
        pix.first += step.first;
      }
      if (pix.second != nextpix.second) {
        pix.second += step.second;
      }
    }
    SDL_RenderDrawPoint(renderer, pix.first, pix.second);
  }
}

void aequus::video::Plot::SetColorMap(std::vector<std::vector<int>> map,
                                      bool range) {
  if (range == false) {
    colormap.first = map;
  } else if (range == true) {
    colormap.second = map;
  }
}

void aequus::video::Plot::Delete() { points.clear(); }

std::pair<int, int>
aequus::video::Plot::ConvertToPix(std::pair<double, double> pos) {
  std::pair<int, int> pixel(0, 0);
  pixel.first = (pos.first - domain.min) * domain.valtopixel;
  pixel.second = (pos.second - range.min) * range.valtopixel;
  pixel.first += domain.pixelstart;
  pixel.second = graphheight - (pixel.second + range.pixelstart);
  return (pixel);
}

void aequus::video::Plot::LoadColor(std::pair<double, double> point,
                                    SDL_Renderer *renderer) {
  if (colormap.first.size() == 1 && colormap.second.size() == 0) {
    SDL_SetRenderDrawColor(renderer, colormap.first[0][0], colormap.first[0][1],
                           colormap.first[0][2], colormap.first[0][3]);
  } else if (colormap.first.size() > 0 || colormap.second.size() > 0) {
    double maxdif =
        (domain.max - domain.min) / (double)(colormap.first.size() - 1);
    double red = 0, green = 0, blue = 0, alpha = 0;
    for (int i = 0; i < colormap.first.size(); i++) {
      double perc =
          (maxdif - fabs(point.first - ((maxdif * i) + domain.min))) / (maxdif);
      if (perc > 0) {
        red += (perc * colormap.first[i][0]);
        green += (perc * colormap.first[i][1]);
        blue += (perc * colormap.first[i][2]);
        alpha += (perc * colormap.first[i][3]);
      }
    }
    maxdif = (range.max - range.min) / (double)(colormap.second.size() - 1);
    double yred = 0, ygreen = 0, yblue = 0, yalpha = 0;
    for (int i = 0; i < colormap.second.size(); i++) {
      double perc =
          (maxdif - fabs(point.second - ((maxdif * i) + range.min))) / (maxdif);
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
  } else {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  }
}
