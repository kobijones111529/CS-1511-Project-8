#pragma once

#include "dynamic_array.h"
#include "item.h"

#include <iostream>
#include <string>

class Bag {
public:
  int getSize() const { return m_items.size(); }
  bool contains(Item const &item) const;
  bool contains(std::string const &item) const;
  int getFrequencyOf(Item const &item) const;
  int getFrequencyOf(std::string const &item) const;
  bool isEmpty() const { return m_items.empty(); }

  void add(Item const &item);
  void add(std::string const &item) { add(Item(item)); }
  bool remove(Item const &item);
  bool remove(std::string const &item) { return remove(Item(item)); }
  int removeAll(Item const &item);
  int removeAll(std::string const &item) { return removeAll(Item(item)); }
  void clear() { m_items.clear(); }
  void display() const;

private:
  dynamic_array<Item> m_items;
};