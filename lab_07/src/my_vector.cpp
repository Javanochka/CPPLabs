#include "my_vector.h"
#include <cassert>
#include <algorithm>
#include <cstring>

MyVector::MyVector() {
  _sz = 0;
  _cp = 2;
  _data = new int[_cp];
}

MyVector::MyVector(std:: size_t init_capacity) {
  _sz = 0;
  _cp = init_capacity;
  assert (_cp > 0 && "init_capacity should be at list 1");
  _data = new int[_cp];
}

MyVector::~MyVector() {
  delete []_data;
}

void MyVector::set(std::size_t index, int value) {
  assert ((index >= 0 && index < _sz) && "Index out of range");
  _data[index] = value;
}

int MyVector::get(std::size_t index) {
  assert ((index >= 0 && index < _sz) && "Index out of range");
  return _data[index];
}

std::size_t MyVector::size() {
  return _sz;
}

std::size_t MyVector::capacity() {
  return _cp;
}

void MyVector::reserve(std::size_t new_capacity) {
  if (new_capacity <= _cp) return;
  int *t_data = new int[new_capacity];
  memcpy(t_data, _data, _cp * sizeof(int));
  delete []_data;
  _data = t_data;
  _cp = new_capacity;
}

void MyVector::resize(std::size_t new_size) {
  if (_sz >= new_size) {
    _sz = new_size;
    return;
  }
  if (_cp < new_size) {
    std::size_t new_cp = _cp;
    while (new_cp < new_size) {
      new_cp *= 2;
    }
    reserve(new_cp);
  }
  memset(_data + _sz, 0, (new_size - _sz)*sizeof(int));
  _sz = new_size;
}

void MyVector::push_back(int value) {
  if (_sz == _cp) {
    reserve(_cp * 2);
  }
  _data[_sz++] = value;
}

void MyVector::insert(std::size_t index, int value) {
  assert ((index >= 0 && index <= _sz) && "Index out of range");
  push_back(0);
  std::move(_data+index, _data+_sz-1, _data+index+1);
  _data[index] = value;
}

void MyVector::erase(std::size_t index) {
  assert ((index >= 0 && index < _sz) && "Index out of range");
  std::move(_data+index+1, _data+_sz, _data+index);
  _sz--;
}
