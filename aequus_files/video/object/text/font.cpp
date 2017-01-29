#include "../../../framework/framework.hpp"
#include "../../../log_indices.hpp"
#include "../../../sdl_headers.hpp"
#include "font.hpp"
#include <map>
#include <pessum.h>
#include <string>

void aequus::video::Font::Init(std::string folderpath) {
  path = folderpath;
  GenorateFonts();
  pessum::logging::LogLoc(pessum::logging::SUCCESS, "Loaded font: " + path,
                          AVOF, "Init");
}

void aequus::video::Font::Delete() {
  std::vector<FontOptions> options = {
      THIN,   ITALIC_THIN,   EXTRA_LIGHT, ITALIC_EXTRA_LIGHT,
      LIGHT,  ITALIC_LIGHT,  REGULAR,     ITALIC_REGULAR,
      MEDIUM, ITALIC_MEDIUM, SEMIBOLD,    ITALIC_SEMIBOLD,
      BOLD,   ITALIC_BOLD,   EXTRA_BOLD,  ITALIC_EXTRA_BOLD,
      BLACK,  ITALIC_BLACK};
  for (int i = 0; i < options.size(); i++) {
    if (Exists(GetFile(options[i])) == true) {
      TTF_CloseFont(GetFont(options[i]));
    }
  }
  fonts.clear();
  path = "";
  point = 12;
}

void aequus::video::Font::SetPoint(int pt) {
  point = pt;
  UpdateFonts();
}

void aequus::video::Font::SetFolder(std::string folderpath) {
  path = folderpath;
  UpdateFonts();
}

TTF_Font *aequus::video::Font::GetFont(FontOptions option) {
  std::map<FontOptions, TTF_Font *>::iterator font;
  font = fonts.find(option);
  if (font != fonts.end()) {
    return (font->second);
  } else {
    pessum::logging::LogLoc(pessum::logging::ERROR,
                            "Font file does not exist: " + GetFile(option),
                            AVOF, "GetFont");
    return (NULL);
  }
}

bool aequus::video::Font::GoodFont() {
  if (fonts.size() > 0) {
    return (true);
  } else {
    return (false);
  }
}

void aequus::video::Font::GenorateFonts() {
  std::vector<FontOptions> options = {
      THIN,   ITALIC_THIN,   EXTRA_LIGHT, ITALIC_EXTRA_LIGHT,
      LIGHT,  ITALIC_LIGHT,  REGULAR,     ITALIC_REGULAR,
      MEDIUM, ITALIC_MEDIUM, SEMIBOLD,    ITALIC_SEMIBOLD,
      BOLD,   ITALIC_BOLD,   EXTRA_BOLD,  ITALIC_EXTRA_BOLD,
      BLACK,  ITALIC_BLACK};
  for (int i = 0; i < options.size(); i++) {
    if (Exists(GetFile(options[i])) == true) {
      fonts[options[i]] = TTF_OpenFont(GetFile(options[i]).c_str(), point);
    }
  }
}

void aequus::video::Font::UpdateFonts() {
  std::map<FontOptions, TTF_Font *>::iterator font;
  for (font = fonts.begin(); font != fonts.end(); ++font) {
    TTF_CloseFont(font->second);
  }
  fonts.clear();
  GenorateFonts();
}

std::string aequus::video::Font::GetFile(FontOptions option) {
  std::string file = "";
  for (unsigned a = path.size() - 1; a > 0 && path[a] != '/'; a--) {
    file = path[a] + file;
  }
  file = path + "/" + file + "-";
  if (option == THIN) {
    file += "Thin.ttf";
  } else if (option == ITALIC_THIN) {
    file += "ThinItalic.ttf";
  } else if (option == EXTRA_LIGHT) {
    file += "ExtraLight.ttf";
  } else if (option == ITALIC_EXTRA_LIGHT) {
    file += "ExtraLightItalic.ttf";
  } else if (option == LIGHT) {
    file += "Light.ttf";
  } else if (option == ITALIC_LIGHT) {
    file += "LightItalic.ttf";
  } else if (option == REGULAR) {
    file += "Regular.ttf";
  } else if (option == ITALIC_REGULAR) {
    file += "Italic.ttf";
  } else if (option == MEDIUM) {
    file += "Medium.ttf";
  } else if (option == ITALIC_MEDIUM) {
    file += "MediumItalic.ttf";
  } else if (option == SEMIBOLD) {
    file += "SemiBold.ttf";
  } else if (option == ITALIC_SEMIBOLD) {
    file += "SemiBoldItalic.ttf";
  } else if (option == BOLD) {
    file += "Bold.ttf";
  } else if (option == ITALIC_BOLD) {
    file += "BoldItalic.ttf";
  } else if (option == EXTRA_BOLD) {
    file += "ExtraBold.ttf";
  } else if (option == ITALIC_EXTRA_BOLD) {
    file += "ExtraBoldItalic.ttf";
  } else if (option == BLACK) {
    file += "Black.ttf";
  } else if (option == ITALIC_BLACK) {
    file += "BlackItalic.ttf";
  }
  return (file);
}
bool aequus::video::Font::Exists(std::string file) {
  std::ifstream f(file.c_str());
  return f.good();
}
