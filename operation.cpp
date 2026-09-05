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
    case UPSTAIR:                                                             \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), UPSTAIR);        \
      break;                                                                   \
    case DOWNSTAIR:                                                           \
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), DOWNSTAIR);      \
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
  int nextX = hero.getX() + dx;
  int nextY = hero.getY() + dy;

  // beyond range
  if (nextX < 0 || nextX >= map.getWidth() ||
      nextY < 0 || nextY >= map.getHeight()) {
      return 0;
  }

  elements next_block = map.getCell(nextX, nextY, hero.getFloor());

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
  case STONE_DOOR: // move forward if have key(s), else do nothing
    if (hero.goDoor())
      _move_forward();
    break;
  case UPSTAIR: // go to up floor
    if (hero.getFloor() + 1 < map.getFloor()) {
      _move_forward();
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), UPSTAIR);
      hero.goUp_block();
    }
    break;
  case DOWNSTAIR: // go to down floor
    if (hero.getFloor() > 0) {
      _move_forward();
      map.setCell(hero.getX(), hero.getY(), hero.getFloor(), DOWNSTAIR);
      hero.goDown_block();
    }
    break;

  case SLIME_GREEN:
  case SKELETON:
  case BAT:
  case APOSTLE_RED:
  case BEELZEBUB:
    if (hero.battle(next_block)) {
      _move_forward(); // defeat the monster
    }
    break;

  case HEALTH_BOTTLE:
    hero.aquireHealth_bottle();
    _move_forward();
    break;
  case BLUE_BOTTLE:
    hero.aquireBlue_bottle();
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
  case HEALTH_CRYSTAL:
    hero.aquireLife_gem();
    _move_forward();
    break;
  case STONE_KEY:
    hero.aquireKey();
    _move_forward();
    break;
  default:;
  }

  return 0;
}
