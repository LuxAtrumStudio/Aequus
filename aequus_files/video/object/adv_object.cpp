#include "../../../pessum_files/pessum_headers.h"
#include "../../aequus_headers.h"
#include "../../sdl_headers.h"
#include "adv_object.h"
#include <iostream>
#include <string>
#include <vector>

void aequus::video::AdvObject::InitializeAdvObj(Renderer renderer, int counter,
                                                std::string resource) {
  logloc = pessum::logging::AddLogLocation(
      "aequus_files/video/object/adv_object.cpp[" + std::to_string(counter) +
      "]/");
  resourcedir = resource;
  objrenderer = renderer;
  advobjcount = counter;
}

void aequus::video::AdvObject::CreateGraph(
    std::string datafile, GraphType graphtype, int graphwidth, int graphheight,
    bool graphbackground, bool graphaxis, bool graphgrid, bool graphvalues,
    bool graphlabels, bool graphtitle, bool graphimagetitle, double xstart,
    double xend, double ystart, double yend) {
  objtype = GRAPH;
  axis = graphaxis;
  values = graphvalues;
  labels = graphlabels;
  title = graphtitle;
  grid = graphgrid;
  imagetitle = graphimagetitle;
  background = graphbackground;
  if (graphtype == LINE) {
    LoadGraphData(datafile);
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS,
                            "Loaded graph data from luxfile", logloc,
                            "CreateGraph");
  }
  if (graphtype == PLOT) {
    minx = xstart;
    maxx = xend;
    ComputeDataPoints(datafile);
  }
  globalobj.InitalizeObj(objrenderer.sdlrenderer, (advobjcount * 10) + 1,
                         resourcedir);
  globalobj.objtexture.SetRenderer(objrenderer.sdlrenderer);
  globalobj.objtexture.sdltexture =
      SDL_CreateTexture(objrenderer.sdlrenderer, SDL_PIXELFORMAT_RGBA8888,
                        SDL_TEXTUREACCESS_TARGET, graphwidth, graphheight);
  if (globalobj.objtexture.sdltexture == NULL) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to create texture", logloc, "CreateGraph");
    framework::GetError();
  }
  globalobj.LoadDefaults(graphwidth, graphheight);
  posx = 0;
  posy = 0;
  width = graphwidth;
  height = graphheight;
  if (graphtype == LINE || graphtype == PLOT) {
    DrawLineGraph();
  }
}

void aequus::video::AdvObject::Display() { globalobj.DisplayObj(); }

void aequus::video::AdvObject::LoadGraphData(std::string datafile) {
  int pointerx, pointery;
  bool typedoublex, typedoubley, colordef = false;
  pessum::luxreader::DataFile data =
      pessum::luxreader::LoadLuxDataFile(datafile);
  int dimensions = 2;
  dimensions = data.datafilevariables[0].intvalue;
  for (unsigned a = 1; a < data.datafilevariables.size(); a++) {
    if (data.datafilevariables[a].variablename == "titles") {
      for (unsigned b = 0;
           b < data.datafilevariables[a].stringvectorvalues.size(); b++) {
        titles.push_back(data.datafilevariables[a].stringvectorvalues[b]);
      }
    }
    for (unsigned b = 1; b < titles.size(); b++) {
      if (data.datafilevariables[a].variablename == titles[b]) {
        GraphData newgraph;
        newgraph.title = titles[b];
        if (data.datafilevariables[a].variabledefinitiontype == "int") {
          unsigned c = 0;
          while (c < data.datafilevariables[a].intvectorvalues.size()) {
            ValueGroup newvalue;
            if (dimensions >= 1) {
              newvalue.x = data.datafilevariables[a].intvectorvalues[c];
              c++;
            }
            if (dimensions >= 2) {
              newvalue.y = data.datafilevariables[a].intvectorvalues[c];
              c++;
            }
            if (dimensions >= 3) {
              newvalue.z = data.datafilevariables[a].intvectorvalues[c];
              c++;
            }
            newgraph.points.push_back(newvalue);
          }
        } else if (data.datafilevariables[a].variabledefinitiontype ==
                   "double") {
          unsigned c = 0;
          while (c < data.datafilevariables[a].doublevectorvalues.size()) {
            ValueGroup newvalue;
            if (dimensions >= 1) {
              newvalue.x = data.datafilevariables[a].doublevectorvalues[c];
              c++;
            }
            if (dimensions >= 2) {
              newvalue.y = data.datafilevariables[a].doublevectorvalues[c];
              c++;
            }
            if (dimensions >= 3) {
              newvalue.z = data.datafilevariables[a].doublevectorvalues[c];
              c++;
            }
            newgraph.points.push_back(newvalue);
          }
        }
        graphs.push_back(newgraph);
      }
    }
    if (data.datafilevariables[a].variablename == "colors") {
      colordef = true;
      for (unsigned b = 0;
           b < data.datafilevariables[a].doublevectorvalues.size(); b += 4) {
        ValueGroup newvalue;
        newvalue.r = data.datafilevariables[a].doublevectorvalues[b];
        newvalue.g = data.datafilevariables[a].doublevectorvalues[b + 1];
        newvalue.b = data.datafilevariables[a].doublevectorvalues[b + 2];
        newvalue.a = data.datafilevariables[a].doublevectorvalues[b + 3];
        colors.push_back(newvalue);
      }
    }
  }
  if (colordef == false) {
    GenColors(graphs.size());
  }
}

void aequus::video::AdvObject::ComputeDataPoints(std::string function) {
  std::vector<std::string> functions;
  std::string newfunction = "";
  for (unsigned a = 0; a < function.size(); a++) {
    if (function[a] != ',') {
      newfunction = newfunction + function[a];
    } else if (function[a] == ',') {
      functions.push_back(newfunction);
      newfunction = "";
    }
  }
  functions.push_back(newfunction);
  stepx = width / (maxx - minx);
  GenColors(functions.size());
  for (unsigned a = 0; a < functions.size(); a++) {
    GraphData newgraph;
    newgraph.title = functions[a];
    int equation = pessum::parser::ParseEquation(functions[a]);
    for (double x = minx; x < maxx; x = x + (maxx - minx) / width) {
      ValueGroup newpoint;
      newpoint.x = x;
      newpoint.y = pessum::parser::ComputeEquation(equation, x);
      newgraph.points.push_back(newpoint);
    }
    graphs.push_back(newgraph);
  }
  for (unsigned a = 0; a < graphs.size(); a++) {
    for (unsigned b = 0; b < graphs[a].points.size(); b++) {
      pessum::logging::Log(pessum::logging::LOG_DATA,
                           std::to_string(graphs[a].points[b].x) + "," +
                               std::to_string(graphs[a].points[b].y));
    }
  }
}

void aequus::video::AdvObject::DrawLineGraph() {
  backgroundcolor.r = 0;
  backgroundcolor.g = 0;
  backgroundcolor.b = 0;
  backgroundcolor.a = 1;
  int colorjump = 0;
  maxx = graphs[0].points[0].x;
  minx = maxx;
  maxy = graphs[0].points[0].y;
  miny = maxy;
  for (unsigned a = 0; a < graphs.size(); a++) {
    for (unsigned b = 0; b < graphs[a].points.size(); b++) {
      if (graphs[a].points[b].x > maxx) {
        maxx = graphs[a].points[b].x;
      } else if (graphs[a].points[b].x < minx) {
        minx = graphs[a].points[b].x;
      }
      if (graphs[a].points[b].y > maxy) {
        maxy = graphs[a].points[b].y;
      } else if (graphs[a].points[b].y < miny) {
        miny = graphs[a].points[b].y;
      }
    }
  }
  stepx = width / (maxx - minx);
  stepy = height / (maxy - miny);
  objrenderer.SetTargetTexture(globalobj);
  draw::SetColor(0, 0, 0, 0);
  objrenderer.Clear();
  if (background == true) {
    DrawBackground(colorjump);
    colorjump++;
  }
  if (grid == true) {
    DrawGrid();
  }
  if (axis == true) {
    DrawAxis();
  }
  if (labels == true) {
    DrawLabels();
  }
  if (title == true) {
    DrawTitle();
  }
  if (values == true) {
    DrawValues();
  }
  if (imagetitle == true) {
    DrawImageTitle();
  }
  for (unsigned a = 0; a < graphs.size(); a++) {
    if (colors.size() > a + colorjump) {
      draw::SetColor(colors[a + colorjump].r, colors[a + colorjump].g,
                     colors[a + colorjump].b, colors[a + colorjump].a);
    } else {
      if (background == false) {
        draw::SetColor(1, 1, 1, 1);
      } else if (background == true) {
        draw::SetColor(0, 0, 0, 1);
      }
    }
    std::vector<ValueGroup> graphpoints = graphs[a].points;
    for (unsigned b = 0; b < graphpoints.size(); b++) {
      graphpoints[b].x = ConvertValue(graphpoints[b].x, false);
      graphpoints[b].y = ConvertValue(graphpoints[b].y, true);
    }
    draw::Lines(graphpoints);
  }
  SDL_SetRenderTarget(objrenderer.sdlrenderer, NULL);
  globalobj.Scale(width, height);
}

void aequus::video::AdvObject::DrawBackground(int colorjump) {
  if (colors.size() > colorjump) {
    draw::SetColor(colors[colorjump].r, colors[colorjump].g,
                   colors[colorjump].b, colors[colorjump].a);
    backgroundcolor.r = colors[colorjump].r;
    backgroundcolor.g = colors[colorjump].g;
    backgroundcolor.b = colors[colorjump].b;
    backgroundcolor.a = colors[colorjump].a;
  } else {
    draw::SetColor(1, 1, 1, 1);
    backgroundcolor.r = 1;
    backgroundcolor.g = 1;
    backgroundcolor.b = 1;
    backgroundcolor.a = 1;
  }
  ValueGroup rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = width;
  rect.h = height;
  draw::FillRect(rect);
}

void aequus::video::AdvObject::DrawAxis() {
  if (background == false) {
    draw::SetColor(1, 1, 1, 1);
  } else if (background == true) {
    draw::SetColor((backgroundcolor.r - 1) * -1, (backgroundcolor.g - 1) * -1,
                   (backgroundcolor.b - 1) * -1, 1);
  }
  ValueGroup xstart, ystart, xend, yend;
  ystart.y = miny;
  ystart.x = 0;
  yend.y = maxy;
  yend.x = 0;
  xstart.x = minx;
  xstart.y = 0;
  xend.x = maxx;
  xend.y = 0;
  if (minx > 0 || maxx < 0) {
    ystart.y = miny;
    ystart.x = minx;
    yend.y = maxy;
    yend.x = minx;
  }
  if (miny > 0 || maxy < 0) {
    xstart.x = minx;
    xstart.y = miny;
    xend.x = maxx;
    xend.y = miny;
  }

  xstart.x = ConvertValue(xstart.x, false);
  xstart.y = ConvertValue(xstart.y, true);
  xend.x = ConvertValue(xend.x, false);
  xend.y = ConvertValue(xend.y, true);
  ystart.x = ConvertValue(ystart.x, false);
  ystart.y = ConvertValue(ystart.y, true);
  yend.x = ConvertValue(yend.x, false);
  yend.y = ConvertValue(yend.y, true);
  draw::Line(xstart, xend);
  draw::Line(ystart, yend);
}

void aequus::video::AdvObject::DrawGrid() {
  if (background == false) {
    draw::SetColor(1, 1, 1, 1);
  } else if (background == true) {
    if (backgroundcolor.r != 0 || backgroundcolor.g != 0 ||
        backgroundcolor.b != 0) {
      draw::SetColor(((backgroundcolor.r * 0.2) - 1) * -1,
                     ((backgroundcolor.g * 0.2) - 1) * -1,
                     ((backgroundcolor.b * 0.2) - 1) * -1, 1);
    } else if (backgroundcolor.r == 0 && backgroundcolor.g == 0 &&
               backgroundcolor.b == 0) {
      draw::SetColor(((backgroundcolor.r - 1) * -1 * 0.2),
                     ((backgroundcolor.g - 1) * -1 * 0.2),
                     ((backgroundcolor.b - 1) * -1 * 0.2), 1);
    }
  }
  for (double i = minx; i < maxx; i += (maxx - minx) / (double)20) {
    ValueGroup start, end;
    start.x = ConvertValue(i, false);
    start.y = ConvertValue(miny, true);
    end.x = ConvertValue(i, false);
    end.y = ConvertValue(maxy, true);
    draw::Line(start, end);
  }
  for (double i = miny; i < maxy; i += (maxy - miny) / (double)20) {
    ValueGroup xstart, xend;
    xstart.x = ConvertValue(minx, false);
    xstart.y = ConvertValue(i, true);
    xend.x = ConvertValue(maxx, false);
    xend.y = ConvertValue(i, true);
    draw::Line(xstart, xend);
  }
}

void aequus::video::AdvObject::DrawLabels() {}

void aequus::video::AdvObject::DrawTitle() {}

void aequus::video::AdvObject::DrawValues() {}

void aequus::video::AdvObject::DrawImageTitle() {}

void aequus::video::AdvObject::GenColors(int number) {
  double red = 1, green = 0, blue = 0;
  int stageone = 0, stagetwo = 0;
  if (background == true) {
    ValueGroup newcolor;
    newcolor.r = 1;
    newcolor.g = 1;
    newcolor.b = 1;
    newcolor.a = 1;
    colors.push_back(newcolor);
  }
  for (int a = 0; a < number; a++) {
    ValueGroup newcolor;
    newcolor.r = red;
    newcolor.g = green;
    newcolor.b = blue;
    newcolor.a = 1;
    colors.push_back(newcolor);
    if (stageone == 0) {
      red = 0;
      green = 1;
      stageone = 1;
    } else if (stageone == 1) {
      green = 0;
      blue = 1;
      stageone = 2;
    } else if (stageone == 2) {
      red = 1;
      green = 1;
      blue = 1;
      stageone = 3;
    }
    if (stageone > 2) {
      if (stagetwo == 0) {
        red = red - (0.9 / (number - 3));
        stagetwo = 1;
      } else if (stagetwo == 1) {
        green = green - (0.9 / (number - 3));
        stagetwo = 2;
      } else if (stagetwo == 2) {
        blue = blue - (0.9 / (number - 3));
        stagetwo = 0;
      }
    }
  }
}

int aequus::video::AdvObject::ConvertValue(double value, bool yaxis) {
  if (yaxis == false) {
    if (minx < 0) {
      value += minx * -1;
    }
    if (minx > 0) {
      value -= minx;
    }
    value *= stepx;
  } else if (yaxis == true) {
    if (minx < 0) {
      value += miny * -1;
    }
    if (minx > 0) {
      value -= miny;
    }
    value = (value - (maxy - miny)) * -1;
    value *= stepy;
  }
  return (value);
}
