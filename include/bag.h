#pragma once

#include "item.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

class Bag {
public:
  int getSize() const { return m_items.size(); }
  bool contains(const Item &item) const;
  bool contains(const std::string &item) const;
  int getFrequencyOf(const Item &item) const;
  int getFrequencyOf(const std::string &item) const;
  bool isEmpty() { return m_items.empty(); }

  void add(Item item) { m_items.push_back(item); }
  void add(std::string item) { add(Item(item)); }
  bool remove(const Item &item);
  bool remove(const std::string &item) { return remove(Item(item)); }
  void clear() { m_items.clear(); }
  void display() const;

private:
  std::vector<Item> m_items;
};