#include "operation.hpp"
#include "elements.hpp"
#include "global.hpp"
#include "map.hpp"

// reset block to the origin if the block was lava, up_block or down_block
// else set it to blank block
#define _move_forward()                                                        \
  {                                                                            \
    /* the block at the same location on map_original */                       \
    switch (map_original.getCell(hero.getX(), hero.getY(), hero.getFloor())) { \
    case LAVA:                                                                 \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), LAVA);            \
      break;                                                                   \
    case UP_BLOCK:                                                             \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), UP_BLOCK);        \
      break;                                                                   \
    case DOWN_BLOCK:                                                           \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), DOWN_BLOCK);      \
      break;                                                                   \
    default:                                                                   \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), SPACE);           \
    }                                                                          \
    hero.setX(hero.getX() + dx);                                               \
    hero.setY(hero.getY() + dy);                                               \
    map.setCell(hero.getX(), hero.getY(), hero.getFloor(), HERO);              \
  }

int move(Direction dir) {
  int dx = (dir == RIGHT) - (dir == LEFT);
  int dy = (dir == DOWN) - (dir == UP);
  elements current_block =
      map.getCell(hero.getX(), hero.getY(), hero.getFloor());
  elements next_block =
      map.getCell(hero.getX() + dx, hero.getY() + dy, hero.getFloor());

  switch (next_block) {
  case WALL: // do nothing
    break;
  case SPACE: // move forward
    _move_forward();
    break;
  case LAVA: // lose 1 hp in lava
    hero.goLava();
    _move_forward();
    break;
  case DOOR: // move forward if have key(s), else do nothing
    if (hero.goDoor())
      _move_forward();
    break;
  case UP_BLOCK: // go to up floor
    _move_forward();
    hero.goUp_block();
    break;
  case DOWN_BLOCK: // go to down floor
    _move_forward();
    hero.goDown_block();
    break;

  case SLIME:
  case SKELETON:
  case BAT:
  case APOSTLE:
  case BEELZEBUB:
    if (hero.battle(next_block)) {
      _move_forward(); // defeat the monster
    }
    break;

  case SMALL_BOTTLE:
    hero.aquireSmall_bottle();
    _move_forward();
    break;
  case BIG_BOTTLE:
    hero.aquireBig_bottle();
    _move_forward();
    break;
  case SWORD:
    hero.aquireSword();
    _move_forward();
    break;
  case SHIELD:
    hero.aquireShield();
    _move_forward();
    break;
  case LIFE_GEM:
    hero.aquireLife_gem();
    _move_forward();
    break;
  case KEY:
    hero.aquireKey();
    _move_forward();
    break;
  default:;
  }

  return 0;
}
