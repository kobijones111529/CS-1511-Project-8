#pragma once

#include "dynamic_array.h"
#include "item.h"

#include <iostream>
#include <memory>
#include <new>
#include <string>

class Bag {
public:
  int getSize() const { return m_items.size(); }
  bool contains(const Item &item) const;
  bool contains(const std::string &item) const;
  int getFrequencyOf(const Item &item) const;
  int getFrequencyOf(const std::string &item) const;
  bool isEmpty() const { return m_items.empty(); }

  void add(Item item);
  void add(std::string item) { add(Item(item)); }
  bool remove(const Item &item);
  bool remove(const std::string &item) { return remove(Item(item)); }
  int removeAll(const Item &item);
  int removeAll(const std::string &item) { return removeAll(Item(item)); }
  void clear() { m_items.clear(); }
  void display() const;

private:
  dynamic_array<Item> m_items;
};