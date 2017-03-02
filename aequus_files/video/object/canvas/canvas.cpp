#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "../object.hpp"
#include "canvas.hpp"
#include <iostream>
#include <pessum.h>
#include <stdarg.h>
#include <string>

void aequus::video::Canvas::Init(int width, int height,
                                 SDL_Renderer *renderer) {
  sdlsurface = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  texturerenderer = SDL_CreateSoftwareRenderer(sdlsurface);
  SDL_SetRenderDrawBlendMode(texturerenderer, SDL_BLENDMODE_BLEND);
  InitTexture(sdlsurface, renderer);
  pessum::logging::Log("SUCCESS", "Created canvas", "aeq/vid/obj/can", "Init");
  Clear();
}

int aequus::video::Canvas::InitShape(bool line, bool closed, bool filled) {
  Shape newshape;
  newshape.color = color;
  newshape.line = line;
  newshape.closed = closed;
  newshape.filled = filled;
  newshape.origin = std::make_pair(0, 0);
  shapes.push_back(newshape);
  return (shapes.size() - 1);
}

void aequus::video::Canvas::SetShapeColor(std::vector<int> color,
                                          int shapeindex) {
  if (shapeindex < 0) {
    shapeindex = shapes.size() + shapeindex;
  }
  if (shapeindex >= 0 && shapeindex < shapes.size()) {
    shapes[shapeindex].color = color;
  }
}

void aequus::video::Canvas::SetShapeBackgroundColor(std::vector<int> color,
                                                    int shapeindex) {
  if (shapeindex < 0) {
    shapeindex = shapes.size() + shapeindex;
  }
  if (shapeindex >= 0 && shapeindex < shapes.size()) {
    shapes[shapeindex].backgroundcolor = color;
  }
}

void aequus::video::Canvas::AddVertex(int x, int y, int shapeindex) {
  if (shapeindex < 0) {
    shapeindex = shapes.size() + shapeindex;
  }
  if (shapeindex >= 0 && shapeindex < shapes.size()) {
    shapes[shapeindex].points.push_back(std::make_pair(x, y));
  }
}

void aequus::video::Canvas::SetShapeOrigin(int x, int y, int shapeindex) {
  if (shapeindex < 0) {
    shapeindex = shapes.size() + shapeindex;
  }
  if (shapeindex >= 0 && shapeindex < shapes.size()) {
    shapes[shapeindex].origin = std::make_pair(x, y);
  }
}

void aequus::video::Canvas::DeleteShape(int shapeindex) {
  if (shapeindex < 0) {
    shapeindex = shapes.size() + shapeindex;
  }
  if (shapeindex >= 0 && shapeindex < shapes.size()) {
    shapes.erase(shapes.begin() + shapeindex);
  }
}

void aequus::video::Canvas::DrawArc(int x, int y, int w, int h,
                                    double thetastart, double thetaend) {
  int shapeindex = InitShape(true, false, false);
  for (double theta = thetastart; theta < thetaend; theta += 0.1) {
    AddVertex(x + (int)(w * cos(theta)), y - (int)(h * sin(theta)), shapeindex);
  }
}

void aequus::video::Canvas::DrawEllipse(int x, int y, int w, int h) {
  int shapeindex = InitShape(true, true, false);
  for (double theta = 0; theta < 2 * 6.283; theta += 0.1) {
    AddVertex(x + (int)(w * cos(theta)), y - (int)(h * sin(theta)), shapeindex);
  }
}

void aequus::video::Canvas::DrawLine(int x1, int y1, int x2, int y2) {
  int shapeindex = InitShape(true, false, false);
  AddVertex(x1, y1, shapeindex);
  AddVertex(x2, y2, shapeindex);
}

void aequus::video::Canvas::DrawPoint(int x, int y) {
  int shapeindex = InitShape(false, false, false);
  AddVertex(x, y, shapeindex);
}

void aequus::video::Canvas::DrawQuad(int vertexcount, ...) {
  int shapeindex = InitShape(true, true, false);
  va_list ap;
  va_start(ap, vertexcount);
  for (int i = 0; i < vertexcount; i++) {
    int x = va_arg(ap, int);
    int y = va_arg(ap, int);
    AddVertex(x, y, shapeindex);
  }
  va_end(ap);
}

void aequus::video::Canvas::DrawRect(int x, int y, int w, int h, int tl, int tr,
                                     int bl, int br) {
  int shapeindex = InitShape(true, true, false);
  if (tl == -1 && tr == -1 && bl == -1 && br == -1) {
    AddVertex(x, y, shapeindex);
    AddVertex(x + w, y, shapeindex);
    AddVertex(x + w, y + h, shapeindex);
    AddVertex(x, y + h, shapeindex);
  } else {
    if (tl != -1 && tr == -1 && bl == -1 && br == -1) {
      tr = tl;
      bl = tl;
      br = tl;
    }
    int cx = x + w - tr, cy = y + tr;
    double theta = 0, deltatheta = 0.1;
    while (theta < 1.57075) {
      AddVertex(cx + (int)(tr * cos(theta)), cy - (int)(tr * sin(theta)),
                shapeindex);
      theta += deltatheta;
    }
    cx = x + tl;
    cy = y + tl;
    while (theta < 3.14159) {
      AddVertex(cx + (int)(tl * cos(theta)), cy - (int)(tl * sin(theta)),
                shapeindex);
      theta += deltatheta;
    }
    cx = x + bl;
    cy = y + h - bl;
    while (theta < 4.71234) {
      AddVertex(cx + (int)(bl * cos(theta)), cy - (int)(bl * sin(theta)),
                shapeindex);
      theta += deltatheta;
    }
    cx = x + w - br;
    cy = y + h - br;
    while (theta < 6.28309) {
      AddVertex(cx + (int)(br * cos(theta)), cy - (int)(br * sin(theta)),
                shapeindex);
      theta += deltatheta;
    }
  }
}

void aequus::video::Canvas::DrawTriangle(int x1, int y1, int x2, int y2, int x3,
                                         int y3) {
  int shapeindex = InitShape(true, true, false);
  AddVertex(x1, y1, shapeindex);
  AddVertex(x2, y2, shapeindex);
  AddVertex(x3, y3, shapeindex);
}

void aequus::video::Canvas::Update() {
  for (int i = 0; i < shapes.size(); i++) {
    DrawShape(i);
  }
  UpdateTexture();
}

void aequus::video::Canvas::Delete() {
  DeleteTexture();
  SDL_DestroyRenderer(texturerenderer);
  shapes.clear();
}

void aequus::video::Canvas::Clear() {
  SDL_SetRenderDrawColor(texturerenderer, backgroundcolor[0],
                         backgroundcolor[1], backgroundcolor[2],
                         backgroundcolor[3]);
  SDL_RenderClear(texturerenderer);
  SDL_SetRenderDrawColor(texturerenderer, color[0], color[1], color[2],
                         color[3]);
}

void aequus::video::Canvas::DrawShape(int shapeindex) {
  if (shapes[shapeindex].color.size() == 3) {
    SDL_SetRenderDrawColor(texturerenderer, shapes[shapeindex].color[0],
                           shapes[shapeindex].color[1],
                           shapes[shapeindex].color[2], 255);
  }
  if (shapes[shapeindex].color.size() == 4) {
    SDL_SetRenderDrawColor(texturerenderer, shapes[shapeindex].color[0],
                           shapes[shapeindex].color[1],
                           shapes[shapeindex].color[2],
                           shapes[shapeindex].color[3]);
  }
  std::vector<SDL_Point> points;
  for (int i = 0; i < shapes[shapeindex].points.size(); i++) {
    SDL_Point newpoint;
    newpoint.x =
        shapes[shapeindex].points[i].first + shapes[shapeindex].origin.first;
    newpoint.y =
        shapes[shapeindex].points[i].second + shapes[shapeindex].origin.second;
    points.push_back(newpoint);
  }
  if (shapes[shapeindex].closed == true && points.size() > 0) {
    points.push_back(points[0]);
  }
  SDL_Point *sdlpoints = &points[0];
  if (shapes[shapeindex].line == false) {
    if (SDL_RenderDrawPoints(texturerenderer, sdlpoints, points.size()) != 0) {
      pessum::logging::Log("ERROR", "Failed to draw shape", "aeq/vid/obj/can",
                           "DrawShape");
      framework::GetSdlError(framework::SDL);
    }
  } else if (shapes[shapeindex].line == true) {
    if (SDL_RenderDrawLines(texturerenderer, sdlpoints, points.size()) != 0) {
      pessum::logging::Log("ERROR", "Failed to draw shape", "aeq/vid/obj/can",
                           "DrawShape");
      framework::GetSdlError(framework::SDL);
    }
  }
}
