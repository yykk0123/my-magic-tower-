#ifndef _ELEMENTS_HPP_
#define _ELEMENTS_HPP_

#include <string>

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

extern struct player hero;

struct monster {
  int hp;
  int attack;
  int defence;
  int score;
  int SKILL;
};

enum skill {
  NONE,
  BLOODSUCKING,
  MENTAL_POLLUTION,
};

extern struct monster slime, skeleton, bat, apostle, beelzebub;

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

// map size and layers
#define WIDTH 10
#define HEIGHT 10
#define LAYERS 2

extern int map_original[LAYERS][HEIGHT][WIDTH], map[LAYERS][HEIGHT][WIDTH];

#endif // _ELEMENTS_HPP_
