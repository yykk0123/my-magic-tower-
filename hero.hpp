#ifndef _HERO_HPP_
#define _HERO_HPP_

#include "role.hpp"

class Hero : public Role {
public:
  Hero() {};
  Hero(const char *name, int hp_limit, int attack, int defence, Skill skill);
  ~Hero() {};

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
