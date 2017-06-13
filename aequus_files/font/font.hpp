#ifndef AEQUUS_FONT_HPP
#define AEQUUS_FONT_HPP
#include <string>
namespace aequus{
  enum FontWeights{
    THIN, EXTRA_LIGHT, LIGHT, REGULAR, MEDIUM, SEMIBOLD, BOLD, EXTRA_BOLD, BLACK
  };
  class Font{
    public:
      Font();
      Font(const Font& copy);
      Font(std::string path);
      void Point(int pt);
      ~Font();
    private:
      std::string folder_path;
      int point;
  };
}
#endif
