#ifndef AEQUUS_OBJECT_BASE_HPP
#define AEQUUS_OBJECT_BASE_HPP
#include <utility>
#include "../sdl_headers.hpp"
#include "../types/type_headers.hpp"
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
    void SetRotatePoint(int x, int y);
    void SetRotatePoint(double x, double y);
    void SetRotatePoint(int x);
    void SetRotatePoint(double x);

    void SetSourcePos(int x, int y);
    void SetSourcePos(double x, double y);
    void SetSourceSize(int w, int h);
    void SetSourceSize(double w, double h);

    void SetDestRect(int x, int y, int w, int h);
    void SetDestRect(double x, double y, double w, double h);
    void SetSourceRect(int x, int y, int w, int h);
    void SetSourceRect(double x, double y, double w, double h);

    void SetBlendMode(SDL_BlendMode blend_mode);
    void SetRendererFlip(SDL_RendererFlip renderer_flip);

    void SetColorMod(int red, int blue, int green, int alpha = 255);
    void SetColorMod(double red, double blue, double green, double alpha = 1);

   protected:
    void CreateSdlTexture();

    std::pair<double, double> relative_rotate_point = std::make_pair(0.5, 0.5);

    SDL_Texture* sdl_texture = NULL;
    SDL_Surface* sdl_surface = NULL;
    SDL_Renderer* sdl_renderer = NULL;

    SDL_Rect* sdl_base_size = NULL;
    SDL_Rect* sdl_source_rect = NULL;
    SDL_Rect* sdl_dest_rect = NULL;

    SDL_Point* sdl_rotate_point = NULL;
    float rotate_angle = 0.0;

    Color color_mod = Make_Color(255, 255, 255, 255);

    SDL_RendererFlip sdl_renderer_flip = SDL_FLIP_NONE;
    SDL_BlendMode sdl_blend_mode = SDL_BLENDMODE_BLEND;
  };
}
#endif
