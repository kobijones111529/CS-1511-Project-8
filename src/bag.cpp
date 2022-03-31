#include "bag.h"

bool Bag::contains(const Item &item) const {
  return std::find(m_items.begin(), m_items.end(), item) != m_items.end();
}

bool Bag::contains(const std::string &item) const {
  return contains(Item(item));
}

int Bag::getFrequencyOf(const Item &item) const {
  return std::count(m_items.begin(), m_items.end(), item);
}

int Bag::getFrequencyOf(const std::string &item) const {
  return getFrequencyOf(Item(item));
}

bool Bag::remove(const Item &item) {
  auto it = std::find(m_items.begin(), m_items.end(), item);
  if (it == m_items.end())
    return false;
  m_items.erase(it);
  return true;
}

void Bag::display() const {
  std::cout << "Bag items:" << std::endl;
  for (const Item &item : m_items) {
    std::cout << '\t' << item.getName() << std::endl;
  }
}