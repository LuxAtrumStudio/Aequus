#ifndef AEQUUS_STRUCTS_COLOR_HPP
#define AEQUUS_STRUCTS_COLOR_HPP
namespace aequus {
  struct ColorValue {
    ColorValue() : value_(255) {}
    ColorValue(const ColorValue& copy) : value_(copy.value_) {}
    explicit ColorValue(int v) { value_ = (double)v / 255.0f; }
    explicit ColorValue(double v) { value_ = v; }
    operator int() { return (int)(value_ * 255); }
    operator double() { return value_; }
    operator unsigned char() { return (unsigned char)(value_ * 255); }
    operator unsigned int() { return (unsigned int)(value_ * 255); }
    double value_;

    friend bool operator==(const ColorValue& lhs, const ColorValue& rhs) {
      return lhs.value_ == rhs.value_;
    }
  };
  struct Color {
    Color() {}
    Color(const Color& copy) : r(copy.r), g(copy.g), b(copy.b), a(copy.a) {}
    Color(int r_, int g_, int b_, int a_ = 255) : r(r_), g(g_), b(b_), a(a_) {}
    Color(double r_, double g_, double b_, double a_ = 1.0)
        : r(r_), g(g_), b(b_), a(a_) {}
    ColorValue r, g, b, a;

    friend bool operator==(const Color& lhs, const Color& rhs) {
      return (lhs.r == rhs.r) && (lhs.g == rhs.g) && (lhs.b == rhs.b) &&
             (lhs.a == rhs.b);
    }
    friend bool operator!=(const Color& lhs, const Color& rhs) {
      return !(lhs == rhs);
    }
  } typedef Color;
}  // namespace aequus
#endif /* ifndef AEQUUS_STRUCTS_COLOR_HPP */
