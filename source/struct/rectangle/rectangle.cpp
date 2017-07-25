#include "rectangle.hpp"

#include <experimental/optional>

#include <pessum/pessum.hpp>

aequus::Rectangle::Rectangle() {}

aequus::Rectangle::Rectangle(int x_, int y_) : x(x_), y(y_) {}

aequus::Rectangle::Rectangle(int x_, int y_, int w_, int h_)
    : x(x_), y(y_), w(w_), h(h_) {}

aequus::Rectangle::~Rectangle() {}

void aequus::Rectangle::SetAttr(std::string name, int value_0) {
  if (name == "y" || name == "top") {
    y = value_0;
  } else if (name == "x" || name == "left") {
    y = value_0;
  } else if (name == "bottom") {
    y = value_0 - h;
  } else if (name == "right") {
    x = value_0 - w;
  } else if (name == "center_x") {
    x = (value_0 - w) / 2;
  } else if (name == "center_y") {
    y = (value_0 - h) / 2;
  } else if (name == "w" || name == "width") {
    w = value_0;
  } else if (name == "h" || name == "height") {
    h = value_0;
  } else {
    pessum::Log(pessum::WARNING, "Invalid attr \"%s\"",
                "aequus::Rectangle::SetAttr", name.c_str());
  }
}

void aequus::Rectangle::SetAttr(std::string name, int value_0, int value_1) {
  if (name == "top_left") {
    x = value_0;
    y = value_1;
  } else if (name == "bottom_left") {
    x = value_0;
    y = value_1 - h;
  } else if (name == "top_right") {
    x = value_0 - w;
    y = value_1;
  } else if (name == "bottom_right") {
    x = value_0 - w;
    y = value_1 - h;
  } else if (name == "mid_top") {
    x = (value_0 - w) / 2;
    y = value_1;
  } else if (name == "mid_left") {
    x = value_0;
    y = (value_1 - h) / 2;
  } else if (name == "mid_bottom") {
    x = (value_0 - w) / 2;
    y = value_1 - h;
  } else if (name == "mid_right") {
    x = value_0 - w;
    y = (value_1 - h) / 2;
  } else if (name == "center") {
    x = (value_0 - w) / 2;
    y = (value_1 - h) / 2;
  } else if (name == "size") {
    w = value_0;
    h = value_1;
  } else if (name == "y" || name == "top") {
    y = value_0;
  } else if (name == "x" || name == "left") {
    y = value_0;
  } else if (name == "bottom") {
    y = value_0 - h;
  } else if (name == "right") {
    x = value_0 - w;
  } else if (name == "center_x") {
    x = (value_0 - w) / 2;
  } else if (name == "center_y") {
    y = (value_0 - h) / 2;
  } else if (name == "w" || name == "width") {
    w = value_0;
  } else if (name == "h" || name == "height") {
    h = value_0;
  } else {
    pessum::Log(pessum::WARNING, "Invalid attr \"%s\"",
                "aequus::Rectangle::SetAttr", name.c_str());
  }
}

void aequus::Rectangle::SetAttr(std::string name, Point value) {
  SetAttr(name, value.x, value.y);
}

int aequus::Rectangle::GetAttr(std::string name) {
  if (name == "y" || name == "top") {
    return y;
  } else if (name == "x" || name == "left") {
    return x;
  } else if (name == "bottom") {
    return y + h;
  } else if (name == "right") {
    return x + w;
  } else if (name == "center_x") {
    return (x + w) / 2;
  } else if (name == "center_y") {
    return (y + h) / 2;
  } else if (name == "w" || name == "width") {
    return w;
  } else if (name == "h" || name == "height") {
    return h;
  } else {
    pessum::Log(pessum::WARNING, "Invalid attr \"%s\"",
                "aequus::Rectangle::SetAttr", name.c_str());
    return 0;
  }
}

aequus::Point aequus::Rectangle::GetAttrPair(std::string name) {}
