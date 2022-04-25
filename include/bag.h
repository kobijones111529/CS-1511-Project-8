#pragma once

#include "dynamic_array.h"
#include "item.h"

#include <iostream>
#include <string>

class Bag {
public:
  int getSize() const;
  bool contains(Item const &item) const;
  int getFrequencyOf(Item const &item) const;
  bool isEmpty() const;

  void add(Item const &item);
  bool remove(Item const &item);
  int removeAll(Item const &item);
  void clear();
  void display() const;

private:
  dynamic_array<Item> m_items;
};