#ifndef AEQUUS_STRUCTS_COLOR_HPP
#define AEQUUS_STRUCTS_COLOR_HPP
namespace aequus {
  struct ColorValue {
    ColorValue() : value_(255) {}
    ColorValue(const ColorValue& copy) : value_(copy.value_) {}
    explicit ColorValue(int v) { value_ = v; }
    explicit ColorValue(double v) { value_ = (int)(255 * v); }
    operator int() { return value_; }
    operator double() { return (double)value_ / (double)255; }
    operator unsigned char() { return (unsigned char)value_; }
    operator unsigned int() { return (unsigned int)value_; }
    int value_;
  };
  struct Color {
    Color() {}
    Color(const Color& copy) : r(copy.r), g(copy.g), b(copy.b), a(copy.a) {}
    Color(int r_, int g_, int b_, int a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}
    Color(double r_, double g_, double b_, double a_ = 1.0)
        : r(r_), g(g_), b(b_), a(a_) {}
    ColorValue r, g, b, a;
  } typedef Color;
}  // namespace aequus
#endif /* ifndef AEQUUS_STRUCTS_COLOR_HPP */
