#include "../../../pessum_files/pessum_headers.h"
#include "../../aequus_headers.h"
#include "../../sdl_headers.h"
#include "adv_object.h"
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

void aequus::video::AdvObject::CreateGraph(std::string datafile, int width,
                                           int height) {
  objtype = GRAPH;
  LoadGraphData(datafile);
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
  globalobj.InitalizeObj(objrenderer.sdlrenderer, (advobjcount * 10) + 1,
                         resourcedir);
  SDL_Surface *graphsurface;
  graphsurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  Renderer graphrenderer;
  graphrenderer.sdlrenderer = SDL_CreateSoftwareRenderer(graphsurface);
  if (graphrenderer.sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to create software renderer for surface",
                            logloc, "CreateGraph");
    framework::GetError();
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS,
                            "Create software renderer for surface", logloc,
                            "CreateGraph");
  }
  draw::InitializeDraw(objrenderer.sdlrenderer);
  draw::SetColor(1, 1, 1, 1);
  int a[2] = {0, 0};
  int b[2] = {100, 100};
  draw::Line(a, b);
  graphrenderer.Update();
  globalobj.objsurface.sdlsurface = graphsurface;
  globalobj.objtexture.SetRenderer(objrenderer.sdlrenderer);
  globalobj.objtexture.CreateTexture(globalobj.objsurface.sdlsurface);
  globalobj.LoadDefaults();
  /*
    globalobj.objtexture.SetRenderer(objrenderer.sdlrenderer);
    globalobj.objtexture.sdltexture =
        SDL_CreateTexture(objrenderer.sdlrenderer, SDL_PIXELFORMAT_RGBA8888,
                          SDL_TEXTUREACCESS_STATIC, width, height);
    globalobj.LoadDefaults();
    objrenderer.SetTargetTexture(globalobj);
    draw::InitializeDraw(objrenderer.sdlrenderer);
    draw::SetColor(1, 1, 1, 1);
    int a[2] = {0, 0};
    int b[2] = {100, 100};
    draw::Line(a, b);
    SDL_RenderPresent(objrenderer.sdlrenderer);
    if (SDL_SetRenderTarget(objrenderer.sdlrenderer, NULL) != 0) {
      pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                              "Failed to set renderer target to default",
    logloc,
                              "CreateGraph");
      framework::GetError();
    } else {
      pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS,
                              "Set renderer target to default", logloc,
                              "CreateGraph");
      objrenderer.Clear();
    }*/
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
            Value newvalue;
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
            Value newvalue;
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
  }
}
