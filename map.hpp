#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <vector>

#include "elements.hpp"

class Map {
public:
  Map();
  ~Map() {}

private:
  int width;
  int height;
  std::vector<std::vector<elements>> map;
};

#endif // !_MAP_HPP_
