#ifndef _ELEMENTS_HPP_
#define _ELEMENTS_HPP_

#include "monster.hpp"

extern Monster slime, skeleton, bat, apostle, beelzebub;

// 0为墙 1为空地 2为岩浆 3为门 4为上层块 5为下层块
// 6 为史莱姆 7为骷髅 8为蝙蝠 9为使徒 10为魔王
// 11为小血瓶 12为大血瓶 13为剑 14为盾 15为生命宝石 16为钥匙
// 17为勇士
enum elements {
  WALL = 0,
  SPACE,
  LAVA,
  DOOR,
  UP_BLOCK,
  DOWN_BLOCK,
  SLIME,
  SKELETON,
  BAT,
  APOSTLE,
  BEELZEBUB,
  SMALL_BOTTLE,
  BIG_BOTTLE,
  SWORD,
  SHIELD,
  LIFE_GEM,
  KEY,
  HERO,
};

#endif // _ELEMENTS_HPP_
