#include "../aequus_headers.hpp"
#include "draw.hpp"
#include <pessum.h>

namespace aequus {
namespace video {
namespace draw {
SDL_Renderer *sdlrenderer = NULL;
int logloc = 0;
double drawcolor[4] = {0};
}
}
}

void aequus::video::draw::InitializeDraw(SDL_Renderer *renderer) {
  sdlrenderer = renderer;
  logloc = pessum::logging::AddLogLocation("aequus_files/video/draw.h/");
}

void aequus::video::draw::SetRenderer(SDL_Renderer *renderer) {
  sdlrenderer = renderer;
}

void aequus::video::draw::Line(ValueGroup a, ValueGroup b) {
  if (sdlrenderer != NULL) {
    if (SDL_RenderDrawLine(sdlrenderer, a.x, a.y, b.x, b.y) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to draw line",
                              logloc, "Line");
    }
  }
}

void aequus::video::draw::Lines(std::vector<ValueGroup> points) {
  if (sdlrenderer != NULL) {
    std::vector<SDL_Point> sdlvec;
    for (unsigned a = 0; a < points.size(); a++) {
      SDL_Point newpoint;
      newpoint.x = points[a].x;
      newpoint.y = points[a].y;
      sdlvec.push_back(newpoint);
    }
    SDL_Point *sdlpoints = &sdlvec[0];
    if (SDL_RenderDrawLines(sdlrenderer, sdlpoints, points.size()) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to draw lines",
                              logloc, "Lines");
    }
  }
}

void aequus::video::draw::Point(ValueGroup point) {
  if (sdlrenderer != NULL) {
    if (SDL_RenderDrawPoint(sdlrenderer, point.x, point.y) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to draw point",
                              logloc, "Point");
    }
  }
}

void aequus::video::draw::Points(std::vector<ValueGroup> points) {
  if (sdlrenderer != NULL) {
    std::vector<SDL_Point> sdlvec;
    for (unsigned a = 0; a < points.size(); a++) {
      SDL_Point newpoint;
      newpoint.x = points[a].x;
      newpoint.y = points[a].y;
      sdlvec.push_back(newpoint);
    }
    SDL_Point *sdlpoints = &sdlvec[0];
    if (SDL_RenderDrawPoints(sdlrenderer, sdlpoints, points.size()) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR, "Failed to draw points",
                              logloc, "Points");
    }
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR, "Renderer Undeclaired",
                            logloc, "Points");
  }
}

void aequus::video::draw::Rect(ValueGroup rect) {
  if (sdlrenderer != NULL) {
    SDL_Rect sdlrect = {rect.x, rect.y, rect.w, rect.h};
    if (SDL_RenderDrawRect(sdlrenderer, &sdlrect) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to draw rectangle", logloc, "Rect");
    }
  }
}

void aequus::video::draw::Rects(std::vector<ValueGroup> rects) {
  if (sdlrenderer != NULL) {
    std::vector<SDL_Rect> sdlvec;
    for (unsigned a = 0; a < rects.size(); a++) {
      SDL_Rect newrect = {rects[a].x, rects[a].y, rects[a].w, rects[a].h};
      sdlvec.push_back(newrect);
    }
    SDL_Rect *sdlrects = &sdlvec[0];
    if (SDL_RenderDrawRects(sdlrenderer, sdlrects, sdlvec.size()) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to draw rectangles", logloc, "Rects");
    }
  }
}

void aequus::video::draw::FillRect(ValueGroup rect) {
  if (sdlrenderer != NULL) {
    SDL_Rect sdlrect = {rect.x, rect.y, rect.w, rect.h};
    if (SDL_RenderFillRect(sdlrenderer, &sdlrect) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to fill rectangle", logloc, "FillRect");
    }
  }
}

void aequus::video::draw::FillRects(std::vector<ValueGroup> rects) {
  if (sdlrenderer != NULL) {
    std::vector<SDL_Rect> sdlvec;
    for (unsigned a = 0; a < rects.size(); a++) {
      SDL_Rect newrect = {rects[a].x, rects[a].y, rects[a].w, rects[a].h};
      sdlvec.push_back(newrect);
    }
    SDL_Rect *sdlrects = &sdlvec[0];
    if (SDL_RenderFillRects(sdlrenderer, sdlrects, sdlvec.size()) != 0) {
      pessum::logging::LogLoc(pessum::logging::ERROR,
                              "Failed to fill rectangles", logloc, "FillRects");
    }
  }
}

void aequus::video::draw::SetColor(double red, double green, double blue,
                                   double alpha) {
  drawcolor[0] = red;
  drawcolor[1] = green;
  drawcolor[2] = blue;
  drawcolor[3] = alpha;
  SDL_SetRenderDrawColor(sdlrenderer, red * 255, green * 255, blue * 255,
                         alpha * 255);
}
