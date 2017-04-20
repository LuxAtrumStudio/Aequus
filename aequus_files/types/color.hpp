#ifndef AEQUUS_COLOR_HPP
#define AEQUUS_COLOR_HPP
namespace aequus {
  struct Color {
    Color();
    Color(int color);
    Color(int color, int a);
    Color(int r, int g, int b);
    Color(int r, int g, int b, int a);
    Color(double color);
    Color(double color, double a);
    Color(double r, double g, double b);
    Color(double r, double g, double b, double a);
    Color(const Color& copy);
    int red = 0, green = 0, blue = 0, alpha = 0;
  };
  Color Make_Color(int color);
  Color Make_Color(int color, int a);
  Color Make_Color(int r, int g, int b);
  Color Make_Color(int r, int g, int b, int a);
  Color Make_Color(double color);
  Color Make_Color(double color, double a);
  Color Make_Color(double r, double g, double b);
  Color Make_Color(double r, double g, double b, double a);
}
#endif
