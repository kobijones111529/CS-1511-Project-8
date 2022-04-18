#pragma once

#include <iostream>
#include <string>

class Item {
public:
  Item(std::string name) : m_name(name) {}
  ~Item() = default;

  std::string getName() const { return m_name; }
  int compare(const Item &other) const { return m_name.compare(other.m_name); }

  friend bool operator==(const Item &left, const Item &right) {
    return left.compare(right) == 0;
  }
  friend bool operator!=(const Item &left, const Item &right) {
    return left.compare(right) != 0;
  }

private:
  std::string m_name;
};