#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../../video.hpp"
#include "../object_headers.hpp"
#include "plot.hpp"
#include <duco.h>
#include <iostream>
#include <pessum.h>
#include <string>

void aequus::video::Plot::Init(std::string str, bool datafile) {
  datasource = str;
  if (datafile == false) {
    ploteq = duco::equation::Equation(str);
  }
}

void aequus::video::Plot::SetGraphData(int ingraphwidth, int ingraphheight,
                                       Dimension dom, Dimension ran,
                                       std::pair<double, double> indatadomain) {
  graphwidth = ingraphwidth;
  graphheight = ingraphheight;
  domain = dom;
  range = ran;
  datadomain = indatadomain;
}

void aequus::video::Plot::SetResolution(int res) { resolution = res; }

void aequus::video::Plot::SetStepSize(double size) { stepsize = size; }

void aequus::video::Plot::SetPlotFormat(PlotType type) { displayformat = type; }

void aequus::video::Plot::SetPolar(bool setting) { polar = setting; }

void aequus::video::Plot::PlotBaseRange(bool setting) { rangebased = setting; }

void aequus::video::Plot::SetPointFormat(PointType type) {
  pointdisplayformat = type;
}

void aequus::video::Plot::SetPointRadius(int r) { pointradius = r; }

void aequus::video::Plot::GenorateData() {
  points.clear();
  double step;
  if (resolution > 0 && stepsize <= 0) {
    step = (datadomain.second - datadomain.first) / (double)resolution;
  } else if (resolution <= 0 && stepsize <= 0) {
    step = (datadomain.second - datadomain.first) / graphwidth;
  } else if (stepsize > 0) {
    step = stepsize;
  }
  for (double i = datadomain.first;
       i <= datadomain.second + (datadomain.second * 0.001); i += step) {
    points.push_back(std::make_pair(i, ploteq.SolveEquation(i)));
  }
}

void aequus::video::Plot::Display(SDL_Renderer *renderer, bool label,
                                  std::string fontname) {
  std::pair<int, int> pix, nextpix;
  for (int i = 0; i < points.size() - 1; i++) {
    pix = ConvertToPix(points[i]);
    nextpix = ConvertToPix(points[i + 1]);
    if (displayformat == COMB) {
      if (rangebased == true) {
        nextpix =
            ConvertToPix(std::make_pair(datadomain.first, points[i].second));
      } else if (rangebased == false) {
        nextpix = ConvertToPix(std::make_pair(points[i].first, range.min));
      }
    }
    double dist = sqrt(pow(nextpix.first - pix.first, 2) +
                       pow(nextpix.second - pix.second, 2));
    LoadColor(points[i], renderer);
    if ((displayformat == LINE || displayformat == CONSTANT ||
         displayformat == COMB) &&
        dist <= graphwidth &&
        (pix.first < graphwidth && pix.first >= domain.pixelstart &&
         pix.second < graphheight - range.pixelstart &&
         pix.second >= range.pixelend)) {
      SDL_RenderDrawLine(renderer, pix.first, pix.second, nextpix.first,
                         nextpix.second);
    }
    if (pointdisplayformat == DOT && pix.first < graphwidth - domain.pixelend &&
        pix.first >= domain.pixelstart &&
        pix.second < graphheight - range.pixelstart &&
        pix.second >= range.pixelend) {
      SDL_RenderDrawPoint(renderer, pix.first, pix.second);
    } else if (pointdisplayformat == CIRCLE) {
      for (double theta = 0; theta < 2 * 6.283; theta += 0.1) {
        if (pix.first + (int)(pointradius * cos(theta)) <
                graphwidth - domain.pixelend &&
            pix.first + (int)(pointradius * cos(theta)) >= domain.pixelstart &&
            pix.second + (int)(pointradius * sin(theta)) <
                graphheight - range.pixelstart &&
            pix.second + (int)(pointradius * sin(theta)) >= range.pixelend) {
          SDL_RenderDrawPoint(renderer,
                              pix.first + (int)(pointradius * cos(theta)),
                              pix.second - (int)(pointradius * sin(theta)));
        }
      }
    } else if (pointdisplayformat == SQUARE) {
    }
  }
  if (label == true && fontname != "") {
    Font font = GetFont(fontname);
    Text text;
    text.Init(datasource, fontname, renderer);
    pix = ConvertToPix(points[0]);
    LoadColor(points[0], renderer);
    if (red != 0 && green != 0 && blue != 0 && alpha != 0) {
      text.SetTextColor(std::vector<int>{(int)(red), (int)(green), (int)(blue),
                                         (int)(alpha)});
    }
    int width, height;
    font.GetSize(datasource, width, height);
    if (pix.second >= range.pixelstart) {
      pix.second -= height;
    }
    if (pix.first > graphwidth - width) {
      pix.first = graphwidth - width;
    }
    text.SetPos(pix.first, pix.second);
    text.Display();
    text.Delete();
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
  if (polar == true) {
    pos = std::make_pair(pos.second * cos(pos.first),
                         pos.second * sin(pos.first));
  }
  pixel.first = (pos.first - domain.min) * domain.valtopixel;
  pixel.second = (pos.second - range.min) * range.valtopixel;
  pixel.first += domain.pixelstart;
  pixel.second = graphheight - (pixel.second + range.pixelstart);
  return (pixel);
}

void aequus::video::Plot::LoadColor(std::pair<double, double> point,
                                    SDL_Renderer *renderer) {
  if (colormap.first.size() == 1 && colormap.second.size() == 0) {
    red = colormap.first[0][0];
    green = colormap.first[0][1];
    blue = colormap.first[0][2];
    alpha = colormap.first[0][3];
    SDL_SetRenderDrawColor(renderer, colormap.first[0][0], colormap.first[0][1],
                           colormap.first[0][2], colormap.first[0][3]);
  } else if (colormap.second.size() == 1 && colormap.first.size() == 0) {
    red = colormap.second[0][0];
    green = colormap.second[0][1];
    blue = colormap.second[0][2];
    alpha = colormap.second[0][3];
    SDL_SetRenderDrawColor(renderer, colormap.second[0][0],
                           colormap.second[0][1], colormap.second[0][2],
                           colormap.second[0][3]);
  } else if (colormap.first.size() > 0 || colormap.second.size() > 0) {
    double maxdif = (datadomain.second - datadomain.first) /
                    (double)(colormap.first.size() - 1);
    red = 0, green = 0, blue = 0, alpha = 0;
    for (int i = 0; i < colormap.first.size(); i++) {
      double perc =
          (maxdif - fabs(point.first - ((maxdif * i) + datadomain.first))) /
          (maxdif);
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
    red = 255;
    blue = 255;
    green = 255;
    alpha = 255;
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  }
}
