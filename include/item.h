#pragma once

#include <string>

class Item {
public:
  Item(std::string const &name);

  std::string getName() const;
  int compare(Item const &other) const;

  friend bool operator==(Item const &left, Item const &right);
  friend bool operator!=(Item const &left, Item const &right);

private:
  std::string m_name;
};