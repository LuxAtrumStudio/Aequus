#ifndef VIDEO_OBJECT_BUTTON_BUTTON_HPP
#define VIDEO_OBJECT_BUTTON_BUTTON_HPP
#include "../../../sdl_headers.hpp"
#include "../image/image.hpp"
#include "../object.hpp"
#include "../text/text.hpp"
#include <string>
#include <vector>
namespace aequus {
namespace video {
class Button : public Object {
public:
  enum Cases { CLIP, COLOR, CUSTOM, NONE };
  void Init(std::string text, std::string font, std::string img,
            SDL_Renderer *renderer, int inwidth = -1, int inheight = -1);
  // Image Functions
  void UpdateFile(std::string img = "");
  // Text Functions
  void SetTextColor(std::vector<int> color);
  void SetTextColor(std::vector<double> color);
  void SetFormat(FontOptions format);
  void UpdateString(std::string newstr = "");
  // Button Functions
  void EventCheck(SDL_Event event);
  void SetStateCase(ButtonState state, Cases setting);
  void SetStateCase(ButtonState state, void (*function)(void));
  void SetSize(int newwidth, int newheight);
  void Delete();

private:
  int buttonwidth = -1, buttonheight = -1;
  std::string filepath = "";
  std::string buttontext = "";
  std::string textfontname = "";
  FontOptions fontoption = REGULAR;
  std::vector<int> textcolor = {255, 255, 255, 255};

  ButtonState currentstate = NORMAL;
  Cases hoverstate = COLOR, pressstate = COLOR, normalstate = COLOR,
        releasestate = NONE;
  void (*hoverfunction)(void);
  void (*pressfunction)(void);
  void (*normalfunction)(void);
  void (*releasefunction)(void);

  SDL_Color sdltextcolor;

  void GenorateButton(SDL_Renderer *renderer = NULL);
  void ColorStateChange();
  void ClipStateChange();
};
}
}
#endif
