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

  /**
   * @brief Add item to bag
   *
   * @param item Item to add
   */
  void add(Item const &item);
  /**
   * @brief Remove first occurance of item from bag
   * 
   * @param item Item to remove
   * @return True if item was removed
   */
  bool remove(Item const &item);
  /**
   * @brief Remove all occurances of item from bag
   * 
   * @param item Item to remove
   * @return Number of items removed
   */
  int removeAll(Item const &item);
  void clear();
  /**
   * @brief Print bag contents to cout
   */
  void display() const;

private:
  dynamic_array<Item> m_items;
};