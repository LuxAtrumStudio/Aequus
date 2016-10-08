#ifndef _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#define _AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
#include <string>
#include <vector>
#include "../../sdl_headers.h"
#include "text.h"
namespace aequus {
namespace video {
// Texture class is used for all uses of sdl textures, and manages all
// funcitons in relation to textures and manipulation of the texture
class Texture {
 public:
  // Used to define the current mode of blending for the texture
  enum BlendMode {
    NONE = SDL_BLENDMODE_NONE,
    BLEND = SDL_BLENDMODE_BLEND,
    ADD = SDL_BLENDMODE_ADD,
    MOD = SDL_BLENDMODE_MOD
  };
  // Used to set any texture mirroring is applied
  enum RenderFlip { NOFLIP = 0, HORIZONTAL = 1, VERITCAL = 2 };
  // Pointer to sdl texture
  SDL_Texture* sdltexture;
  // Pointer to sdl renderer for texture rendering
  SDL_Renderer* sdlrenderer;
  // Pointer to sdl surface for texture creation
  SDL_Surface* sdlsurface;
  // Creates a new sdl texture from provided sdl surface
  void CreateTexture(SDL_Surface* surface);
  // Termiantes the texture, and clears all data
  void TerminateTexture();
  // Sets the sdl renderer for texture rendering to the provided sdl renderer
  void SetRenderer(SDL_Renderer* renderer = NULL);
  // Renders the texture to the currently set renderer
  void Render();
  // Sets the color modication to the texture
  // red, green, blue, alpha
  void SetColorMod(double colormod[4] = 0);
  // Sets the blending mode for the texture
  void SetBlendMode(BlendMode mode);
  // Rotates the texture to specified angle given in degrees or radians
  void Rotate(double angle, bool degree = false);
  // Mirrors the texture according to the provided value
  void Flip(RenderFlip flip);
  // Sets the point of rotaiton fr the texture
  void SetRotatePoint(int x, int y);
  // Sets the source clip rectangle
  // x, y are the top right of the clip
  // x, y, width, height
  void SetSourceRect(int rect[4] = 0);
  // Sets the destination clip rectangle that the texture is sent to
  // Defaults to the same size as the texture clip space
  // x, y are the top right of the clip
  // x, y, widht, height
  void SetDestinationRect(int rect[4] = 0);

 private:
  // Stores the log location index
  int logloc = 0;
  // Stores the textures width and height, for future use
  int texturewidth, textureheight;
  // Declairs where the texture originated from:
  // either a text surface, or an image surface
  bool textorigin = false;
  // Stores the current angle of rotation for the texutre
  double rotateangle = 0;
  // Stores the current blending mode for the texture
  BlendMode blendmode = NONE;
  // Stores the currently set mirroring settings for the texture
  RenderFlip renderflip = RenderFlip::NOFLIP;
  // Stores the current roation axis for the texture
  int rotatex = -1, rotatey = -1;
  // Sdl rectangles for the source and destinaiton clips
  SDL_Rect sourcerect = {0, 0, 0, 0}, destinationrect = {0, 0, 0, 0};
  // Stores the color modification data for the texture
  // red, green, blue, alpha
  double color[4];
  // Loades the sdl texture structure from preassigned variables
  void LoadTexture();
  // Closes the sdl texture and reloads a new one based off of new variables
  void UpdateTexture();
  // Terminates the sdl texture, but maintains all class data
  void CloseTexture();
};
}
}
#endif  // !_AEQUUS_FILES_VIDEO_OBJECT_TEXTURE_H_
