#ifndef VIDEO_OBJECT_TEXT_TEXT_HPP
#define VIDEO_OBJECT_TEXT_TEXT_HPP
#include "../../../sdl_headers.hpp"
#include "../../video_enums.hpp"
#include "../texture/texture.hpp"
#include "font.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
enum TextRenderer { SOLID, SHADED, BLEND };
class Text : public Texture {
public:
  void Init(std::string str, std::string fontname, SDL_Renderer *renderer);
  void SetTextColor(std::vector<int> color);
  void SetTextColor(std::vector<double> color);
  void SetBackgroundColor(std::vector<int> color);
  void SetBackgroundColor(std::vector<double> color);
  void UpdateString(std::string newstr = "");
  void UpdateText();
  void Delete();

private:
  std::string text = "";
  TextRenderer textformat = BLEND;
  std::string textfont = "";
  std::vector<int> textcolor = {255, 255, 255, 255},
                   backgroundcolor = {0, 0, 0, 255};

  SDL_Color sdltextcolor, sdlbackgroundcolor;

  void GenorateText(SDL_Renderer *renderer = NULL);
};
}
}
#endif
