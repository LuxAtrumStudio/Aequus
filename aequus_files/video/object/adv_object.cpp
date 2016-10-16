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
  std::string xaxis, yaxis, graphtitle;
  std::vector<Value> points;
  int pointerx, pointery;
  bool typedoublex, typedoubley;
  pessum::luxreader::DataFile data =
      pessum::luxreader::LoadLuxDataFile(datafile);
  for (unsigned a = 0; a < data.datafilevariables.size(); a++) {
    if (data.datafilevariables[a].variablename == "titles") {
      graphtitle = data.datafilevariables[a].stringvectorvalues[0];
      xaxis = data.datafilevariables[a].stringvectorvalues[1];
      yaxis = data.datafilevariables[a].stringvectorvalues[2];
    }
    if (data.datafilevariables[a].variablename == xaxis) {
      if (data.datafilevariables[a].variabledefinitiontype == "int") {
        pointerx = a;
        typedoublex = false;
      } else {
        pointerx = a;
        typedoublex = true;
      }
    }
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
        newvalue.doubley =
            data.datafilevariables[pointery].doublevectorvalues[a];
      }
      points.push_back(newvalue);
    }
  } else if (typedoublex == true) {
    for (unsigned a = 0;
         a < data.datafilevariables[pointerx].doublevectorvalues.size(); a++) {
      Value newvalue;
      newvalue.doublex = data.datafilevariables[pointerx].intvectorvalues[a];
      if (typedoubley == false &&
          data.datafilevariables[pointery].intvectorvalues.size() > a) {
        newvalue.y = data.datafilevariables[pointery].intvectorvalues[a];
      }
      if (typedoubley == true &&
          data.datafilevariables[pointery].doublevectorvalues.size() > a) {
        newvalue.doubley =
            data.datafilevariables[pointery].doublevectorvalues[a];
      }
      points.push_back(newvalue);
    }
  }
  for (unsigned a = 0; a < points.size(); a++) {
    pessum::logging::LogLoc(pessum::logging::LOG_DATA,
                            "(" + std::to_string(points[a].x) + "," +
                                std::to_string(points[a].y) + ")");
  }
}
