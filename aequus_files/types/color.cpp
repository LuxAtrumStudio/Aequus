#include "color.hpp"

aequus::Color::Color() {}

aequus::Color::Color(int color) {
  red = color;
  blue = color;
  green = color;
  alpha = 255;
}

aequus::Color::Color(int color, int a) {
  red = color;
  blue = color;
  green = color;
  alpha = a;
}

aequus::Color::Color(int r, int g, int b) {
  red = r;
  blue = b;
  green = g;
  alpha = 255;
}

aequus::Color::Color(int r, int g, int b, int a) {
  red = r;
  blue = b;
  green = g;
  alpha = a;
}

aequus::Color::Color(double color) {
  red = 255 * color;
  blue = 255 * color;
  green = 255 * color;
  alpha = 255;
}

aequus::Color::Color(double color, double a) {
  red = 255 * color;
  blue = 255 * color;
  green = 255 * color;
  alpha = 255 * a;
}

aequus::Color::Color(double r, double g, double b) {
  red = 255 * r;
  blue = 255 * b;
  green = 255 * g;
  alpha = 255;
}

aequus::Color::Color(double r, double g, double b, double a) {
  red = 255 * r;
  blue = 255 * b;
  green = 255 * g;
  alpha = 255 * a;
}

aequus::Color::Color(const Color& copy) {
  red = copy.red;
  blue = copy.blue;
  green = copy.green;
  alpha = copy.alpha;
}

aequus::Color aequus::Make_Color(int color) { return (Color(color)); }

aequus::Color aequus::Make_Color(int color, int a) { return (Color(color, a)); }

aequus::Color aequus::Make_Color(int r, int g, int b) {
  return (Color(r, g, b));
}

aequus::Color aequus::Make_Color(int r, int g, int b, int a) {
  return (Color(r, g, b, a));
}

aequus::Color aequus::Make_Color(double color) { return (Color(color)); }

aequus::Color aequus::Make_Color(double color, double a) {
  return (Color(color, a));
}

aequus::Color aequus::Make_Color(double r, double g, double b) {
  return (Color(r, g, b));
}

aequus::Color aequus::Make_Color(double r, double g, double b, double a) {
  return (Color(r, g, b, a));
}
