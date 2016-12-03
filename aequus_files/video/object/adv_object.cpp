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
    bool graphlabels, bool graphtitle, bool graphimagetitle,
    std::string graphname, double xstart, double xend, double ystart,
    double yend) {
  objtype = GRAPH;
  axis = graphaxis;
  values = graphvalues;
  labels = graphlabels;
  title = graphtitle;
  grid = graphgrid;
  imagetitle = graphimagetitle;
  background = graphbackground;
  graphformat = graphtype;
  titlestr = graphname;
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

void aequus::video::AdvObject::UpdateGraph(std::string data) {
  GraphType tgraphtype = graphformat;
  int tgraphwidth = width, tgraphheight = height;
  bool gbg = background, ga = axis, gv = values, gl = labels, gt = title,
       gg = grid, git = imagetitle;
  std::string gtitle = titlestr;
  double gsx = minx, gex = maxx;
  double gsy = miny, gey = maxy;
  if (graphformat == PLOT) {
    gsy = 0;
    gey = 0;
  }
  TerminateAdvObject();
  CreateGraph(data, tgraphtype, tgraphwidth, tgraphheight, gbg, ga, gg, gv, gl,
              gt, git, gtitle, gsx, gex, gsy, gey);
}

void aequus::video::AdvObject::CreateTextBox(int boxwidth, int boxheight,
                                             std::string texture,
                                             bool whitetext, bool clip,
                                             std::string defaulttext) {
  objtype = TEXTBOX;
  storedtext = defaulttext;
  selected = false;
  whitetextcheck = whitetext;
  clipcheck = clipcheck;
  width = boxwidth;
  height = boxheight;
  texturedir = texture;
  posx = 0;
  posy = 0;
  globalobj.InitalizeObj(objrenderer.sdlrenderer, (advobjcount * 10) + 1,
                         resourcedir);
  globalobj.CreateButton(defaulttext, texturedir, whitetext, clip, false, width,
                         height);
}

void aequus::video::AdvObject::UpdateTextBox(int x, int y, int state) {
  if (globalobj.UpdateButton(x, y, state) == true) {
    if (selected == true) {
      selected = false;
      globalobj.SetColor(1, 1, 1, 1);
    } else {
      selected = true;
      if (clipcheck == false) {
        globalobj.SetColor(0.0, 0.5, 0.85, 1);
      }
    }
  }
}

void aequus::video::AdvObject::UpdateTextBoxText(int key) {
  bool updatetext = false;
  if (selected == true) {
    if (key == 8 && storedtext.size() > 0) {
      updatetext = true;
      storedtext.pop_back();
    } else if (key == 13) {
      updatetext = true;
      selected = false;
    } else if (key == 127 && storedtext.size() > 0) {
      updatetext = true;
      storedtext.pop_back();
    } else if (key >= 32 && key <= 126) {
      updatetext = true;
      storedtext.push_back(char(key));
    }
    if (updatetext = true) {
      globalobj.CreateButton(storedtext, texturedir, whitetextcheck, clipcheck,
                             false, width, height);
      if (selected == true) {
        globalobj.SetColor(0, 0.5, 0.85, 1);
      } else {
        globalobj.SetColor(1, 1, 1, 1);
      }
      globalobj.SetPos(posx, posy);
    }
  }
}

std::string aequus::video::AdvObject::GetString() {
  if (selected == false) {
    return (storedtext);
  } else {
    return ("");
  }
}

void aequus::video::AdvObject::Display() { globalobj.DisplayObj(); }

void aequus::video::AdvObject::SetPos(int x, int y) {
  posx = x;
  posy = y;
  globalobj.SetPos(posx, posy);
}

void aequus::video::AdvObject::TerminateAdvObject() {
  logloc = 0;
  advobjcount = 0;
  posx = 0;
  posy = 0;
  width = 0;
  height = 0;
  storedtext = "";
  texturedir = "";
  whitetextcheck = false;
  clipcheck = false;
  selected = false;
  titlestr = "";
  titles.clear();
  graphs.clear();
  colors.clear();
  minx = 0;
  maxx = 0;
  miny = 0;
  maxy = 0;
  stepx = 0;
  stepy = 0;
  axis = false;
  values = false;
  labels = false;
  title = false;
  grid = false;
  imagetitle = false;
  background = false;
  globalobj.TerminateObject();
}

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
  titlestr = titles[0];
}

void aequus::video::AdvObject::ComputeDataPoints(std::string function) {
  if (titlestr == "") {
    titlestr = "PLOT GRAPH";
  }
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
  for (unsigned i = 0; i < functions.size(); i++) {
    GraphData newgraph;
    newgraph.title = functions[i];
    for (int j = 0; j < newgraph.title.size(); j++) {
      if (newgraph.title[j] == ' ') {
        newgraph.title.erase(newgraph.title.begin() + j);
      }
    }
    int equation = pessum::parser::ParseEquation(functions[i]);
    for (double x = minx; x < maxx; x = x + (maxx - minx) / width) {
      ValueGroup newpoint;
      newpoint.x = x;
      newpoint.y = pessum::parser::ComputeEquation(equation, x);
      newgraph.points.push_back(newpoint);
    }
    graphs.push_back(newgraph);
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
    draw::SetColor(0.2, 0.2, 0.2, 1);
  } else if (background == true) {
    if (backgroundcolor.r != 0 || backgroundcolor.g != 0 ||
        backgroundcolor.b != 0) {
      draw::SetColor(((backgroundcolor.r * 0.2) - 1) * -1,
                     ((backgroundcolor.g * 0.2) - 1) * -1,
                     ((backgroundcolor.b * 0.2) - 1) * -1, 1);
    } else if (backgroundcolor.r == 0 && backgroundcolor.g == 0 &&
               backgroundcolor.b == 0) {
      draw::SetColor(0.2, 0.2, 0.2, 1);
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

void aequus::video::AdvObject::DrawLabels() {
  double red = 1, green = 1, blue = 1;
  if (grid == true) {
    if (background == false) {
      red = 0.5;
      green = 0.5;
      blue = 0.5;
    } else if (background == true) {
      if (backgroundcolor.r != 0 || backgroundcolor.g != 0 ||
          backgroundcolor.b != 0) {
        red = ((backgroundcolor.r * 0.5) - 1) * -1;
        green = ((backgroundcolor.g * 0.5) - 1) * -1;
        blue = ((backgroundcolor.b * 0.5) - 1) * -1;
      } else if (backgroundcolor.r == 0 && backgroundcolor.g == 0 &&
                 backgroundcolor.b == 0) {
        red = 0.5;
        green = 0.5;
        blue = 0.5;
      }
    }
    for (double i = minx; i < maxx; i += (maxx - minx) / (double)20) {
      std::string labelstr = std::to_string(i);
      for (int i = labelstr.size() - 1; i > 0; i--) {
        if (labelstr[i] == '0') {
          labelstr.pop_back();
        } else if (labelstr[i] != '0') {
          break;
        }
      }
      if (labelstr.back() == '.') {
        labelstr.pop_back();
      }
      Object label;
      label.InitalizeObj(objrenderer.sdlrenderer);
      label.CreateTextObj(labelstr, 10, red, green, blue, 1);
      label.SetPos(ConvertValue(i, false), ConvertValue(0, true));
      label.DisplayObj();
    }
    for (double i = miny; i < maxy; i += (maxy - miny) / (double)20) {
      std::string labelstr = std::to_string(i);
      for (int i = labelstr.size() - 1; i > 0; i--) {
        if (labelstr[i] == '0') {
          labelstr.pop_back();
        } else if (labelstr[i] != '0') {
          break;
        }
      }
      if (labelstr.back() == '.') {
        labelstr.pop_back();
      }
      Object label;
      label.InitalizeObj(objrenderer.sdlrenderer);
      label.CreateTextObj(labelstr, 10, red, green, blue, 1);
      label.SetPos(ConvertValue(0, false), ConvertValue(i, true));
      label.DisplayObj();
    }
  }
  if (axis == true) {
    if (background == true) {
      red = (backgroundcolor.r - 1) * -1;
      green = (backgroundcolor.g - 1) * -1;
      blue = (backgroundcolor.b - 1) * -1;
    }
    Object xlabel;
    xlabel.InitalizeObj(objrenderer.sdlrenderer);
    xlabel.CreateTextObj("X", 10, red, green, blue, 1);
    xlabel.SetPos(ConvertValue(maxx, false) - xlabel.GetIntValue("sizex"),
                  ConvertValue(0, true) - xlabel.GetIntValue("sizey"));
    xlabel.DisplayObj();
    Object ylabel;
    ylabel.InitalizeObj(objrenderer.sdlrenderer);
    ylabel.CreateTextObj("Y", 10, red, green, blue, 1);
    ylabel.SetPos(ConvertValue(0, false), ConvertValue(maxy, true));
    ylabel.DisplayObj();
  }
}

void aequus::video::AdvObject::DrawTitle() {
  double red = 1, blue = 1, green = 1, alpha = 1;
  for (int i = 0; i < graphs.size(); i++) {
    if (colors.size() > i + background) {
      red = colors[i + background].r;
      green = colors[i + background].g;
      blue = colors[i + background].b;
      alpha = colors[i + background].a;
    } else if (background == true) {
      red = 0;
      blue = 0;
      green = 0;
      alpha = 1;
    }
    Object title;
    title.InitalizeObj(objrenderer.sdlrenderer);
    title.CreateTextObj(graphs[i].title, 12, red, green, blue, alpha);
    title.SetPos(ConvertValue(graphs[i].points[0].x, false),
                 ConvertValue(graphs[i].points[0].y, true) -
                     title.GetIntValue("sizey"));
    title.DisplayObj();
  }
}

void aequus::video::AdvObject::DrawValues() {
  double red = 1, blue = 1, green = 1, alpha = 1;
  for (int i = 0; i < graphs.size(); i++) {
    double valuejump = 1;
    if (graphs[i].points.size() > 20) {
      valuejump = graphs[i].points.size() / 20.0;
    }
    if (colors.size() > i + background) {
      red = colors[i + background].r;
      green = colors[i + background].g;
      blue = colors[i + background].b;
      alpha = colors[i + background].a;
    } else if (background == true) {
      red = 0;
      blue = 0;
      green = 0;
      alpha = 1;
    }
    for (double j = 0; j < graphs[i].points.size(); j += valuejump) {
      int k = j;
      std::string valuestr = std::to_string(graphs[i].points[k].y);
      for (int i = valuestr.size() - 1; i > 0; i--) {
        if (valuestr[i] == '0') {
          valuestr.pop_back();
        } else if (valuestr[i] != '0') {
          break;
        }
      }
      if (valuestr.back() == '.') {
        valuestr.pop_back();
      }
      Object value;
      value.InitalizeObj(objrenderer.sdlrenderer);
      value.CreateTextObj(valuestr, 10, red, green, blue, alpha);
      value.SetPos(ConvertValue(graphs[i].points[k].x, false),
                   ConvertValue(graphs[i].points[k].y, true));
      value.DisplayObj();
    }
  }
}

void aequus::video::AdvObject::DrawImageTitle() {
  double red = 1, green = 1, blue = 1;
  if (background == true) {
    red = (backgroundcolor.r - 1) * -1;
    green = (backgroundcolor.g - 1) * -1;
    blue = (backgroundcolor.b - 1) * -1;
  }
  Object name;
  name.InitalizeObj(objrenderer.sdlrenderer);
  name.CreateTextObj(titlestr, 20, red, green, blue, 1, Text::BOLD);
  name.DisplayObj();
}

void aequus::video::AdvObject::GenColors(int number) {
  double red = 1, green = 0, blue = 0;
  int stageone = 0;
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
    if (stageone == 3) {
      red = (rand() % 1000) / 1000.0;
      green = (rand() % 1000) / 1000.0;
      blue = (rand() % 1000) / 1000.0;
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
