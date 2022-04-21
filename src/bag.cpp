#include "bag.h"

bool Bag::contains(Item const &item) const {
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      return true;
  }
  return false;
}

bool Bag::contains(std::string const &item) const {
  return contains(Item(item));
}

int Bag::getFrequencyOf(Item const &item) const {
  int frequency = 0;
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      frequency++;
  }
  return frequency;
}

int Bag::getFrequencyOf(std::string const &item) const {
  return getFrequencyOf(Item(item));
}

void Bag::add(Item const &item) { m_items.push_back(item); }

bool Bag::remove(Item const &item) {
  auto pos = m_items.begin();
  for (; pos != m_items.end() && *pos != item; pos++) {
  }
  if (pos == m_items.end()) {
    return false;
  }
  m_items.erase(pos);
  return true;
}

int Bag::removeAll(Item const &item) {
  int found = 0;
  for (auto it = m_items.begin(); it != m_items.end();) {
    if (*it == item) {
      m_items.erase(it);
      found++;
    } else {
      it++;
    }
  }

  return found;
}

void Bag::display() const {
  std::cout << "Bag items:" << std::endl;
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    std::cout << '\t' << it->getName() << std::endl;
  }
}