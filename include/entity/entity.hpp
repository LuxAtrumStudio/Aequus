#ifndef AEQUUS_OBJECT_OBJECT_HPP
#define AEQUUS_OBJECT_OBJECT_HPP

#include <memory>

#include "../sdl_headers.hpp"
#include "../types.hpp"
#include "texture.hpp"

namespace aequus {
  namespace entity {
    enum RenderFlip { FLIP_NONE, FLIP_HORIZONTAL, FLIP_VERTICAL };

    class Object {
     public:
      Object();
      Object(const Object& copy);
      Object(std::shared_ptr<SDL_Renderer*> renderer);
      ~Object();

      virtual void Display();

      void Scale(double w, double h);
      void ScaleWidth(double w);
      void ScaleHeight(double h);
      void SetSize(int w, int h);
      void SetWidth(int w);
      void SetHeight(int h);

      void Translate(int x, int y);
      void TranslateX(int x);
      void TranslateY(int y);
      void SetPosition(int x, int y);
      void SetPosX(int x);
      void SetPosY(int y);

      void ScaleSource(double w, double h);
      void ScaleSourceWidth(double w);
      void ScaleSourceHeight(double h);
      void SetSourceSize(int w, int h);
      void SetSourceWidth(int w);
      void SetSourceHeight(int h);

      void TranslateSource(int x, int y);
      void TranslateSourceX(int x);
      void TranslateSourceY(int y);
      void SetSourcePosition(int x, int y);
      void SetSourcePosX(int x);
      void SetSourcePosY(int y);

      void SetRect(Rect rect);
      void SetRect(int x, int y, int w, int h);
      void SetSourceRect(Rect rect);
      void SetSourceRect(int x, int y, int w, int h);

      void Rotate(double angle);
      void SetRotation(double angle);
      void SetRotatePoint(Point rotate_point);

      // TODO (06-09-17, Arden): Move to texture class.
      void SetBlendMode(unsigned int blend_mode);

      void SetRenderFlip(unsigned int render_flip);

      Rect GetRect();
      Rect GetSourceRect();

      // TODO (06-09-17, Arden): Move to texture class.
      void SetColorMod(Color color_mod);

     protected:
      // void CreateTexture();
      // void DestroyTexture();

      double rotate_angle_ = 0.0;
      Point rotate_point_;
      Rect source_rect_, dest_rect_;
      unsigned int blend_mode_, render_flip_;
      Color color_mod_;

      SDL_RendererFlip sdl_render_flip_;

      // std::shared_ptr<SDL_Texture*> sdl_texture_ = NULL;
      // std::shared_ptr<SDL_Surface*> sdl_surface_ = NULL;
      Texture texture_;
      std::shared_ptr<SDL_Renderer*> sdl_renderer_ = NULL;

     private:
    };
  }  // namespace entity
}  // namespace aequus

#endif /* ifndef AEQUUS_OBJECT_OBJECT_HPP */
