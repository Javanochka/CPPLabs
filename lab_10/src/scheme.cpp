#include "scheme.h"
#include <utility>
#include <cstdio>
#include <cstddef>

Scheme::Scheme(int capacity) {
  cap_ = capacity;
  size_ = 0;
  figures_ = new Figure*[cap_];
}

Scheme::~Scheme() {
  for(int i = 0; i < size_; i++) {
    delete figures_[i];
  }
  delete [] figures_;
}

void Scheme::push_back_figure(Figure* fg) {
  if(size_ + 1 == cap_) {
    printf("Sorry, I can't pushback a figure.\n");
    return;
  }
  figures_[size_++] = fg;
}

void Scheme::remove_figure(int id) {
  for(int i = 0; i < size_; i++) {
    if(figures_[i]->get_id() == id) {
      for(int j = i + 1; j < size_; j++) {
        std::swap(figures_[j], figures_[j-1]);
      }
      delete figures_[size_-1];
      size_--;
      return;
    }
  }
}

void Scheme::print_all_figures() const {
  for(int i = 0; i < size_; i++) {
    figures_[i]->print();
  }
}

void Scheme::zoom_figure(int id, int factor) {
  for(int i = 0; i < size_; i++) {
    if(figures_[i]->get_id() == id) {
      figures_[i]->zoom(factor);
      return;
    }
  }
}

Figure* Scheme::is_inside_figure(int x, int y) const {
  for(int i = 0; i < size_; i++) {
    if(figures_[i]->is_inside(x, y)) {
      return figures_[i];
    }
  }
  return NULL;
}

void Scheme::move(int id, int new_x, int new_y) {
  for(int i = 0; i < size_; i++) {
    if(figures_[i]->get_id() == id) {
      figures_[i]->move(new_x, new_y);
      return;
    }
  }
}
