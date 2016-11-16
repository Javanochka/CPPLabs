#include "matrix.h"
#include <cstring>


Matrix::Matrix(std::size_t r, std::size_t c) {
  _rows = r;
  _cols = c;
  _data = new int*[r];
  for(std::size_t i = 0; i < r; i++) {
    _data[i] = new int[c];
    memset(_data[i], 0, c * sizeof(int));
  }
}

Matrix::Matrix(const Matrix& m) {
  _rows = m._rows;
  _cols = m._cols;
  _data = new int*[_rows];
  for(std::size_t i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
    for(std::size_t j = 0; j < _cols; j++) {
      _data[i][j] = m._data[i][j];
    }
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
  for(std::size_t i = 0; i < _rows; i++) {
    delete[] _data[i];
  }
  delete[] _data;
  _rows = m._rows;
  _cols = m._cols;
  _data = new int*[_rows];
  for(std::size_t i = 0; i < _rows; i++) {
    _data[i] = new int[_cols];
    for(std::size_t j = 0; j < _cols; j++) {
      _data[i][j] = m._data[i][j];
    }
  }
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
