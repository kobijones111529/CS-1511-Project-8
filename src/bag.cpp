#include "bag.h"

int Bag::getSize() const { return m_items.size(); }

bool Bag::contains(Item const &item) const {
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      return true;
  }
  return false;
}

int Bag::getFrequencyOf(Item const &item) const {
  int frequency = 0;
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item)
      frequency++;
  }
  return frequency;
}

bool Bag::isEmpty() const { return m_items.empty(); }

void Bag::add(Item const &item) { m_items.push_back(item); }

bool Bag::remove(Item const &item) {
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    if (*it == item) {
      m_items.erase(it);
      return true;
    }
  }
  return false;
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

void Bag::clear() { m_items.clear(); }

void Bag::display() const {
  std::cout << "Bag items:" << std::endl;
  for (auto it = m_items.begin(); it != m_items.end(); it++) {
    std::cout << '\t' << it->getName() << std::endl;
  }
}