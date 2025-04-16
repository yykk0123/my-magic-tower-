#ifndef _HERO_HPP_
#define _HERO_HPP_

#include "monster.hpp"
#include "role.hpp"

enum direction {
  UP,
  LEFT,
  DOWN,
  RIGHT,
};

class Hero : public Role {
public:
  Hero() {};
  Hero(const char *name, int hp_limit, int attack, int defence, Skill skill);
  ~Hero() {};

  int move();
  int battle(Monster &monster);
  int use_samll_bottle();
  int use_big_bottle();
  void update_hero_location();

  int getX() { return x; }
  int getY() { return y; }
  int getFloor() { return floor; }
  void setFloor(int floor) { floor = floor; }

private:
  std::string name;
  int hp;
  int hp_limit;
  int defence;
  int attack;
  int score;
  int key;
  int small_bottle;
  int big_bottle;
  int x;
  int y;
  int floor;
};

#endif // _HERO_HPP_
