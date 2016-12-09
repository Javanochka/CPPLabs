#include "rectangle.h"
#include <string.h>
#include <cstdio>
#include <algorithm>

Rectangle::Rectangle(int id, int x, int y, int width, int height) : Figure(id, x, y) {
  width_ = width;
  height_ = height;
}

Rectangle::~Rectangle() {}

void Rectangle::print() const {
  printf("Rectangle %d: x = %d y = %d width = %d height = %d\n", id_, x_, y_, width_, height_);
}

bool Rectangle::is_inside(int x, int y) const {
  return (2*abs(x-x_) <= width_ && 2*abs(y-y_) <= height_);
}

void Rectangle::zoom(int factor) {
  width_ *= factor;
  height_ *= factor;
}
