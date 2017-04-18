#ifndef AEQUUS_OBJECT_BASE_HPP
#define AEQUUS_OBJECT_BASE_HPP
#include "../sdl_headers.hpp"
namespace aequus {
  enum ObjectType { AEQ_OBJ_NONE, AEQ_OBJ_LAYOUT, AEQ_OBJ_IMAGE };
  class ObjectBase {
   public:
    ObjectBase();
    ObjectBase(const ObjectBase& obj);
    ~ObjectBase();
    virtual int Type();
    virtual void Display();
    void Scale(double x, double y);
    void Scale(double x);
    void Scale(int x, int y);
    void Scale(int x, bool height = false);
    void Translate(int x, int y);
    void Rotate(double angle);
   protected:
    void CreateSdlTexture();

    SDL_Texture* sdl_texture = NULL;
    SDL_Surface* sdl_surface = NULL;
    SDL_Renderer* sdl_renderer = NULL;

    SDL_Rect* sdl_base_size = NULL;
    SDL_Rect* sdl_source_rect = NULL;
    SDL_Rect* sdl_dest_rect = NULL;

    SDL_Point* sdl_rotate_point = NULL;
    float rotate_angle = 0.0;

    SDL_RendererFlip sdl_renderer_flip = SDL_FLIP_NONE;
    SDL_BlendMode sdl_blend_mode = SDL_BLENDMODE_BLEND;
  };
}
#endif
