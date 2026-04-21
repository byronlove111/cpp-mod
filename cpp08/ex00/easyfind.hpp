#ifndef EASYFIND_HPP
#define EASYFIND_HPP

#include <algorithm>
#include <stdexcept>

template <typename T>
int easyfind(const T &container, int value) {
  typename T::const_iterator it = std::find(container.begin(), container.end(), value);
  if (it == container.end()) {
    throw std::out_of_range("Value not found");
  }
  return *it;
}

#endif
