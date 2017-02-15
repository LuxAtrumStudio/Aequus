#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../../video.hpp"
#include "../object_headers.hpp"
#include "graph.hpp"
#include <iostream>
#include <map>
#include <pessum.h>
#include <stdarg.h>
#include <string>

void aequus::video::Graph::Init(int width, int height, SDL_Renderer *renderer) {
  sdlsurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  texturerenderer = SDL_CreateSoftwareRenderer(sdlsurface);
  SDL_SetRenderDrawBlendMode(texturerenderer, SDL_BLENDMODE_BLEND);
  InitTexture(sdlsurface, renderer);
  Dimension newdim;
  dimensions.push_back(newdim);
  dimensions.push_back(newdim);
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Created graph",
                          logmap["AEQ_VID_OBJ_GRA"], "Init");
  graphwidth = width;
  graphheight = height;
  colormap["AXIS"] = {255, 255, 255, 255};
  colormap["MAJORGRID"] = {255, 255, 255, 364};
  colormap["MINORGRID"] = {255, 255, 255, 50};
  colormap["BACKGROUND"] = {0, 0, 0, 255};
  CalculatePix();
  DisplayGraph();
}

void aequus::video::Graph::Init(int width, int height, bool axis, bool grid,
                                bool label, bool title,
                                SDL_Renderer *renderer) {}

void aequus::video::Graph::SetDrawAxis(bool setting) { dispaxis = setting; }

void aequus::video::Graph::SetDrawGrid(bool setting) { dispgrid = setting; }

void aequus::video::Graph::SetDrawLabel(bool setting) { displabel = setting; }

void aequus::video::Graph::SetDrawTitle(bool setting) { disptitle = setting; }

void aequus::video::Graph::ToggleDrawAxis() { dispaxis = !dispaxis; }

void aequus::video::Graph::ToggleDrawGrid() { dispgrid = !dispgrid; }

void aequus::video::Graph::ToggleDrawLabel() { displabel = !displabel; }

void aequus::video::Graph::ToggleDrawTitle() { disptitle = !disptitle; }

void aequus::video::Graph::SetColor(std::string name, std::vector<int> color) {
  colormap[name] = color;
}

void aequus::video::Graph::SetColor(std::string name,
                                    std::vector<double> color) {
  colormap[name] =
      std::vector<int>{(int)(255 * color[0]), (int)(255 * color[1]),
                       (int)(255 * color[2]), (int)(255 * color[3])};
}

void aequus::video::Graph::SetColor(std::string name, int red, int green,
                                    int blue, int alpha) {
  colormap[name] = std::vector<int>{red, green, blue, alpha};
}

void aequus::video::Graph::SetColor(std::string name, double red, double green,
                                    double blue, double alpha) {
  colormap[name] = std::vector<int>{(int)(255 * red), (int)(255 * green),
                                    (int)(255 * blue), (int)(255 * alpha)};
}

void aequus::video::Graph::SetGrid(int dim, int major, int minor) {
  if (dim >= 0 && dim < dimensions.size()) {
    dimensions[dim].majormarks = major;
    dimensions[dim].minormarks = minor;
  }
}

void aequus::video::Graph::SetRange(int dim, double min, double max) {
  if (dim >= 0 && dim < dimensions.size()) {
    dimensions[dim].min = min;
    dimensions[dim].max = max;
  }
}

void aequus::video::Graph::SetAxisTitle(int dim, std::string title) {
  if (dim >= 0 && dim < dimensions.size()) {
    dimensions[dim].title = title;
  }
}

void aequus::video::Graph::SetGraphTitle(std::string title) {
  graphtitle = title;
}

void aequus::video::Graph::SetFont(std::string name) { fontname = name; }

void aequus::video::Graph::SetTitleFont(std::string name) { titlefont = name; }

void aequus::video::Graph::SetLabelFont(std::string name) { labelfont = name; }

std::vector<int> aequus::video::Graph::GetColor(std::string name) {
  std::map<std::string, std::vector<int>>::iterator it = colormap.find(name);
  if (it != colormap.end()) {
    return (it->second);
  } else {
    return (std::vector<int>{0, 0, 0, 0});
  }
}

void aequus::video::Graph::AddPlot(Plot newplot) { plots.push_back(newplot); }

void aequus::video::Graph::Update() {
  CalculatePix();
  DisplayGraph();
}

void aequus::video::Graph::Delete() {}

void aequus::video::Graph::DisplayGraph() {
  ClearGraph();
  if (dispgrid == true) {
    DisplayGrid();
  }
  if (dispaxis == true) {
    DisplayAxis();
  }
  if (displabel == true) {
    DisplayLabel();
  }
  if (disptitle == true) {
    DisplayTitle();
  }
  UpdateTexture();
}

void aequus::video::Graph::ClearGraph() {
  LoadColor("BACKGROUND");
  SDL_RenderClear(texturerenderer);
}

void aequus::video::Graph::DisplayPlots() {
  for (int i = 0; i < plots.size(); i++) {
    // plots[i].Display();
  }
}

void aequus::video::Graph::DisplayAxis() {
  LoadColor("AXIS");
  Font font = GetFont(fontname);
  Text label;
  label.Init("", fontname, texturerenderer);
  std::pair<int, int> point, endpoint;
  std::vector<double> pos, endpos;
  for (int i = 0; i < dimensions.size(); i++) {
    pos.push_back(dimensions[i].min);
  }
  point = ConvertToPix(pos);
  for (int i = 0; i < dimensions.size(); i++) {
    endpos = pos;
    endpos[i] = dimensions[i].max;
    endpoint = ConvertToPix(endpos);
    SDL_RenderDrawLine(texturerenderer, point.first, point.second,
                       endpoint.first, endpoint.second);
    double step = (dimensions[i].max - dimensions[i].min) /
                  (double)(dimensions[i].majormarks + 1);
    for (double j = dimensions[i].min; j <= dimensions[i].max; j += step) {
      int width, height;
      std::string str = ShortenDouble(j);
      label.UpdateString(str);
      font.GetSize(str, width, height);
      endpos[i] = j;
      endpoint = ConvertToPix(endpos);
      endpoint.first -= width;
      label.SetPos(endpoint.first, endpoint.second);
      label.Display();
    }
  }
  label.Delete();
}

void aequus::video::Graph::DisplayGrid() {
  std::pair<int, int> start(0, 0), end(0, 0);
  for (int i = 0; i < dimensions.size(); i++) {
    double majorstep = (dimensions[i].max - dimensions[i].min) /
                       (double)(dimensions[i].majormarks + 1);
    double minorstep = majorstep / (double)(dimensions[i].minormarks + 1);
    for (double j = dimensions[i].min; j <= dimensions[i].max; j += minorstep) {
      if (remainder(j, majorstep) == 0) {
        LoadColor("MAJORGRID");
      } else {
        LoadColor("MINORGRID");
      }
      for (int k = 0; k < dimensions.size(); k++) {
        if (k != i) {
          std::vector<double> startpos(dimensions.size(), 0),
              endpos(dimensions.size(), 0);
          startpos[i] = j;
          endpos[i] = j;
          startpos[k] = dimensions[k].min;
          endpos[k] = dimensions[k].max;
          start = ConvertToPix(startpos);
          end = ConvertToPix(endpos);
          SDL_RenderDrawLine(texturerenderer, start.first, start.second,
                             end.first, end.second);
        }
      }
    }
  }
}

void aequus::video::Graph::DisplayLabel() {
  Text label;
  std::string loadedfont;
  if (labelfont != "") {
    loadedfont = labelfont;
  } else {
    loadedfont = fontname;
  }
  Font font = GetFont(loadedfont);
  label.Init("", loadedfont, texturerenderer);
  int width = 0, height = 0;
  if (dimensions.size() == 2 && coordinatization == CARTESIAN) {
    font.GetSize(dimensions[0].title, width, height);
    label.UpdateString(dimensions[0].title);
    label.SetPos((graphwidth - width) / 2, graphheight - height);
    label.Display();
    font.GetSize(dimensions[1].title, width, height);
    label.UpdateString(dimensions[1].title);
    label.SetPos((-2.0 / 3.0) * height, (graphheight - width) / 2);
    label.SetRotatePoint(0.5, 0.5);
    label.Rotate(90);
    label.Display();
  }
  label.Delete();
}

void aequus::video::Graph::DisplayTitle() {
  Text title;
  std::string loadedfont;
  if (titlefont != "") {
    loadedfont = titlefont;
  } else if (labelfont != "") {
    loadedfont = labelfont;
  } else {
    loadedfont = fontname;
  }
  title.Init(graphtitle, loadedfont, texturerenderer);
  title.Display();
  title.Delete();
}

void aequus::video::Graph::CalculatePix() {
  int textheight = 0, null = 0;
  Font font;
  if (dimensions.size() == 2) {
    if (fontname != "") {
      font = GetFont(fontname);
      double rangeval = dimensions[1].max;
      if (std::to_string(dimensions[1].min).size() >
          std::to_string(dimensions[1].max).size()) {
        rangeval = dimensions[1].min;
      }
      std::string str = ShortenDouble(rangeval);
      font.GetSize(str, dimensions[0].pixelstart, null);
      str = ShortenDouble(dimensions[0].max);
      font.GetSize(str, null, textheight);
      dimensions[1].pixelstart = textheight;
      dimensions[0].pixelend = 2;
      dimensions[1].pixelend = 2;
    }
    if (displabel == true) {
      std::string loadedfont = fontname;
      if (labelfont != "") {
        loadedfont = labelfont;
      }
      font = GetFont(loadedfont);
      font.GetSize("A", null, textheight);
      dimensions[0].pixelstart += textheight;
      dimensions[1].pixelstart += textheight;
    }
    if (disptitle == true) {
      std::string loadedfont = fontname;
      if (titlefont != "") {
        loadedfont = titlefont;
      } else if (labelfont != "") {
        loadedfont = labelfont;
      }
      font = GetFont(loadedfont);
      font.GetSize("A", null, textheight);
      dimensions[1].pixelend += textheight;
    }
    dimensions[0].valtopixel = (double)(graphwidth - dimensions[0].pixelstart -
                                        dimensions[0].pixelend) /
                               (double)(dimensions[0].max - dimensions[0].min);
    dimensions[1].valtopixel = (double)(graphwidth - dimensions[1].pixelstart -
                                        dimensions[1].pixelend) /
                               (double)(dimensions[1].max - dimensions[1].min);
  }
}

void aequus::video::Graph::LoadColor(std::string color) {
  std::map<std::string, std::vector<int>>::iterator it;
  it = colormap.find(color);
  if (it != colormap.end()) {
    SDL_SetRenderDrawColor(texturerenderer, it->second[0], it->second[1],
                           it->second[2], it->second[3]);
  } else {
    SDL_SetRenderDrawColor(texturerenderer, 255, 255, 255, 0);
  }
}

std::string aequus::video::Graph::ShortenDouble(double val) {
  std::string str = std::to_string(val);
  for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.'); j--) {
    if (str[j] == '.') {
      j = 0;
    }
    str.pop_back();
  }
  return (str);
}

std::pair<int, int>
aequus::video::Graph::ConvertToPix(std::vector<double> vals) {
  std::pair<int, int> pixel(0, 0);
  if (dimensions.size() != vals.size()) {
    return (pixel);
  }
  if (coordinatization == CARTESIAN) {
    if (dimensions.size() == 2) {
      pixel.first = (vals[0] - dimensions[0].min) * dimensions[0].valtopixel;
      pixel.second = (vals[1] - dimensions[1].min) * dimensions[1].valtopixel;
    }
    pixel.first += dimensions[0].pixelstart;
    pixel.second = graphheight - (pixel.second + dimensions[1].pixelstart);
  }
  return (pixel);
}
//
//
// void aequus::video::Graph::DrawGrid() {
//   double domainstep = (domain.second - domain.first) / domainmajormarkcount;
//   double rangestep = (range.second - range.first) / rangemajormarkcount;
//   for (double i = domain.first; i <= domain.second; i += domainstep) {
//     LoadColor("MAJORGRID");
//     SDL_RenderDrawLine(
//         texturerenderer, ((i - domain.first) * dvaltopix) + domainoffset,
//         height - rangeoffset, ((i - domain.first) * dvaltopix) +
//         domainoffset,
//         rangemax);
//     if (domainminormarkcount != 0) {
//       LoadColor("MINORGRID");
//       double minstep = domainstep / (double)(domainminormarkcount + 1);
//       for (double j = i; j < i + domainstep && j < domain.second;
//            j += minstep) {
//         SDL_RenderDrawLine(
//             texturerenderer, ((j - domain.first) * dvaltopix) + domainoffset,
//             height - rangeoffset,
//             ((j - domain.first) * dvaltopix) + domainoffset, rangemax);
//       }
//     }
//   }
//   for (double i = range.first; i <= range.second; i += rangestep) {
//     LoadColor("MAJORGRID");
//     SDL_RenderDrawLine(texturerenderer, domainoffset,
//                        height - (((i - range.first) * rvaltopix) +
//                        rangeoffset),
//                        width - domainmax,
//                        height -
//                            (((i - range.first) * rvaltopix) + rangeoffset));
//     if (rangeminormarkcount != 0) {
//       LoadColor("MINORGRID");
//       double minstep = rangestep / (double)(rangeminormarkcount + 1);
//       for (double j = i; j < i + rangestep && j < range.second; j += minstep)
//       {
//         SDL_RenderDrawLine(
//             texturerenderer, domainoffset,
//             height - (((j - range.first) * rvaltopix) + rangeoffset),
//             width - domainmax,
//             height - (((j - range.first) * rvaltopix) + rangeoffset));
//       }
//     }
//   }
// }
//
// void aequus::video::Graph::LoadColor(std::string comp) {
//   std::map<std::string, std::vector<int>>::iterator color;
//   color = colors.find(comp);
//   if (color != colors.end()) {
//     SDL_SetRenderDrawColor(texturerenderer, color->second[0],
//     color->second[1],
//                            color->second[2], color->second[3]);
//   } else {
//     SDL_SetRenderDrawColor(texturerenderer, 255, 255, 255, 0);
//   }
// }
//
// int aequus::video::Graph::ConvertToPix(double val, bool isrange) {
//   if (isrange == false) {
//     return (((val - domain.first) * dvaltopix) + domainoffset);
//   } else if (isrange == true) {
//     return (height - (((val - range.first) * rvaltopix) + rangeoffset));
//   }
//   return (0);
// }
//
// std::string aequus::video::Graph::ShrinkString(std::string str) {
//   for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.');
//   j--) {
//     if (str[j] == '.') {
//       j = 0;
//     }
//     str.pop_back();
//   }
//   return (str);
// }
