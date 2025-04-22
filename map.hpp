#ifndef _MAP_HPP_
#define _MAP_HPP_

#include <string>
#include <vector>

#include "elements.hpp"

class Map {
public:
  Map() {};
  Map(std::string path);
  Map &operator=(const Map &other) = default;
  ~Map() {}

  int getWidth() { return width; }
  int getHeight() { return height; }
  elements getCell(int w, int h, int floor) { return map[floor][h][w]; }
  void setCell(int w, int h, int floor, elements ele) {
    map[floor][h][w] = ele;
  }

private:
  int width;
  int height;
  int floor;
  std::vector<std::vector<std::vector<elements>>> map;
};

#endif // !_MAP_HPP_
