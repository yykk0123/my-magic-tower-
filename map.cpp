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

Map::Map() {
  std::ifstream file("./assets/map.json");
  if (!file) {
    std::cerr << "Could not open ./assets/map.json.\n";
  }

  json j;
  file >> j;

  // Read the legend
  std::map<char, elements> char2element;
  for (auto &[symbolStr, meaningStr] : j["legend"].items()) {
    char symbol = symbolStr[0];
    std::string meaning = meaningStr.get<std::string>();
    char2element[symbol] = string2elements[meaning];
  }

  // Load data
  height = j["height"];
  width = j["width"];

  // Load the map
  for (const auto &rowStr : j["tiles"]) {
    std::string row = rowStr.get<std::string>();
    std::vector<elements> mapRow;
    for (auto ch : row) {
      mapRow.push_back(char2element[ch]);
    }
    map.push_back(mapRow);
  }

  std::cout << height << " " << width << "\n";
  // // Print the map
  // for (const auto &row : map) {
  //   for (auto tile : row) {
  //     std::cout << tile;
  //   }
  //   std::cout << "\n";
  // }
}
