#pragma once

#include <cstddef>
#include <iostream>
#include <memory>

template <typename T> class dynamic_array {
public:
  struct ConstIterator {
    ConstIterator(const T *ptr) : m_ptr(ptr) {}

    const T &operator*() const { return *m_ptr; }
    const T *operator->() const { return m_ptr; }

    friend bool operator==(const ConstIterator &a, const ConstIterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const ConstIterator &a, const ConstIterator &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend ConstIterator operator+(const ConstIterator &left,
                                   const size_t &right) {
      return ConstIterator(left.m_ptr + right);
    }
    friend ConstIterator operator-(const ConstIterator &left,
                                   const size_t &right) {
      return ConstIterator(left.m_ptr + right);
    }
    friend size_t operator-(const ConstIterator &left,
                            const ConstIterator &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    const T *m_ptr;
  };

  struct Iterator {
    Iterator(T *ptr) : m_ptr(ptr) {}

    operator ConstIterator() const { return ConstIterator(m_ptr); }

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    Iterator &operator++() {
      m_ptr++;
      return *this;
    }
    Iterator operator++(int) {
      Iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    Iterator &operator--() {
      m_ptr--;
      return *this;
    }
    Iterator operator--(int) {
      Iterator tmp = *this;
      --(*this);
      return tmp;
    }
    friend bool operator==(const Iterator &a, const Iterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const Iterator &a, const Iterator &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend Iterator operator+(const Iterator &left, const size_t &right) {
      return Iterator(left.m_ptr + right);
    }
    friend Iterator operator-(const Iterator &left, const size_t &right) {
      return Iterator(left.m_ptr + right);
    }
    friend size_t operator-(const Iterator &left, const Iterator &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    T *m_ptr;
  };

  dynamic_array() : m_size(0), m_buffer(nullptr) {}
  ~dynamic_array() {
    for (auto it = begin(); it != end(); it++) {
      it->~T();
    }
    delete[] m_buffer;
  }

  Iterator begin() const { return Iterator(reinterpret_cast<T *>(m_buffer)); }
  Iterator end() const {
    return Iterator(reinterpret_cast<T *>(m_buffer) + m_size);
  }

  size_t size() const noexcept { return m_size; }
  bool empty() const noexcept { return m_size == 0; }

  T &operator[](size_t index) { return *(begin() + index); }
  const T &operator[](size_t index) const { return *(begin() + index); }

  void push_back(const T &val) {
    char *newBuffer = new char[(m_size + 1) * sizeof(T)];
    T *oldArray = reinterpret_cast<T *>(m_buffer);
    T *newArray = reinterpret_cast<T *>(newBuffer);
    for (size_t i = 0; i < m_size; i++) {
      new (newArray + i) T(*(oldArray + i));
    }
    new (newArray + m_size) T(val);
    if (oldArray != nullptr) {
      for (size_t i = 0; i < m_size; i++) {
        (oldArray + i)->~T();
      }
    }
    if (m_buffer != nullptr) {
      delete[] m_buffer;
    }
    m_buffer = newBuffer;
    m_size++;
  }

  void push_back(T &&val) {
    char *newBuffer = new char[(m_size + 1) * sizeof(T)];
    T *oldArray = reinterpret_cast<T *>(m_buffer);
    T *newArray = reinterpret_cast<T *>(newBuffer);
    for (size_t i = 0; i < m_size; i++) {
      new (newArray + i) T(*(oldArray + i));
    }
    new (newArray + m_size) T(val);
    if (oldArray != nullptr) {
      for (size_t i = 0; i < m_size; i++) {
        (oldArray + i)->~T();
      }
    }
    if (m_buffer != nullptr) {
      delete[] m_buffer;
    }
    m_buffer = newBuffer;
    m_size++;
  }

  Iterator erase(ConstIterator pos) {
    char *newBuffer = new char[(m_size - 1) * sizeof(T)];
    T *oldArray = reinterpret_cast<T *>(m_buffer);
    T *newArray = reinterpret_cast<T *>(newBuffer);
    Iterator returnIt(nullptr);
    for (auto oldIt = begin(), newIt = Iterator(newArray); oldIt != end();
         oldIt++) {
      if (oldIt != pos) {
        new (std::addressof(*newIt)) T(*oldIt);
        newIt++;
      } else {
        returnIt = newIt;
      }
    }
    if (oldArray != nullptr) {
      for (size_t i = 0; i < m_size; i++) {
        (oldArray + i)->~T();
      }
    }
    if (m_buffer != nullptr) {
      delete[] m_buffer;
    }
    m_buffer = newBuffer;
    m_size--;
    return returnIt;
  }

  void clear() noexcept {
    for (auto it = begin(); it != end(); it++) {
      it->~T();
    }
    delete[] m_buffer;
    m_buffer = nullptr;
    m_size = 0;
  }

private:
  size_t m_size;
  char *m_buffer;
};