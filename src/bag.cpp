#include "bag.h"

bool Bag::contains(const Item &item) const {
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      return true;
  }
  return false;
}

bool Bag::contains(const std::string &item) const {
  return contains(Item(item));
}

int Bag::getFrequencyOf(const Item &item) const {
  int frequency = 0;
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      frequency++;
  }
  return frequency;
}

int Bag::getFrequencyOf(const std::string &item) const {
  return getFrequencyOf(Item(item));
}

void Bag::add(Item item) { m_items.push_back(item); }

bool Bag::remove(const Item &item) {
  auto pos = m_items.begin();
  for (; pos != m_items.end() && *pos != item; pos++) {
  }
  if (pos == m_items.end()) {
    return false;
  }
  m_items.erase(pos);
  return true;
}

int Bag::removeAll(const Item &item) {
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