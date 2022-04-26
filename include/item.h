#pragma once

#include <string>

class Item {
public:
  Item(std::string const &name);
  Item(char const *name);

  std::string getName() const;
  /**
   * @brief Compare with other item
   *
   * @param other Item to compare with
   * @return -1 if this precedes other alphabetically; 1 if other item
   * precedes this; 0 if items are equal
   */
  int compare(Item const &other) const;

  friend bool operator==(Item const &left, Item const &right);
  friend bool operator!=(Item const &left, Item const &right);

private:
  std::string m_name;
};