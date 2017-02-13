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

void aequus::video::Graph::SetDomainGrid(int major, int minor) {
  domainmajor = major;
  domainminor = minor;
}

void aequus::video::Graph::SetRangeGrid(int major, int minor) {
  rangemajor = major;
  rangeminor = minor;
}

void aequus::video::Graph::SetDomain(std::pair<double, double> domain) {
  domainmin = domain.first;
  domainmax = domain.second;
}

void aequus::video::Graph::SetRange(std::pair<double, double> range) {
  rangemin = range.first;
  rangemax = range.second;
}

void aequus::video::Graph::SetAxisTitle(
    std::pair<std::string, std::string> titles) {
  if (titles.first != "") {
    domaintitle = titles.first;
  }
  if (titles.second != "") {
    rangetitle = titles.second;
  }
}

void aequus::video::Graph::SetDomain(double min, double max) {
  domainmin = min;
  domainmax = max;
}

void aequus::video::Graph::SetRange(double min, double max) {
  rangemin = min;
  rangemax = max;
}

void aequus::video::Graph::SetAxisTitle(std::string domain, std::string range) {
  if (domain != "") {
    domaintitle = domain;
  }
  if (range != "") {
    rangetitle = range;
  }
}

std::vector<int> aequus::video::Graph::GetColor(std::string name) {
  std::map<std::string, std::vector<int>>::iterator it = colormap.find(name);
  if (it != colormap.end()) {
    return (it->second);
  } else {
    return (std::vector<int>{0, 0, 0, 0});
  }
}

void aequus::video::Graph::AddPlot(Plot newplot) { plots.push_back(newplot); }

// void aequus::video::Graph::Init(int w, int h, SDL_Renderer *renderer) {
//   sdlsurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
//   texturerenderer = SDL_CreateSoftwareRenderer(sdlsurface);
//   SDL_SetRenderDrawBlendMode(texturerenderer, SDL_BLENDMODE_BLEND);
//   InitTexture(sdlsurface, renderer);
//   pessum::logging::LogLoc(pessum::logging::SUCCESS, "Created graph",
//                           logmap["AEQ_VID_OBJ_GRA"], "Init");
//   textfontname = "Roboto";
//   width = w;
//   height = h;
//   domain = std::make_pair(-10, 10);
//   range = std::make_pair(-10, 10);
//   colors["AXIS"] = {255, 255, 255, 255};
//   colors["MAJORGRID"] = {255, 255, 255, 364};
//   colors["MINORGRID"] = {255, 255, 255, 50};
//   colors["BACKGROUND"] = {0, 0, 0, 255};
//   int null = 0;
//   Font font = GetFont(textfontname);
//   double rangeval = range.second;
//   if (std::to_string(range.first).size() >
//       std::to_string(range.second).size()) {
//     rangeval = range.first;
//   }
//   std::string str = ShrinkString(std::to_string(rangeval));
//   font.GetSize(str, domainoffset, null);
//   str = ShrinkString(std::to_string(domain.second));
//   font.GetSize(str, null, rangeoffset);
//   domainmax = rangeoffset / 2;
//   rangemax = domainoffset / 2;
//   DrawAll();
// }
//
//
// void aequus::video::Graph::Update() { UpdateTexture(); }
//
// void aequus::video::Graph::Delete() {
//   for (int i = 0; i < plots.size(); i++) {
//     plots[i].Delete();
//   }
// }
//
// void aequus::video::Graph::Clear() {
//   LoadColor("BACKGROUND");
//   SDL_RenderClear(texturerenderer);
// }
//
// void aequus::video::Graph::DrawAll() {
//   Clear();
//   CalcValToPix();
//   if (drawgrid == true) {
//     DrawGrid();
//   }
//   if (drawaxis == true) {
//     DrawAxis();
//   }
//   if (drawlabel == true) {
//   }
//   if (drawtitle == true) {
//   }
//   UpdateTexture();
// }
//
// void aequus::video::Graph::DrawPlots() {
//   for (int i = 0; i < plots.size(); i++) {
//     plots[i].Display(texturerenderer,
//                      {domain.first, domain.second, dvaltopix,
//                       (double)domainoffset, range.first, range.second,
//                       rvaltopix, (double)rangeoffset, (double)width,
//                       (double)height});
//   }
// }
//
// void aequus::video::Graph::DrawAxis() {
//   LoadColor("AXIS");
//   Font font = GetFont(textfontname);
//   int null;
//   SDL_RenderDrawLine(texturerenderer, domainoffset, height - rangeoffset,
//                      domainoffset, rangemax);
//   SDL_RenderDrawLine(texturerenderer, domainoffset, height - rangeoffset,
//                      width - domainmax, height - rangeoffset);
//   double domainstep = (domain.second - domain.first) / domainmajormarkcount;
//   double rangestep = (range.second - range.first) / rangemajormarkcount;
//   for (double i = domain.first; i <= domain.second; i += domainstep) {
//     int width;
//     std::string str = ShrinkString(std::to_string(i));
//     Text label;
//     label.Init(str, textfontname, texturerenderer);
//     font.GetSize(str, width, null);
//     label.SetPos(((i - domain.first) * dvaltopix) + domainoffset - (width /
//     2),
//                  height - rangeoffset);
//     label.Display();
//   }
//   for (double i = range.first; i <= range.second; i += rangestep) {
//     int txtwidth, txtheight;
//     std::string str = ShrinkString(std::to_string(i));
//     Text label;
//     label.Init(str, textfontname, texturerenderer);
//     font.GetSize(str, txtwidth, txtheight);
//     label.SetPos(domainoffset - txtwidth,
//                  height - (((i - range.first) * rvaltopix) + rangeoffset +
//                            (txtheight / 2)));
//     label.Display();
//   }
// }
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
// void aequus::video::Graph::CalcValToPix() {
//   int graphdomainpix = width - domainoffset - domainmax;
//   int graphrangepix = height - rangeoffset - rangemax;
//   double deltadomain = domain.second - domain.first,
//          deltarange = range.second - range.first;
//   dvaltopix = (double)graphdomainpix / deltadomain;
//   rvaltopix = (double)graphrangepix / deltarange;
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
