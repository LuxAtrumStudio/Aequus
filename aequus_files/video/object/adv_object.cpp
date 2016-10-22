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

void aequus::video::AdvObject::CreateGraph(std::string datafile,
                                           GraphType graphtype, int graphwidth,
                                           int graphheight, double xstart,
                                           double xend, double ystart,
                                           double yend) {
  objtype = GRAPH;
  if (graphtype == LINE) {
    LoadGraphData(datafile);
  }
  if (graphtype == PLOT) {
    minx = xstart;
    maxx = xend;
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
  globalobj.LoadDefaults();
  posx = 0;
  posy = 0;
  width = graphwidth;
  height = graphheight;
  if (graphtype == LINE) {
    DrawLineGraph();
  }
}

void aequus::video::AdvObject::Display() { globalobj.DisplayObj(); }

void aequus::video::AdvObject::LoadGraphData(std::string datafile) {
  int pointerx, pointery;
  bool typedoublex, typedoubley;
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
}

void aequus::video::AdvObject::ComputeDataPoints(std::string funcion) {}

void aequus::video::AdvObject::DrawLineGraph() {
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
  for (unsigned a = 0; a < graphs.size(); a++) {
    if (colors.size() > a) {
      draw::SetColor(colors[a].r, colors[a].g, colors[a].b, colors[a].a);
    } else {
      draw::SetColor(1, 1, 1, 1);
    }
    std::vector<ValueGroup> graphpoints = graphs[a].points;
    for (unsigned b = 0; b < graphpoints.size(); b++) {
      if (minx < 0) {
        graphpoints[b].x = graphpoints[b].x + (minx * -1);
      }
      if (miny < 0) {
        graphpoints[b].y = graphpoints[b].y + (miny * -1);
      }
      graphpoints[b].y = (graphpoints[b].y - (maxy - miny)) * -1;
      graphpoints[b].x = graphpoints[b].x * stepx;
      graphpoints[b].y = graphpoints[b].y * stepy;
      // pessum::logging::Log(pessum::logging::LOG_DATA,
      //                     std::to_string(graphpoints[b].x) + "," +
      //                         std::to_string(graphpoints[b].y));
    }
    draw::Lines(graphpoints);
  }
  SDL_SetRenderTarget(objrenderer.sdlrenderer, NULL);
  globalobj.Scale(width, height);
}
