#pragma once

#include <string>

class Item {
public:
  Item(std::string name) : m_name(name) {}

  std::string getName() const { return m_name; }
  int compare(const Item &other) const { return m_name.compare(other.m_name); }

  operator std::string() const { return m_name; }
  friend bool operator==(const Item &left, const Item &right) {
    return left.compare(right) == 0;
  }
  friend bool operator!=(const Item &left, const Item &right) {
    return left.compare(right) != 0;
  }

private:
  std::string m_name;
};