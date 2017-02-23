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

void aequus::video::Plot::SetPolar(bool setting) { polar = setting; }

void aequus::video::Plot::SetPlotFormat(PlotType type) { displayformat = type; }

void aequus::video::Plot::SetPointFormat(PointType type) {
  pointdisplayformat = type;
}

void aequus::video::Plot::SetPointRadius(int r) { pointradius = r; }

void aequus::video::Plot::PlotBaseRange(bool setting) { rangebased = setting; }

void aequus::video::Plot::SetBarWidth(int width) { barwidth = width; }

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
  rangedomain = std::make_pair(ploteq.SolveEquation(datadomain.first),
                               ploteq.SolveEquation(datadomain.first));
  for (double i = datadomain.first;
       i <= datadomain.second + (datadomain.second * 0.0001); i += step) {
    points.push_back(std::make_pair(i, ploteq.SolveEquation(i)));
    if (points[points.size() - 1].second < rangedomain.first) {
      rangedomain.first = points[points.size() - 1].second;
    }
    if (points[points.size() - 1].second > rangedomain.second) {
      rangedomain.second = points[points.size() - 1].second;
    }
  }
  if (polar == false) {
    rangedomain.first = range.min;
    rangedomain.second = range.max;
  }
}

void aequus::video::Plot::Display(SDL_Renderer *renderer, bool label,
                                  std::string fontname) {
  if (displayformat == SCATTER) {
    DisplayScatter(renderer, label, fontname);
  } else if (displayformat == LINE) {
    DisplayLine(renderer, label, fontname);
  } else if (displayformat == CONSTANT) {
    DisplayConstant(renderer, label, fontname);
  } else if (displayformat == BAR) {
    DisplayBar(renderer, label, fontname);
  } else if (displayformat == COMB) {
    DisplayComb(renderer, label, fontname);
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

void aequus::video::Plot::DisplayPoint(std::pair<int, int> point,
                                       SDL_Renderer *renderer) {
  if (pointdisplayformat == DOT) {
    if (Check(point.first, point.second) == true) {
      SDL_RenderDrawPoint(renderer, point.first, point.second);
    }
  } else if (pointdisplayformat == CIRCLE) {
    for (double theta = 0; theta < 6.283; theta += 0.1) {
      if (Check(point.first + (int)(pointradius * cos(theta)),
                point.second - (int)(pointradius * sin(theta))) == true) {
        SDL_RenderDrawPoint(renderer,
                            point.first + (int)(pointradius * cos(theta)),
                            point.second - (int)(pointradius * sin(theta)));
      }
    }
  } else if (pointdisplayformat == SQUARE) {
    DisplayPixelLine(
        std::make_pair(point.first - pointradius, point.second - pointradius),
        std::make_pair(point.first + pointradius, point.second - pointradius),
        renderer);
    DisplayPixelLine(
        std::make_pair(point.first - pointradius, point.second + pointradius),
        std::make_pair(point.first + pointradius, point.second + pointradius),
        renderer);
    DisplayPixelLine(
        std::make_pair(point.first - pointradius, point.second - pointradius),
        std::make_pair(point.first - pointradius, point.second + pointradius),
        renderer);
    DisplayPixelLine(
        std::make_pair(point.first + pointradius, point.second - pointradius),
        std::make_pair(point.first + pointradius, point.second + pointradius),
        renderer);
  } else if (pointdisplayformat == DIAMOND) {
    DisplayPixelLine(std::make_pair(point.first, point.second - pointradius),
                     std::make_pair(point.first + pointradius, point.second),
                     renderer);
    DisplayPixelLine(std::make_pair(point.first, point.second - pointradius),
                     std::make_pair(point.first - pointradius, point.second),
                     renderer);
    DisplayPixelLine(std::make_pair(point.first, point.second + pointradius),
                     std::make_pair(point.first + pointradius, point.second),
                     renderer);
    DisplayPixelLine(std::make_pair(point.first, point.second + pointradius),
                     std::make_pair(point.first - pointradius, point.second),
                     renderer);
  } else if (pointdisplayformat == STAR || pointdisplayformat == PLUS) {
    DisplayPixelLine(std::make_pair(point.first - pointradius, point.second),
                     std::make_pair(point.first + pointradius, point.second),
                     renderer);
    DisplayPixelLine(std::make_pair(point.first, point.second - pointradius),
                     std::make_pair(point.first, point.second + pointradius),
                     renderer);
    if (pointdisplayformat == STAR) {
      DisplayPixelLine(std::make_pair(point.first - (0.707106 * pointradius),
                                      point.second - (0.707106 * pointradius)),
                       std::make_pair(point.first + (0.707106 * pointradius),
                                      point.second + (0.707106 * pointradius)),
                       renderer);
      DisplayPixelLine(std::make_pair(point.first - (0.707106 * pointradius),
                                      point.second + (0.707106 * pointradius)),
                       std::make_pair(point.first + (0.707106 * pointradius),
                                      point.second - (0.707106 * pointradius)),
                       renderer);
    }
  }
}

void aequus::video::Plot::DisplayLabel(SDL_Renderer *renderer,
                                       std::string fontname) {
  Font font = GetFont(fontname);
  Text text;
  text.Init(datasource, fontname, renderer);
  std::pair<int, int> pix = ConvertToPix(points[0]);
  LoadColor(points[0], renderer);
  if (red != 0 && green != 0 && blue != 0 && alpha != 0) {
    text.SetTextColor(
        std::vector<int>{(int)(red), (int)(green), (int)(blue), (int)(alpha)});
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

void aequus::video::Plot::DisplayDataLine(std::pair<double, double> start,
                                          std::pair<double, double> end,
                                          SDL_Renderer *renderer) {
  std::pair<int, int> pixel(-1, -1), lastpixel(-1, -1);
  std::pair<double, double> step(0, 0);
  double slope;
  if (start.first > end.first) {
    std::pair<double, double> temp = start;
    start = end;
    end = temp;
  }
  step.first = (domain.max - domain.min) / (double)graphwidth;
  step.second = (range.max - range.min) / (double)graphheight;
  if (start.first == end.first) {
    while (start.second < end.second - step.second) {
      pixel = ConvertToPix(start);
      if (Check(pixel.first, pixel.second) == true) {
        if (lastpixel.first != -1) {
          DisplayPixelLine(pixel, lastpixel, renderer);
        }
        lastpixel = pixel;
      } else {
        lastpixel.first = -1;
      }
      start.second += step.second;
    }
    while (start.second > end.second + step.second) {
      pixel = ConvertToPix(start);
      if (Check(pixel.first, pixel.second) == true) {
        if (lastpixel.first != -1) {
          DisplayPixelLine(pixel, lastpixel, renderer);
        }
        lastpixel = pixel;
      } else {
        lastpixel.first = -1;
      }
      start.second -= step.second;
    }
  }
  while (start.first < end.first) {
    slope = (end.second - start.second);
    if (end.first != start.first &&
        (end.first - start.first) >= (step.first / 2)) {
      slope /= (end.first - start.first);
    }
    if (start.second < end.second) {
      for (int i = 0; i < round(slope); i++) {
        pixel = ConvertToPix(start);
        if (Check(pixel.first, pixel.second) == true) {
          if (lastpixel.first != -1) {
            DisplayPixelLine(pixel, lastpixel, renderer);
          }
          lastpixel = pixel;
        } else {
          lastpixel.first = -1;
        }
        start.second += step.second;
      }
    } else if (start.second > end.second) {
      for (int i = 0; i > round(slope); i--) {
        pixel = ConvertToPix(start);
        if (Check(pixel.first, pixel.second) == true) {
          SDL_RenderDrawPoint(renderer, pixel.first, pixel.second);
          if (lastpixel.first != -1) {
            DisplayPixelLine(pixel, lastpixel, renderer);
          }
          lastpixel = pixel;
        } else {
          lastpixel.first = -1;
        }
        start.second -= step.second;
      }
    }
    if (slope == 0) {
      pixel = ConvertToPix(start);
      if (Check(pixel.first, pixel.second) == true) {
        if (lastpixel.first != -1) {
          DisplayPixelLine(pixel, lastpixel, renderer);
        }
        lastpixel = pixel;
      } else {
        lastpixel.first = -1;
      }
    }
    start.first += step.first;
  }
}

void aequus::video::Plot::DisplayPixelLine(std::pair<int, int> start,
                                           std::pair<int, int> end,
                                           SDL_Renderer *renderer) {
  std::pair<int, int> direction(0, 0);
  double length =
      sqrt(pow(end.first - start.first, 2) + pow(end.second - start.second, 2));
  if (start.first > end.first) {
    direction.first = -1;
  } else if (start.first < end.first) {
    direction.first = 1;
  }
  if (start.second > end.second) {
    direction.second = -1;
  } else if (start.second < end.second) {
    direction.second = 1;
  }
  while (start != end && length < graphheight) {
    double slope = (end.second - start.second);
    if (end.first - start.first != 0) {
      slope /= (double)(end.first - start.first);
    }
    slope = fabs(slope);
    for (int i = 0; i < slope; i++) {
      if (Check(start.first, start.second) == true) {
        SDL_RenderDrawPoint(renderer, start.first, start.second);
      }
      if (start.second != end.second) {
        start.second += direction.second;
      }
    }
    if (slope == 0) {
      if (Check(start.first, start.second) == true) {
        SDL_RenderDrawPoint(renderer, start.first, start.second);
      }
    }
    if (start.first != end.first) {
      start.first += direction.first;
    }
  }
}

void aequus::video::Plot::DisplayScatter(SDL_Renderer *renderer, bool label,
                                         std::string fontname) {
  std::pair<int, int> pix;
  for (int i = 0; i < points.size(); i++) {
    pix = ConvertToPix(points[i]);
    LoadColor(points[i], renderer);
    if (pix.first > domain.pixelstart &&
        pix.first < graphwidth - domain.pixelend &&
        pix.second < graphheight - range.pixelstart &&
        pix.second > range.pixelend) {
      DisplayPoint(pix, renderer);
    }
  }
  if (label == true) {
    DisplayLabel(renderer, fontname);
  }
}

void aequus::video::Plot::DisplayLine(SDL_Renderer *renderer, bool label,
                                      std::string fontname) {
  std::pair<int, int> pix, nextpix, step;
  for (int i = 0; i < points.size() - 1; i++) {
    nextpix = ConvertToPix(points[i + 1]);
    pix = ConvertToPix(points[i]);
    LoadColor(points[i], renderer);
    DisplayPixelLine(pix, nextpix, renderer);
    DisplayPoint(pix, renderer);
  }
  DisplayPoint(ConvertToPix(points[points.size() - 1]), renderer);
  if (label == true) {
    DisplayLabel(renderer, fontname);
  }
}

void aequus::video::Plot::DisplayConstant(SDL_Renderer *renderer, bool label,
                                          std::string fontname) {
  std::pair<double, double> pos, nextpos, gotopos;
  for (int i = 0; i < points.size() - 1; i++) {
    pos = points[i];
    nextpos = points[i + 1];
    LoadColor(points[i], renderer);
    gotopos = pos;
    if (rangebased == false) {
      if (nextpos.first > pos.first) {
        gotopos.first += (nextpos.first - pos.first) / 2.0;
      } else if (nextpos.first < pos.first) {
        gotopos.first -= (nextpos.first - pos.first) / 2.0;
      }
      DisplayDataLine(pos, gotopos, renderer);
      pos = gotopos;
      gotopos.second = nextpos.second;
      DisplayDataLine(pos, gotopos, renderer);
      pos = gotopos;
      DisplayDataLine(pos, nextpos, renderer);
    } else if (rangebased == true) {
      if (nextpos.second > pos.second) {
        gotopos.second += (nextpos.second - pos.second) / 2.0;
      } else if (nextpos.second < pos.second) {
        gotopos.second -= (nextpos.second - pos.second) / 2.0;
      }
      DisplayDataLine(pos, gotopos, renderer);
      pos = gotopos;
      gotopos.first = nextpos.first;
      DisplayDataLine(pos, gotopos, renderer);
      pos = gotopos;
      DisplayDataLine(pos, nextpos, renderer);
    }
    DisplayPoint(ConvertToPix(points[i]), renderer);
  }
  DisplayPoint(ConvertToPix(points[points.size() - 1]), renderer);
  if (label == true) {
    DisplayLabel(renderer, fontname);
  }
}

void aequus::video::Plot::DisplayBar(SDL_Renderer *renderer, bool label,
                                     std::string fontname) {
  std::pair<double, double> pos, nextpos;
  std::pair<int, int> pix, lastpix(-1, -1);
  double step = (datadomain.second - datadomain.first) / graphwidth;
  for (int i = 0; i < points.size(); i++) {
    pos = points[i];
    LoadColor(points[i], renderer);
    if (rangebased == false) {
      pos.first -= step * (barwidth / 2);
      DisplayDataLine(pos,
                      std::make_pair(pos.first + step * barwidth, pos.second),
                      renderer);
      nextpos = std::make_pair(pos.first, rangedomain.first);
      DisplayDataLine(pos, nextpos, renderer);
      pos.first += step * barwidth;
      nextpos = std::make_pair(pos.first, rangedomain.first);
      DisplayDataLine(pos, nextpos, renderer);
    } else if (rangebased == true) {
      pos.second -= step * (barwidth / 2);
      DisplayDataLine(pos,
                      std::make_pair(pos.first, pos.second + step * barwidth),
                      renderer);
      nextpos = std::make_pair(datadomain.first, pos.second);
      DisplayDataLine(pos, nextpos, renderer);
      pos.second += step * barwidth;
      nextpos = std::make_pair(datadomain.first, pos.second);
      DisplayDataLine(pos, nextpos, renderer);
    }
    DisplayPoint(ConvertToPix(points[i]), renderer);
  }
  if (label == true) {
    DisplayLabel(renderer, fontname);
  }
}

void aequus::video::Plot::DisplayComb(SDL_Renderer *renderer, bool label,
                                      std::string fontname) {
  std::pair<double, double> pos, nextpos;
  for (int i = 0; i < points.size(); i++) {
    pos = points[i];
    LoadColor(points[i], renderer);
    if (rangebased == false) {
      nextpos = std::make_pair(pos.first, rangedomain.first);
      DisplayDataLine(pos, nextpos, renderer);
    } else if (rangebased == true) {
      nextpos = std::make_pair(datadomain.first, pos.second);
      DisplayDataLine(pos, nextpos, renderer);
    }
    DisplayPoint(ConvertToPix(points[i]), renderer);
  }
  if (label == true) {
    DisplayLabel(renderer, fontname);
  }
}

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

std::pair<double, double>
aequus::video::Plot::ConvertToVal(std::pair<int, int> pix) {
  std::pair<double, double> pos(0.0, 0.0);

  pos.first = ((double)(pix.first - domain.pixelstart) * domain.valtopixel) +
              domain.min;
  pos.second = ((double)(graphheight - pix.second - range.pixelstart) *
                range.valtopixel) +
               range.min;
  if (polar == true) {
    std::pair<double, double> polarcoord(0.0, 0.0);
    if (pos.first > 0) {
      polarcoord.first = atan(pos.second / pos.first);
    } else if (pos.first < 0 && pos.second >= 0) {
      polarcoord.first = atan(pos.second / pos.first) + 3.14159265359;
    } else if (pos.first < 0 && pos.second < 0) {
      polarcoord.first = atan(pos.second / pos.first) - 3.14159265359;
    } else if (pos.first == 0 && pos.second > 0) {
      polarcoord.first = 1.57079632679;
    } else if (pos.first == 0 && pos.second < 0) {
      polarcoord.first = -1.57079632679;
    } else if (pos.first == 0 && pos.second == 0) {
      polarcoord.first = 0;
    }
    polarcoord.second = sqrt(pow(pos.first, 2) + pow(pos.second, 2));
    pos = polarcoord;
  }
  return (pos);
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

bool aequus::video::Plot::Check(int x, int y) {
  if (x > domain.pixelstart && x < graphwidth - domain.pixelend &&
      y > range.pixelend && y < graphheight - range.pixelstart) {
    return (true);
  }
  return (false);
}

bool aequus::video::Plot::Check(double x, double y) {
  if (x > domain.min && x < domain.max && y > range.min && y < range.max) {
    return (true);
  }
  return (false);
}
