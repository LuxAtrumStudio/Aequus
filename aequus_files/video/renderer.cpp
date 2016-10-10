#include "renderer.h"
#include "../../pessum_files/logging.h"
#include "../aequus_headers.h"
#include <string>
#include <vector>

void aequus::video::Renderer::CreateRenderer(SDL_Window *sdlwindow,
                                             std::string title,
                                             RendererFlags flags) {
  logloc = pessum::logging::AddLogLocation("aequus_files/video/window[" +
                                           title + "]/renderer");
  sdlrenderer = SDL_CreateRenderer(sdlwindow, -1, flags);
  rendererflag = flags;
  if (sdlrenderer == NULL) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to create renderer", logloc,
                            "CreateRenderer");
    framework::GetError();
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Create renderer",
                            logloc, "CreateRenderer");
  }
}

void aequus::video::Renderer::DestroyRenderer() {
  SDL_DestroyRenderer(sdlrenderer);
  pessum::logging::LogLoc(pessum::logging::LOG_SUCCESS, "Destroyed renderer",
                          logloc, "DestroyRenderer");
}

void aequus::video::Renderer::SetTargetTexture(Object target) {
  if (rendererflag == TARGETTEXTURE) {
    if (SDL_SetRenderTarget(sdlrenderer, target.objtexture.sdltexture) != 0) {
      pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                              "Failed to set render target texture", logloc,
                              "SetTargetTexture");
      framework::GetError();
    }
  } else {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Renderer cannot target texture", logloc,
                            "SetTargetTexture");
  }
}

void aequus::video::Renderer::SetViewport(int rect[4]) {
  SDL_Rect sdlrect;
  sdlrect.x = rect[0];
  sdlrect.y = rect[1];
  sdlrect.w = rect[2];
  sdlrect.h = rect[3];
  if (SDL_RenderSetViewport(sdlrenderer, &sdlrect) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to set render viewport", logloc,
                            "SetViewport");
    framework::GetError();
  }
}

void aequus::video::Renderer::SetScale(float scalex, float scaley) {
  if (SDL_RenderSetScale(sdlrenderer, scalex, scaley) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to set render scale", logloc, "SetScale");
    framework::GetError();
  }
}

void aequus::video::Renderer::SetResolution(int width, int height) {
  if (SDL_RenderSetLogicalSize(sdlrenderer, width, height) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to set render resolution", logloc,
                            "SetResolution");
    framework::GetError();
  }
}

void aequus::video::Renderer::SetTargetClip(int rect[4]) {
  SDL_Rect sdlrect;
  sdlrect.x = rect[0];
  sdlrect.y = rect[1];
  sdlrect.w = rect[2];
  sdlrect.h = rect[3];
  if (SDL_RenderSetClipRect(sdlrenderer, &sdlrect) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to set render clip", logloc,
                            "SetTargetClip");
    framework::GetError();
  }
}

void aequus::video::Renderer::Update() { SDL_RenderPresent(sdlrenderer); }

void aequus::video::Renderer::Clear() {
  SDL_SetRenderDrawColor(sdlrenderer, 0, 0, 0, 1);
  if (SDL_RenderClear(sdlrenderer) != 0) {
    pessum::logging::LogLoc(pessum::logging::LOG_ERROR,
                            "Failed to clear renderer", logloc, "Clear");
    framework::GetError();
  }
  double color[4];
  for (unsigned a = 0; a < 4; a++) {
    color[a] = aequus::video::draw::drawcolor[a];
  }
  SDL_SetRenderDrawColor(sdlrenderer, color[0] * 255, color[1] * 255,
                         color[2] * 255, color[3] * 255);
}