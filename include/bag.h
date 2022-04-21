#pragma once

#include "dynamic_array.h"
#include "item.h"

#include <iostream>
#include <string>

class Bag {
public:
  int getSize() const;
  bool contains(Item const &item) const;
  bool contains(std::string const &item) const;
  int getFrequencyOf(Item const &item) const;
  int getFrequencyOf(std::string const &item) const;
  bool isEmpty() const;

  void add(Item const &item);
  void add(std::string const &item);
  bool remove(Item const &item);
  bool remove(std::string const &item);
  int removeAll(Item const &item);
  int removeAll(std::string const &item);
  void clear();
  void display() const;

private:
  dynamic_array<Item> m_items;
};