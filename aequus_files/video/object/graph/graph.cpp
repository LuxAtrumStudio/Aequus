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

void aequus::video::Graph::Init(int w, int h, SDL_Renderer *renderer) {
  sdlsurface = SDL_CreateRGBSurface(0, w, h, 32, 0, 0, 0, 0);
  texturerenderer = SDL_CreateSoftwareRenderer(sdlsurface);
  SDL_SetRenderDrawBlendMode(texturerenderer, SDL_BLENDMODE_BLEND);
  InitTexture(sdlsurface, renderer);
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Created graph",
                          logmap["AEQ_VID_OBJ_GRA"], "Init");
  textfontname = "Roboto";
  width = w;
  height = h;
  domain = std::make_pair(-10, 10);
  range = std::make_pair(-10, 10);
  // domain = std::make_pair(0, 10);
  // range = std::make_pair(0, 10);
  colors["AXIS"] = {255, 255, 255, 255};
  colors["MAJORGRID"] = {255, 255, 255, 364};
  colors["MINORGRID"] = {255, 255, 255, 50};
  int null = 0;
  Font font = GetFont(textfontname);
  double rangeval = range.second;
  if (std::to_string(range.first).size() >
      std::to_string(range.second).size()) {
    rangeval = range.first;
  }
  std::string str = std::to_string(rangeval);
  for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.'); j--) {
    if (str[j] == '.') {
      j = 0;
    }
    str.pop_back();
  }
  font.GetSize(str, domainoffset, null);
  str = std::to_string(domain.second);
  for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.'); j--) {
    if (str[j] == '.') {
      j = 0;
    }
    str.pop_back();
  }
  font.GetSize(str, null, rangeoffset);
  domainmax = rangeoffset / 2;
  rangemax = domainoffset / 2;
  CalcValToPix();
  DrawGrid();
  DrawAxis();
  UpdateTexture();
}

void aequus::video::Graph::LoadColorMap(std::string file) {
  pessum::luxreader::DataFile lux = pessum::luxreader::LoadLuxDataFile(file);
  int indexcount = lux.datafilevariables[0].intvalue;
  for (int i = 1; i < indexcount + 1 && i < lux.datafilevariables.size(); i++) {
    colormap.push_back(lux.datafilevariables[i].intvectorvalues);
  }
}

void aequus::video::Graph::AddColorSetting(std::vector<int> color) {
  colormap.push_back(color);
}

void aequus::video::Graph::AddPlot(Plot *newplot) { plots.push_back(newplot); }

void aequus::video::Graph::AddPlot(std::string ploteq) {
  Plot *newplot = new Plot;
  newplot->Init(ploteq);
  double step =
      (domain.second - domain.first) / (width - domainoffset - domainmax);
  newplot->GenPlot(domain.first, domain.second, step);
  newplot->SetColorMap({{255, 0, 0, 255}, {0, 255, 0, 255}, {0, 0, 255, 255}},
                       true);
  plots.push_back(newplot);
  DrawPlots();
  Update();
}

void aequus::video::Graph::Update() { UpdateTexture(); }

void aequus::video::Graph::Delete() {
  for (int i = 0; i < plots.size(); i++) {
    plots[i]->Delete();
  }
}

void aequus::video::Graph::Clear() {}

void aequus::video::Graph::DrawPlots() {
  for (int i = 0; i < plots.size(); i++) {
    plots[i]->Display(texturerenderer,
                      {domain.first, domain.second, dvaltopix,
                       (double)domainoffset, range.first, range.second,
                       rvaltopix, (double)rangeoffset, (double)width,
                       (double)height});
    // std::vector<std::pair<double, double>> points = plots[i]->GetPoints();
    // for (int i = 0; i < points.size(); i++) {
    //  if (points[i].second > range.first && points[i].second < range.second) {
    //    SDL_RenderDrawPoint(texturerenderer, ConvertToPix(points[i].first),
    //                        ConvertToPix(points[i].second, true));
    //  }
    //}
  }
}

void aequus::video::Graph::DrawAxis() {
  LoadColor("AXIS");
  Font font = GetFont(textfontname);
  int null;
  SDL_RenderDrawLine(texturerenderer, domainoffset, height - rangeoffset,
                     domainoffset, rangemax);
  SDL_RenderDrawLine(texturerenderer, domainoffset, height - rangeoffset,
                     width - domainmax, height - rangeoffset);
  double domainstep = (domain.second - domain.first) / domainmajormarkecount;
  double rangestep = (range.second - range.first) / rangemajormarkcount;
  for (double i = domain.first; i <= domain.second; i += domainstep) {
    int width;
    std::string str = std::to_string(i);
    for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.');
         j--) {
      if (str[j] == '.') {
        j = 0;
      }
      str.pop_back();
    }
    Text label;
    label.Init(str, textfontname, texturerenderer);
    font.GetSize(str, width, null);
    label.SetPos(((i - domain.first) * dvaltopix) + domainoffset - (width / 2),
                 height - rangeoffset);
    label.Display();
  }
  for (double i = range.first; i <= range.second; i += rangestep) {
    int txtwidth, txtheight;
    std::string str = std::to_string(i);
    for (int j = str.size() - 1; j > 0 && (str[j] == '0' || str[j] == '.');
         j--) {
      if (str[j] == '.') {
        j = 0;
      }
      str.pop_back();
    }
    Text label;
    label.Init(str, textfontname, texturerenderer);
    font.GetSize(str, txtwidth, txtheight);
    label.SetPos(domainoffset - txtwidth,
                 height - (((i - range.first) * rvaltopix) + rangeoffset +
                           (txtheight / 2)));
    label.Display();
  }
}

void aequus::video::Graph::DrawGrid() {
  double domainstep = (domain.second - domain.first) / domainmajormarkecount;
  double rangestep = (range.second - range.first) / rangemajormarkcount;
  for (double i = domain.first; i <= domain.second; i += domainstep) {
    LoadColor("MAJORGRID");
    SDL_RenderDrawLine(
        texturerenderer, ((i - domain.first) * dvaltopix) + domainoffset,
        height - rangeoffset, ((i - domain.first) * dvaltopix) + domainoffset,
        rangemax);
    if (domainminormarkcount != 0) {
      LoadColor("MINORGRID");
      double minstep = domainstep / (double)(domainminormarkcount + 1);
      for (double j = i; j < i + domainstep && j < domain.second;
           j += minstep) {
        SDL_RenderDrawLine(
            texturerenderer, ((j - domain.first) * dvaltopix) + domainoffset,
            height - rangeoffset,
            ((j - domain.first) * dvaltopix) + domainoffset, rangemax);
      }
    }
  }
  for (double i = range.first; i <= range.second; i += rangestep) {
    LoadColor("MAJORGRID");
    SDL_RenderDrawLine(texturerenderer, domainoffset,
                       height - (((i - range.first) * rvaltopix) + rangeoffset),
                       width - domainmax,
                       height -
                           (((i - range.first) * rvaltopix) + rangeoffset));
    if (rangeminormarkcount != 0) {
      LoadColor("MINORGRID");
      double minstep = rangestep / (double)(rangeminormarkcount + 1);
      for (double j = i; j < i + rangestep && j < range.second; j += minstep) {
        SDL_RenderDrawLine(
            texturerenderer, domainoffset,
            height - (((j - range.first) * rvaltopix) + rangeoffset),
            width - domainmax,
            height - (((j - range.first) * rvaltopix) + rangeoffset));
      }
    }
  }
}

void aequus::video::Graph::CalcValToPix() {
  int graphdomainpix = width - domainoffset - domainmax;
  int graphrangepix = height - rangeoffset - rangemax;
  double deltadomain = domain.second - domain.first,
         deltarange = range.second - range.first;
  dvaltopix = (double)graphdomainpix / deltadomain;
  rvaltopix = (double)graphrangepix / deltarange;
}

void aequus::video::Graph::LoadColor(std::string comp) {
  std::map<std::string, std::vector<int>>::iterator color;
  color = colors.find(comp);
  if (color != colors.end()) {
    SDL_SetRenderDrawColor(texturerenderer, color->second[0], color->second[1],
                           color->second[2], color->second[3]);
  } else {
    SDL_SetRenderDrawColor(texturerenderer, 255, 255, 255, 0);
  }
}

int aequus::video::Graph::ConvertToPix(double val, bool isrange) {
  if (isrange == false) {
    return (((val - domain.first) * dvaltopix) + domainoffset);
  } else if (isrange == true) {
    return (height - (((val - range.first) * rvaltopix) + rangeoffset));
  }
  return (0);
}
