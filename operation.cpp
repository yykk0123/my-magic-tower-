#include <cstdio>
#include <cstdlib>

#include "elements.hpp"
#include "operation.hpp"

int end = 0; // 0 for not ended, 1 for win, -1 for lose

void update_hero_location(struct player *hero) {
  // get the location of the hero originally
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      if (map[hero->lct.floor][i][j] == HERO) {
        hero->lct.y = i;
        hero->lct.x = j;
      }
}

// reset block to the origin if the block was lava, up_block or down_block
// else set it to blank block
#define move_forward()                                                         \
  {                                                                            \
    /* the block at the same location on map_original */                       \
    switch (*(current_block - map[0][0] + map_original[0][0])) {               \
    case LAVA:                                                                 \
      *current_block = LAVA;                                                   \
      break;                                                                   \
    case UP_BLOCK:                                                             \
      *current_block = UP_BLOCK;                                               \
      break;                                                                   \
    case DOWN_BLOCK:                                                           \
      *current_block = DOWN_BLOCK;                                             \
      break;                                                                   \
    default:                                                                   \
      *current_block = SPACE;                                                  \
    }                                                                          \
    *new_block = HERO;                                                         \
    hero->lct.x += dx;                                                         \
    hero->lct.y += dy;                                                         \
  }

// direction can be UP, DOWN, LEFT, or RIGHT
int move(struct player *hero, int direction) {
  int *current_block = &map[hero->lct.floor][hero->lct.y][hero->lct.x];
  int dx = (direction == LEFT) ? -1 : ((direction == RIGHT) ? 1 : 0);
  int dy = (direction == DOWN) ? 1 : ((direction == UP) ? -1 : 0);
  int *new_block = &map[hero->lct.floor][hero->lct.y + dy][hero->lct.x + dx];

  switch (*new_block) {
  case WALL: // do nothing
    break;
  case SPACE: // move forward
    move_forward();
    break;
  case LAVA: // lose 1 hp in lava
    hero->hp -= 1;
    move_forward();
    break;
  case DOOR: // move forward if have key(s), else do nothing
    if (hero->key) {
      hero->key -= 1;
      move_forward();
    }
    break;
  case UP_BLOCK: // go to up floor
    move_forward();
    hero->lct.floor += 1;
    update_hero_location(hero);
    break;
  case DOWN_BLOCK: // go to down floor
    move_forward();
    hero->lct.floor -= 1;
    update_hero_location(hero);
    break;

  case SLIME:
  case SKELETON:
  case BAT:
  case APOSTLE:
  case BEELZEBUB:
    if (battle(hero, *new_block))
      move_forward(); // defeat the monster
    break;

  case SMALL_BOTTLE:
    hero->small_bottle += 1;
    move_forward();
    break;
  case BIG_BOTTLE:
    hero->big_bottle += 1;
    move_forward();
    break;
  case SWORD:
    hero->attack += 20;
    move_forward();
    break;
  case SHIELD:
    hero->defence += 10;
    move_forward();
    break;
  case LIFE_GEM:
    hero->hp_limit += 50;
    move_forward();
    break;
  case KEY:
    hero->key += 1;
    move_forward();
    break;
  }

  return 0;
}

// use the small bottle if small==1 else big bottle
int use_bottle(struct player *hero, int small) {
  if (small) {
    if (hero->small_bottle == 0)
      return -1;
    hero->small_bottle -= 1;
    hero->hp += 10;
  } else {
    if (hero->big_bottle == 0)
      return -1;
    hero->big_bottle -= 1;
    hero->hp += 25;
  }

  if (hero->hp > hero->hp_limit)
    hero->hp = hero->hp_limit;

  return 0;
}

// fight with the monster, return 1 if win, else 0
int battle(struct player *hero, int monster_type) {

  // copy the property of monster
  struct monster mst;
  switch (monster_type) {
    // clang-format off
    case SLIME:     mst=slime;     break;
    case SKELETON:  mst=skeleton;  break;
    case BAT:       mst=bat;       break;
    case APOSTLE:   mst=apostle;   break;
    case BEELZEBUB: mst=beelzebub; break;
    // clang-format on
  }

  int attack = hero->attack - mst.defence;
  int hurt = mst.attack - hero->defence;

  // they can't hurt each other
  if (attack <= 0 && hurt <= 0)
    return 0;

  // hero can't attack monsters
  else if (attack <= 0)
    hero->hp -= hurt * ROUND;

  // monsters can't hurt hero
  else if (hurt <= 0)
    mst.hp -= attack * ROUND * (mst.SKILL == MENTAL_POLLUTION ? 2 / 3 : 1);

  // they can hurt each other
  else
    for (int round = 1; round < ROUND && hero->hp > 0 && mst.hp > 0; round++) {
      if (mst.SKILL == MENTAL_POLLUTION && round % 3 == 0)
        mst.hp += attack; // hero is interfered and can't attack monsters
      mst.hp -= attack;
      hero->hp -= hurt;
      if (mst.SKILL == BLOODSUCKING)
        mst.hp += hurt; // monsters can suck blood if have the skill
    }

  if (mst.hp <= 0) {
    hero->score += mst.score;
    if (monster_type == BEELZEBUB)
      end = 1;
    return 1; // defeat the monster
  } else if (hero->hp <= 0) {
    end = -1;
  }
  return 0;
}
