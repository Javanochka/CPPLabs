#include "matrix.h"
#include <cstring>
#include <algorithm>

Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new int*[r];
  for(std::size_t i = 0; i < r; i++) {
    _data[i] = new int[c]();
  }
}

Matrix::Matrix(const Matrix& m) {
  _rows = m._rows;
  _cols = m._cols;
  _data = new int*[_rows];
  for(std::size_t i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
    memcpy(_data[i], m._data[i], sizeof(int)*_cols);
  }
}

Matrix::~Matrix() {
  for(std::size_t i = 0; i < _rows; i++) {
    delete[] _data[i];
  }
  delete[] _data;
}

std::size_t Matrix::get_rows() const {
  return _rows;
}
std::size_t Matrix::get_cols() const {
  return _cols;
}

void Matrix::set(std::size_t i, std::size_t j, int val) {
  _data[i][j] = val;
}

int Matrix::get(std::size_t i, std::size_t j) const {
  return _data[i][j];
}

void Matrix::print(FILE* f) const {
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < _cols; j++) {
      fprintf(f, "%d ", _data[i][j]);
    }
    fprintf(f, "\n");
  }
}

Matrix& Matrix::operator=(const Matrix& m) {
  if(this == &m) return *this;
  Matrix temp(m);
  std::swap(_cols, temp._cols);
  std::swap(_rows, temp._rows);
  std::swap(temp._data, _data);
  return *this;
}

bool Matrix::operator==(const Matrix& m) const {
  if(_rows != m._rows || _cols != m._cols) return false;
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < _cols; j++) {
      if(_data[i][j] != m._data[i][j]) return false;
    }
  }
  return true;
}

bool Matrix::operator!=(const Matrix& m) const {
  return !(*this == m);
}

Matrix& Matrix::operator+=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < _cols; j++) {
      _data[i][j] += m._data[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator-=(const Matrix& m) {
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < _cols; j++) {
      _data[i][j] -= m._data[i][j];
    }
  }
  return *this;
}

Matrix& Matrix::operator*=(const Matrix& m) {
  (*this) = (*this) * m;
  return *this;
}

Matrix Matrix::operator+(const Matrix& m) const {
  Matrix res = *this;
  res += m;
  return res;
}

Matrix Matrix::operator-(const Matrix& m) const {
  Matrix res = *this;
  res -= m;
  return res;
}

Matrix Matrix::operator*(const Matrix& m) const {
  Matrix res(_rows, m._cols);
  for(std::size_t i = 0; i < _rows; i++) {
    for(std::size_t j = 0; j < m._cols; j++) {
      for(std::size_t k = 0; k < _cols; k++) {
        res._data[i][j] += _data[i][k] * m._data[k][j];
      } 
    }
  }
  return res;
}
