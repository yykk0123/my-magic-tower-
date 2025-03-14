#ifndef _ELEMENTS_CPP_
#define _ELEMENTS_CPP_

#include <string>

// map size and layers
#define WIDTH 10
#define HEIGHT 10
#define LAYERS 2

struct player {
  std::string name;
  int hp;
  int hp_limit;
  int defence;
  int attack;
  int score;
  int key;
  int small_bottle;
  int big_bottle;
  struct location {
    int x;
    int y;
    int floor;
  } lct;
};
struct player hero = {
    "", // name
    50, // hp
    50, // hp_limit
    5,  // attack
    20, // defence
};

enum skill {
  NONE,
  BLOODSUCKING,
  MENTAL_POLLUTION,
};

struct monster {
  int hp;
  int attack;
  int defence;
  int score;
  int SKILL;
};

struct monster slime = {10, 5, 5, 5, NONE};
struct monster skeleton = {16, 8, 8, 8, NONE};
struct monster bat = {25, 15, 0, 10, BLOODSUCKING};
struct monster apostle = {50, 30, 15, 25, MENTAL_POLLUTION};
struct monster beelzebub = {100, 25, 15, 100, NONE};

// 0为墙 1为空地 2为岩浆 3为门 4为上层块 5为下层块
// 6 为史莱姆 7为骷髅 8为蝙蝠 9为使徒 10为魔王
// 11为小血瓶 12为大血瓶 13为剑 14为盾 15为生命宝石 16为钥匙
// 104为勇士
enum elements {
  WALL = 0,
  SPACE = 1,
  LAVA = 2,
  DOOR = 3,
  UP_BLOCK = 4,
  DOWN_BLOCK = 5,
  SLIME = 6,
  SKELETON = 7,
  BAT = 8,
  APOSTLE = 9,
  BEELZEBUB = 10,
  SMALL_BOTTLE = 11,
  BIG_BOTTLE = 12,
  SWORD = 13,
  SHIELD = 14,
  LIFE_GEM = 15,
  KEY = 16,
  HERO = 104,
};

int map_original[LAYERS][HEIGHT][WIDTH] = {
    // clang-format off
    {
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 104, 1, 2, 11, 12, 13, 14, 15, 0,
        0, 1,   4, 9, 8,  7,  6,  3,  16, 0,
        0, 10,  0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
    },
    {
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 104, 1, 1, 1, 10, 0, 0, 0, 0,
        0, 5,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
    },
};

int map[LAYERS][HEIGHT][WIDTH] = {}; // will copy from map_original in `initialize()`

#endif // _ELEMENTS_CPP_
