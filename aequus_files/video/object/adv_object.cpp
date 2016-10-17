#include "../../../pessum_files/pessum_headers.h"
#include "../../aequus_headers.h"
#include "../../sdl_headers.h"
#include "adv_object.h"
#include <string>
#include <vector>

void aequus::video::AdvObject::InitalizeAdvObj(SDL_Renderer *renderer,
                                               int counter,
                                               std::string resource) {
  logloc = pessum::logging::AddLogLocation(
      "aequus_files/video/object/adv_object.cpp[" + std::to_string(counter) +
      "]/");
  resourcedir = resource;
  objrenderer = renderer;
}

void aequus::video::AdvObject::CreateGraph(std::string datafile, int width,
                                           int height, SDL_Renderer *renderer) {
  objtype = GRAPH;
  pessum::logging::Log();
  LoadGraphData(datafile);
  pessum::logging::Log();
  minx = points[0].x;
  maxx = points[0].x;
  miny = points[0].y;
  maxy = points[0].y;
  pessum::logging::Log();
  for (unsigned a = 1; a < points.size(); a++) {
    if (points[a].x < minx) {
      minx = points[a].x;
    } else if (points[a].x > maxx) {
      maxx = points[a].x;
    }
    if (points[a].y < miny) {
      miny = points[a].y;
    } else if (points[a].y > maxy) {
      maxy = points[a].y;
    }
  }
  pessum::logging::Log();
  std::string filepath = resourcedir + "images/graph.png";
  Surface graphline;
  graphline.LoadSurface(filepath);
  Surface graph;
  graph.sdlsurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  if (graph.sdlsurface == NULL) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to create graph surface", logloc,
                            "CreateGraph");
  }
  pessum::logging::Log();
  double xstep, ystep;
  xstep = (maxx - minx) / width;
  ystep = (maxy - miny) / height;
  SDL_Rect up = {0, 0, 200, 200};
  SDL_Rect down = {200, 0, 200, 200};
  SDL_Rect flat = {0, 200, 200, 200};
  SDL_Rect fill = {200, 200, 200, 200};
  pessum::logging::Log();
  for (unsigned a = 1; a < points.size(); a++) {
    if (points[a - 1].y < points[a].y) {
      int rectx, recty, rectw, recth;
      rectx = (xstep * points[a - 1].x);
      recty = (height - (ystep * points[a].y));
      rectw = xstep * (points[a].x - points[a - 1].x);
      recth = ystep * (points[a].y - points[a - 1].y);
      SDL_Rect dest = {rectx, recty, rectw, recth};
      SDL_BlitScaled(graphline.sdlsurface, &up, graph.sdlsurface, &dest);
    }
  }
}
void aequus::video::AdvObject::LoadGraphData(std::string datafile) {
  int pointerx, pointery;
  bool typedoublex, typedoubley;
  pessum::luxreader::DataFile data =
      pessum::luxreader::LoadLuxDataFile(datafile);
  pessum::logging::Log();
  for (unsigned a = 0; a < data.datafilevariables.size(); a++) {
    pessum::logging::Log();
    if (data.datafilevariables[a].variablename == "titles" &&
        data.datafilevariables[a].stringvectorvalues.size() > 2) {
      pessum::logging::Log(pessum::logging::LOG_DATA,
                           data.datafilevariables[a].stringvectorvalues[0]);
      graphtitle = data.datafilevariables[a].stringvectorvalues[0];
      pessum::logging::Log(pessum::logging::LOG_DATA, "A");
      xaxis = data.datafilevariables[a].stringvectorvalues[1];
      pessum::logging::Log();
      yaxis = data.datafilevariables[a].stringvectorvalues[2];
    }
    pessum::logging::Log();
    if (data.datafilevariables[a].variablename == xaxis) {
      if (data.datafilevariables[a].variabledefinitiontype == "int") {
        pointerx = a;
        typedoublex = false;
      } else {
        pointerx = a;
        typedoublex = true;
      }
    }
    pessum::logging::Log();
    if (data.datafilevariables[a].variablename == yaxis) {
      if (data.datafilevariables[a].variabledefinitiontype == "int") {
        pointery = a;
        typedoubley = false;
      } else {
        pointery = a;
        typedoubley = true;
      }
    }
  }
  pessum::logging::Log();
  if (typedoublex == false) {
    for (unsigned a = 0;
         a < data.datafilevariables[pointerx].intvectorvalues.size(); a++) {
      Value newvalue;
      newvalue.x = data.datafilevariables[pointerx].intvectorvalues[a];
      if (typedoubley == false &&
          data.datafilevariables[pointery].intvectorvalues.size() > a) {
        newvalue.y = data.datafilevariables[pointery].intvectorvalues[a];
      }
      if (typedoubley == true &&
          data.datafilevariables[pointery].doublevectorvalues.size() > a) {
        newvalue.y = data.datafilevariables[pointery].doublevectorvalues[a];
      }
      points.push_back(newvalue);
    }
    pessum::logging::Log();
  } else if (typedoublex == true) {
    for (unsigned a = 0;
         a < data.datafilevariables[pointerx].doublevectorvalues.size(); a++) {
      Value newvalue;
      newvalue.x = data.datafilevariables[pointerx].intvectorvalues[a];
      if (typedoubley == false &&
          data.datafilevariables[pointery].intvectorvalues.size() > a) {
        newvalue.y = data.datafilevariables[pointery].intvectorvalues[a];
      }
      if (typedoubley == true &&
          data.datafilevariables[pointery].doublevectorvalues.size() > a) {
        newvalue.y = data.datafilevariables[pointery].doublevectorvalues[a];
      }
      points.push_back(newvalue);
    }
  }
}
