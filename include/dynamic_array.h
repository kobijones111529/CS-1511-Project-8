#pragma once

#include <cstddef>
#include <utility>

template <typename T> class dynamic_array {
public:
  struct const_iterator {
    const_iterator(T const *ptr) : m_ptr(ptr) {}

    T const &operator*() const { return *m_ptr; }
    T const *operator->() const { return m_ptr; }
    const_iterator &operator++() {
      m_ptr++;
      return *this;
    }
    const_iterator operator++(int) {
      const_iterator tmp = *this;
      ++(*this);
      return tmp;
    }
    const_iterator &operator--() {
      m_ptr--;
      return *this;
    }
    const_iterator operator--(int) {
      const_iterator tmp = *this;
      --(*this);
      return tmp;
    }
    friend bool operator==(const_iterator const &a, const_iterator const &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(const_iterator const &a, const_iterator const &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend const_iterator operator+(const_iterator const &left,
                                    size_t const &right) {
      return const_iterator(left.m_ptr + right);
    }
    friend const_iterator operator-(const_iterator const &left,
                                    size_t const &right) {
      return const_iterator(left.m_ptr - right);
    }
    friend size_t operator-(const_iterator const &left,
                            const_iterator const &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    T const *m_ptr;
  };

  struct iterator {
    iterator(T *ptr) : m_ptr(ptr) {}

    operator const_iterator() const { return const_iterator(m_ptr); }

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
    friend bool operator==(iterator const &a, iterator const &b) {
      return a.m_ptr == b.m_ptr;
    }
    friend bool operator!=(iterator const &a, iterator const &b) {
      return a.m_ptr != b.m_ptr;
    }
    friend iterator operator+(iterator const &left, size_t const &right) {
      return iterator(left.m_ptr + right);
    }
    friend iterator operator-(iterator const &left, size_t const &right) {
      return iterator(left.m_ptr - right);
    }
    friend size_t operator-(iterator const &left, iterator const &right) {
      return left.m_ptr - right.m_ptr;
    }

  private:
    T *m_ptr;
  };

  dynamic_array() : m_size(0), m_capacity(0), m_buffer(nullptr) {}
  dynamic_array(dynamic_array const &x)
      : m_size(0), m_capacity(0), m_buffer(nullptr) {
    *this = x;
  }
  dynamic_array(dynamic_array &&x) noexcept
      : m_size(0), m_capacity(0), m_buffer(nullptr) {
    *this = std::move(x);
  }
  dynamic_array(std::initializer_list<T> il)
      : m_size(0), m_capacity(0), m_buffer(nullptr) {
    *this = il;
  }
  ~dynamic_array() {
    for (size_t i = 0; i < m_size; i++) {
      reinterpret_cast<T *>(m_buffer)[i].~T();
    }
    delete[] m_buffer;
  }

  dynamic_array &operator=(dynamic_array const &x) {
    for (size_t i = 0; i < m_size; i++) {
      reinterpret_cast<T *>(m_buffer)[i].~T();
    }

    if (x.m_size > m_capacity)
      reserve(x.m_size);

    for (size_t i = 0; i < x.m_size; i++) {
      new (reinterpret_cast<T *>(m_buffer) + i)
          T(reinterpret_cast<T *>(x.m_buffer)[i]);
    }

    m_size = x.m_size;
    return *this;
  }

  dynamic_array &operator=(dynamic_array &&x) noexcept {
    if (this != &x) {
      for (size_t i = 0; i < m_size; i++) {
        reinterpret_cast<T *>(m_buffer)[i].~T();
      }
      delete[] m_buffer;

      m_size = 0;
      m_capacity = 0;
      m_buffer = nullptr;

      std::swap(m_size, x.m_size);
      std::swap(m_capacity, x.m_capacity);
      std::swap(m_buffer, x.m_buffer);
    }

    return *this;
  }

  dynamic_array &operator=(std::initializer_list<T> il) {
    for (size_t i = 0; i < m_size; i++) {
      reinterpret_cast<T *>(m_buffer)[i].~T();
    }

    if (il.size() > m_capacity)
      reserve(il.size());

    for (size_t i = 0; i < il.size(); i++) {
      new (reinterpret_cast<T *>(m_buffer) + i) T(*(il.begin() + i));
    }

    m_size = il.size();
    return *this;
  }

  iterator begin() const { return iterator(reinterpret_cast<T *>(m_buffer)); }
  iterator end() const {
    return iterator(reinterpret_cast<T *>(m_buffer) + m_size);
  }
  const_iterator cbegin() const {
    return const_iterator(reinterpret_cast<T *>(m_buffer));
  }
  const_iterator cend() const {
    return const_iterator(reinterpret_cast<T *>(m_buffer) + m_size);
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

  void push_back(T const &val) {
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

  iterator erase(const_iterator pos) {
    return _erase(begin() + (pos - cbegin()));
  }

  void swap(dynamic_array &x) {
    if (this == &x)
      return;

    std::swap(m_size, x.m_size);
    std::swap(m_capacity, x.m_capacity);
    std::swap(m_buffer, x.m_buffer);
  }

  void clear() noexcept {
    for (size_t i = 0; i < m_size; i++) {
      reinterpret_cast<T *>(m_buffer)[i].~T();
    }
    m_size = 0;
  }

private:
  size_t m_size;
  size_t m_capacity;
  char *m_buffer;

  iterator _erase(iterator pos) {
    pos->~T();
    for (iterator it = pos + 1; it != end(); it++) {
      std::swap(*(it - 1), *it);
    }
    m_size--;
    return pos;
  }
};