#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <stdexcept>
#include <string>
#include <vector>

#include "elements.hpp"
#include "map.hpp"

using json = nlohmann::json;

Map::Map(std::string path) {
  const std::map<std::string, elements> string2elements = {
      {"HERO", HERO},
      {"WALL", WALL},
      {"SPACE", SPACE},
      {"STONE_DOOR", STONE_DOOR},
      {"IRON_DOOR", IRON_DOOR},
      {"CRYSTAL_DOOR", CRYSTAL_DOOR},
      {"REBORN_POINT", REBORN_POINT},
      {"IRON_FENCE", IRON_FENCE},
      {"UPSTAIR", UPSTAIR},
      {"DOWNSTAIR", DOWNSTAIR},
      {"LAVA", LAVA},
      {"BOOM", BOOM},
      {"SWORD_FRONT_WAND", SWORD_FRONT_WAND},
      {"PLATFORM", PLATFORM},
      {"STAR", STAR},
      {"STONE_KEY", STONE_KEY},
      {"IRON_KEY", IRON_KEY},
      {"CRYSTAL_KEY", CRYSTAL_KEY},
      {"HEALTH_BOTTLE", HEALTH_BOTTLE},
      {"BLUE_BOTTLE", BLUE_BOTTLE},
      {"HEALTH_CRYSTAL", HEALTH_CRYSTAL},
      {"BLUE_CRYSTAL", BLUE_CRYSTAL},
      {"ORB_OF_HERO", ORB_OF_HERO},
      {"ORB_OF_WISDOM", ORB_OF_WISDOM},
      {"ORB_OF_FLYING", ORB_OF_FLYING},
      {"CROSS", CROSS},
      {"SAINT_WATER", SAINT_WATER},
      {"MAGIC_MATTOCK", MAGIC_MATTOCK},
      {"DESTURCTION_BOMB", DESTURCTION_BOMB},
      {"WING_GREEN", WING_GREEN},
      {"WING_BLUE", WING_BLUE},
      {"WING_RED", WING_RED},
      {"DRAGON_SLAYER", DRAGON_SLAYER},
      {"FROZEN_MARKER", FROZEN_MARKER},
      {"SUPER_KEY", SUPER_KEY},
      {"SUPER_MAGIC_MATTOCK", SUPER_MAGIC_MATTOCK},
      {"LUCKY_COIN", LUCKY_COIN},
      {"SLIME_GREEN", SLIME_GREEN},
      {"SLIME_RED", SLIME_RED},
      {"SLIME_BLACK", SLIME_BLACK},
      {"BAT_BABY", BAT_BABY},
      {"MAGE_BLUE", MAGE_BLUE},
      {"MAGE_RED", MAGE_RED},
      {"FIGHTER_YELLOW", FIGHTER_YELLOW},
      {"FIGHTER_BLUE", FIGHTER_BLUE},
      {"SKELETON", SKELETON},
      {"SKELETON_WARRIOR", SKELETON_WARRIOR},
      {"SKELETON_CAPTAIN", SKELETON_CAPTAIN},
      {"BAT", BAT},
      {"DEAD_BODY", DEAD_BODY},
      {"DEAD_SOILDER", DEAD_SOILDER},
      {"STONE_FACE", STONE_FACE},
      {"APOSTLE_RED", APOSTLE_RED},
      {"APOSTLE_BLUE", APOSTLE_BLUE},
      {"VAMPIRE", VAMPIRE},
      {"OCTOPUS_1", OCTOPUS_1},
      {"OCTOPUS_2", OCTOPUS_2},
      {"OCTOPUS_3", OCTOPUS_3},
      {"OCTOPUS_4", OCTOPUS_4},
      {"OCTOPUS_5", OCTOPUS_5},
      {"OCTOPUS_6", OCTOPUS_6},
      {"OCTOPUS_7", OCTOPUS_7},
      {"OCTOPUS_8", OCTOPUS_8},
      {"OCTOPUS_9", OCTOPUS_9},
      {"DRAGON_1", DRAGON_1},
      {"DRAGON_2", DRAGON_2},
      {"DRAGON_3", DRAGON_3},
      {"DRAGON_4", DRAGON_4},
      {"DRAGON_5", DRAGON_5},
      {"DRAGON_6", DRAGON_6},
      {"DRAGON_7", DRAGON_7},
      {"DRAGON_8", DRAGON_8},
      {"DRAGON_9", DRAGON_9},
      {"KNIGHT_YELLOW", KNIGHT_YELLOW},
      {"KNIGHT_RED", KNIGHT_RED},
      {"KNIGHT_CAPTAIN", KNIGHT_CAPTAIN},
      {"SAINT_KNIGHT", SAINT_KNIGHT},
      {"SKELETON_KNIGHT", SKELETON_KNIGHT},
      {"SLIME_MAN", SLIME_MAN},
      {"DARK_MAGE", DARK_MAGE},
      {"BAT_VAMPIRE", BAT_VAMPIRE},
      {"SLIME_KING", SLIME_KING},
      {"WIZARD_RED", WIZARD_RED},
      {"WIZARD_YELLOW", WIZARD_YELLOW},
      {"DARK_KNIGHT", DARK_KNIGHT},
      {"BIG_MUSCLE", BIG_MUSCLE},
      {"BEELZEBUB", BEELZEBUB},
      {"DRAK_HERO", DRAK_HERO},
      {"GOLEM_1", GOLEM_1},
      {"GOLEM_2", GOLEM_2},
      {"GOLEM_3", GOLEM_3},
      {"MERCHANT", MERCHANT},
      {"THIEF", THIEF},
      {"FAIRY", FAIRY},
      {"PRIEST", PRIEST},
      {"GODDESS", GODDESS},
      {"SWORD", SWORD},
      {"IRON_SWORD", IRON_SWORD},
      {"HERO_SWORD", HERO_SWORD},
      {"SAINT_SWORD", SAINT_SWORD},
      {"EXCALIBUR", EXCALIBUR},
      {"SHIELD", SHIELD},
      {"IRON_SHIELD", IRON_SHIELD},
      {"HERO_SHILED", HERO_SHILED},
      {"SAINT_SHIELD", SAINT_SHIELD},
      {"MAGIC_SHILED", MAGIC_SHILED},
      {"STONE_KEY_STICKER", STONE_KEY_STICKER},
      {"IRON_KEY_STICKER", IRON_KEY_STICKER},
      {"CRYSTAL_KEY_STICKER", CRYSTAL_KEY_STICKER},
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
    auto elementIt = string2elements.find(meaning);
    if (elementIt == string2elements.end())
      throw std::runtime_error("Unknown map element: " + meaning);

    // Map symbols are two characters; JSON legend keys may include a trailing
    // space only to match the old fixed-width parser.
    char2element.emplace(symbolStr.substr(0, 2), elementIt->second);
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
      for (int column = 0; column < width; ++column) {
        const std::string symbol = row.substr(column * 3, 2);
        auto symbolIt = char2element.find(symbol);
        if (symbolIt == char2element.end())
          throw std::runtime_error("Unknown map symbol: '" + symbol + "'");
        mapRow.push_back(symbolIt->second);
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
