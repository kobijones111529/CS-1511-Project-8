#pragma once

#include <memory>

template <typename T> class dynamic_array {
public:
  struct iterator {
    iterator(T *ptr) : m_ptr(ptr) {}

    T &operator*() const { return *m_ptr; }
    T *operator->() const { return m_ptr; }
    iterator &operator++() {
      m_ptr++;
      return *this;
    }
    iterator operator++(int) {
      iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    iterator &operator--() {
      m_ptr--;
      return *this;
    }
    iterator operator--(int) {
      iterator tmp = *this;
      --(*this);
      return tmp;
    }
    friend bool operator==(const iterator &a, const iterator &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const iterator &a, const iterator &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend iterator operator+(const iterator &left, const size_t &right) {
      return iterator(left.m_ptr + right);
    }
    friend iterator operator-(const iterator &left, const size_t &right) {
      return iterator(left.m_ptr - right);
    }
    friend size_t operator-(const iterator &left, const iterator &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    T *m_ptr;
  };

  dynamic_array() : m_size(0), m_capacity(0), m_buffer(nullptr) {}
  ~dynamic_array() {
    for (iterator it = begin(); it != end(); it++) {
      it->~T();
    }
    delete[] m_buffer;
  }

  iterator begin() const { return iterator(reinterpret_cast<T *>(m_buffer)); }
  iterator end() const {
    return iterator(reinterpret_cast<T *>(m_buffer) + m_size);
  }

  size_t size() const noexcept { return m_size; }
  size_t capacity() const noexcept { return m_capacity; }
  bool empty() const noexcept { return m_size == 0; }
  void reserve(size_t n) {
    if (n <= m_size)
      return;

    char *newBuffer = new char[n * sizeof(T)];
    for (size_t i = 0; i < m_size; i++) {
      new (reinterpret_cast<T *>(newBuffer) + i)
          T(reinterpret_cast<T *>(m_buffer)[i]);
    }
    delete[] m_buffer;
    m_buffer = newBuffer;
    m_capacity = n;
  }

  T &operator[](size_t index) {
    return *(reinterpret_cast<T *>(m_buffer) + index);
  }
  const T &operator[](size_t index) const {
    return *(reinterpret_cast<T *>(m_buffer) + index);
  }

  void push_back(const T &val) {
    if (m_size >= m_capacity)
      reserve(m_size * 2 + 1);

    new (reinterpret_cast<T *>(m_buffer) + m_size) T(val);
    m_size++;
  }

  void push_back(T &&val) {
    if (m_size >= m_capacity)
      reserve(m_size * 2 + 1);

    new (reinterpret_cast<T *>(m_buffer) + m_size) T(val);
    m_size++;
  }

  iterator erase(const iterator pos) {
    pos->~T();
    for (iterator it = pos + 1; it != end(); it++) {
      std::swap(*(it - 1), *it);
    }
    m_size--;
    return pos;
  }

  void clear() noexcept {
    for (iterator it = begin(); it != end(); it++) {
      it->~T();
    }
    m_size = 0;
  }

private:
  size_t m_size;
  size_t m_capacity;
  char *m_buffer;
};