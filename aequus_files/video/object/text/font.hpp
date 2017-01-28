#ifndef VIDEO_OBJECT_TEXT_FONT_HPP
#define VIDEO_OBJECT_TEXT_FONT_HPP
#include "../../../sdl_headers.hpp"
#include "../../video_enums.hpp"
#include "../texture/texture.hpp"
#include <map>
#include <string>
#include <vector>
namespace aequus {
namespace video {
enum FontOptions {
  THIN,
  ITALIC_THIN,
  EXTRA_LIGHT,
  ITALIC_EXTRA_LIGHT,
  LIGHT,
  ITALIC_LIGHT,
  REGULAR,
  ITALIC_REGULAR,
  MEDIUM,
  ITALIC_MEDIUM,
  SEMIBOLD,
  ITALIC_SEMIBOLD,
  BOLD,
  ITALIC_BOLD,
  EXTRA_BOLD,
  ITALIC_EXTRA_BOLD,
  BLACK,
  ITALIC_BLACK
};
class Font {
public:
  void Init(std::string folderpath);
  void Delete();
  TTF_Font *GetFont(FontOptions option);

private:
  std::string path = "";
  int point = 12;
  std::map<FontOptions, TTF_Font *> fonts;
  void GenorateFonts();
  void UpdateFonts();
  std::string GetFile(FontOptions option);
  bool Exists(std::string file);
};
}
}
#endif
