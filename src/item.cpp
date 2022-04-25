#include "item.h"

Item::Item(std::string const &name) : m_name(name) {}
Item::Item(char const *name) : m_name(name) {}

std::string Item::getName() const { return m_name; }

int Item::compare(Item const &other) const {
  return m_name.compare(other.m_name);
}

bool operator==(Item const &left, Item const &right) {
  return left.compare(right) == 0;
}
bool operator!=(Item const &left, Item const &right) {
  return left.compare(right) != 0;
}