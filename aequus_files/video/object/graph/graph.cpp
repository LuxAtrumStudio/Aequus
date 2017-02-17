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
  datadomain = std::make_pair(0.0, 0.0);
  sdlsurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  texturerenderer = SDL_CreateSoftwareRenderer(sdlsurface);
  SDL_SetRenderDrawBlendMode(texturerenderer, SDL_BLENDMODE_BLEND);
  InitTexture(sdlsurface, renderer);
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

void aequus::video::Graph::SetDrawEquation(bool setting) { dispeqs = setting; }

void aequus::video::Graph::ToggleDrawAxis() { dispaxis = !dispaxis; }

void aequus::video::Graph::ToggleDrawGrid() { dispgrid = !dispgrid; }

void aequus::video::Graph::ToggleDrawLabel() { displabel = !displabel; }

void aequus::video::Graph::ToggleDrawTitle() { disptitle = !disptitle; }

void aequus::video::Graph::ToggleDrawEquation() { dispeqs = !dispeqs; }

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
  if (dim == 0) {
    domain.majormarks = major - 1;
    domain.minormarks = minor;
  } else if (dim == 1) {
    range.majormarks = major - 1;
    range.minormarks = minor;
  }
}

void aequus::video::Graph::SetRange(int dim, double min, double max) {
  if (dim == 0) {
    domain.min = min;
    domain.max = max;
  } else if (dim == 1) {
    range.min = min;
    range.max = max;
  } else if (dim == -1) {
    datadomain.first = min;
    datadomain.second = max;
  }
}

void aequus::video::Graph::SetAxisTitle(int dim, std::string title) {
  if (dim == 0) {
    domain.title = title;
  } else if (dim == 1) {
    range.title = title;
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

void aequus::video::Graph::AddPlot(Plot newplot) {
  int index = plots.size();
  plots.push_back(newplot);
  plots[index].SetGraphData(graphwidth, graphheight, domain, range, datadomain);
  plots[index].GenorateData();
  plots[index].Display(texturerenderer, dispeqs, fontname);
  UpdateTexture();
}

void aequus::video::Graph::Update() {
  CalculatePix();
  for (int i = 0; i < plots.size(); i++) {
    plots[i].SetGraphData(graphwidth, graphheight, domain, range, datadomain);
    plots[i].GenorateData();
  }
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
  DisplayPlots();
  UpdateTexture();
}

void aequus::video::Graph::ClearGraph() {
  LoadColor("BACKGROUND");
  SDL_RenderClear(texturerenderer);
}

void aequus::video::Graph::DisplayPlots() {
  for (int i = 0; i < plots.size(); i++) {
    plots[i].Display(texturerenderer, dispeqs, fontname);
  }
}

void aequus::video::Graph::DisplayAxis() {
  LoadColor("AXIS");
  Font font = GetFont(fontname);
  Text label;
  label.Init("A", fontname, texturerenderer);
  std::pair<int, int> point, endpoint;
  std::vector<double> pos = {domain.min, range.min}, endpos;
  point = ConvertToPix(pos);
  endpos = pos;
  endpos[0] = domain.max;
  endpoint = ConvertToPix(endpos);
  SDL_RenderDrawLine(texturerenderer, point.first, point.second, endpoint.first,
                     endpoint.second);
  double step = (domain.max - domain.min) / (double)(domain.majormarks + 1);
  for (double j = domain.min; j <= domain.max + (domain.max * 0.00001);
       j += step) {
    int width, height;
    std::string str = ShortenDouble(j);
    if (str != "") {
      label.UpdateString(str);
      font.GetSize(str, width, height);
      endpos[0] = j;
      endpoint = ConvertToPix(endpos);
      if (j < domain.max && j != domain.min) {
        endpoint.first -= (width / 2);
      } else if (j >= domain.max) {
        endpoint.first -= width;
      }
      label.SetPos(endpoint.first, endpoint.second);
      label.Display();
    }
  }

  endpos = pos;
  endpos[1] = range.max;
  endpoint = ConvertToPix(endpos);
  SDL_RenderDrawLine(texturerenderer, point.first, point.second, endpoint.first,
                     endpoint.second);
  step = (range.max - range.min) / (double)(range.majormarks + 1);
  for (double j = range.min; j <= range.max + (range.max * 0.00001);
       j += step) {
    int width, height;
    std::string str = ShortenDouble(j);
    if (str != "") {
      label.UpdateString(str);
      font.GetSize(str, width, height);
      endpos[1] = j;
      endpoint = ConvertToPix(endpos);
      endpoint.first -= width;
      if (j < range.max && j != range.min) {
        endpoint.second -= (height / 2);
      } else if (j == range.min) {
        endpoint.second -= height;
      }
      label.SetPos(endpoint.first, endpoint.second);
      label.Display();
    }
  }

  label.Delete();
}

void aequus::video::Graph::DisplayGrid() {
  std::pair<int, int> start(0, 0), end(0, 0);
  double majorstep =
      (domain.max - domain.min) / (double)(domain.majormarks + 1);
  double minorstep = majorstep / (double)(domain.minormarks + 1);
  std::vector<double> startpos = {domain.min, range.min},
                      endpos = {domain.min, range.max};
  for (double j = domain.min; j <= domain.max + (domain.max * 0.00001);
       j += minorstep) {
    if (remainder(j, majorstep) >= -majorstep * 0.00001 &&
        remainder(j, majorstep) <= majorstep * 0.00001) {
      LoadColor("MAJORGRID");
    } else {
      LoadColor("MINORGRID");
    }
    startpos[0] = j;
    endpos[0] = j;
    start = ConvertToPix(startpos);
    end = ConvertToPix(endpos);
    SDL_RenderDrawLine(texturerenderer, start.first, start.second, end.first,
                       end.second);
  }
  majorstep = (range.max - range.min) / (double)(range.majormarks + 1);
  minorstep = majorstep / (double)(range.minormarks + 1);
  startpos = {domain.min, range.min};
  endpos = {domain.max, range.min};
  for (double j = range.min; j <= range.max + (range.max * 0.00001);
       j += minorstep) {
    if (remainder(j, majorstep) >= -majorstep * 0.00001 &&
        remainder(j, majorstep) <= majorstep * 0.00001) {
      LoadColor("MAJORGRID");
    } else {
      LoadColor("MINORGRID");
    }
    startpos[1] = j;
    endpos[1] = j;
    start = ConvertToPix(startpos);
    end = ConvertToPix(endpos);
    SDL_RenderDrawLine(texturerenderer, start.first, start.second, end.first,
                       end.second);
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
  int width = 0, height = 0;
  if (domain.title != "") {
    font.GetSize(domain.title, width, height);
    label.Init(domain.title, loadedfont, texturerenderer);
    label.SetPos((graphwidth - width) / 2, graphheight - height);
    label.Display();
  }
  if (range.title != "") {
    font.GetSize(range.title, width, height);
    label.UpdateString(range.title);
    label.SetPos(-(width / 3), (graphheight - height) / 2);
    label.SetRotatePoint(0.5, 0.5);
    label.Rotate(-90);
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
  if (fontname != "" && dispaxis == true) {
    font = GetFont(fontname);
    double rangeval = range.max;
    if (std::to_string(range.min).size() > std::to_string(range.max).size()) {
      rangeval = range.min;
    }
    std::string str = ShortenDouble(rangeval);
    font.GetSize(str, domain.pixelstart, null);
    str = ShortenDouble(domain.max);
    font.GetSize(str, null, textheight);
    range.pixelstart = textheight;
    domain.pixelend = 2;
    range.pixelend = 2;
  } else {
    domain.pixelstart = 2;
    range.pixelstart = 2;
    domain.pixelend = 2;
    domain.pixelend = 2;
  }
  if (displabel == true) {
    std::string loadedfont = fontname;
    if (labelfont != "") {
      loadedfont = labelfont;
    }
    font = GetFont(loadedfont);
    font.GetSize("A", null, textheight);
    domain.pixelstart += textheight * 2;
    range.pixelstart += textheight;
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
    range.pixelend += textheight;
  }
  domain.valtopixel =
      (double)(graphwidth - domain.pixelstart - domain.pixelend) /
      (double)(domain.max - domain.min);
  range.valtopixel = (double)(graphwidth - range.pixelstart - range.pixelend) /
                     (double)(range.max - range.min);
  if (datadomain.first == datadomain.second) {
    datadomain.first = domain.min;
    datadomain.second = domain.max;
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
  if (vals.size() != 2) {
    return (pixel);
  }
  pixel.first = (vals[0] - domain.min) * domain.valtopixel;
  pixel.second = (vals[1] - range.min) * range.valtopixel;
  pixel.first += domain.pixelstart;
  pixel.second = graphheight - (pixel.second + range.pixelstart);
  return (pixel);
}
