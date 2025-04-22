#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <string>
#include <vector>

#include "elements.hpp"
#include "map.hpp"

using json = nlohmann::json;

Map::Map(std::string path) {
  std::map<std::string, elements> string2elements = {
      {"WALL", WALL},
      {"SPACE", SPACE},
      {"LAVA", LAVA},
      {"DOOR", DOOR},
      {"UP_BLOCK", UP_BLOCK},
      {"DOWN_BLOCK", DOWN_BLOCK},
      {"SLIME", SLIME},
      {"SKELETON", SKELETON},
      {"BAT", BAT},
      {"APOSTLE", APOSTLE},
      {"BEELZEBUB", BEELZEBUB},
      {"SMALL_BOTTLE", SMALL_BOTTLE},
      {"BIG_BOTTLE", BIG_BOTTLE},
      {"SWORD", SWORD},
      {"SHIELD", SHIELD},
      {"LIFE_GEM", LIFE_GEM},
      {"KEY", KEY},
      {"HERO", HERO},
  };

  std::ifstream file(path);
  if (!file) {
    std::cerr << "Could not open ./assets/map.json.\n";
  }

  json j;
  file >> j;

  // Read the legend
  std::map<std::string, elements> char2element;
  for (auto &[symbolStr, meaningStr] : j["legend"].items()) {
    std::string meaning = meaningStr.get<std::string>();
    char2element[symbolStr] = string2elements[meaning];
  }

  // Load data
  height = j["height"];
  width = j["width"];
  floor = j["floor"];

  // Load the map
  for (auto &[floor_num_str, floor_data] : j["floors"].items()) {
    std::vector<std::vector<elements>> mapFloor;
    for (const auto &rowStr : floor_data) {
      std::string row = rowStr.get<std::string>();
      std::vector<elements> mapRow;
      for (int i = 0; i < width * 3; i += 3) {
        mapRow.push_back(char2element[row.substr(i, 3)]);
      }
      mapFloor.push_back(mapRow);
    }
    map.push_back(mapFloor);
  }

  //   // Print the map
  //   for (const auto &floor : map) {
  //     for (auto &row : floor) {
  //       for (auto &tile : row)
  //         std::cout << tile;
  //       std::cout << "\n";
  //     }
  //     std::cout << "\n";
  //   }
}
