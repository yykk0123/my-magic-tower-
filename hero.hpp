#ifndef _HERO_HPP_
#define _HERO_HPP_

#include "elements.hpp"
#include "role.hpp"

class Hero : public Role {
public:
  Hero() {};
  ~Hero() {};

  void init(const char *name, int hp_limit, int attack, int defence,
            Skill skill);

  bool battle(elements monster_type);
  int use_small_bottle();
  int use_big_bottle();
  void update_location();

  std::string getName() { return name; }
  int getHp() { return hp; }
  int getHp_limit() { return hp_limit; }
  int getAttack() { return attack; }
  int getDefence() { return defence; }
  int getScore() { return score; }
  Skill getSkill() { return skill; }
  int getSmall_bottle() { return small_bottle; }
  int getBig_bottle() { return big_bottle; }
  int getX() { return x; }
  int getY() { return y; }
  int getFloor() { return floor; }

  // clang-format off
  void goLava() { hp--; }
  bool goDoor() { if (key) { key--; return true; } return false; }
  void goUp_block() { floor++; update_location(); }
  void goDown_block() { floor--; update_location(); }
  void aquireSmall_bottle() { small_bottle++; }
  void aquireBig_bottle() { big_bottle++; }
  void aquireSword() { attack += 20; }
  void aquireShield() { defence += 10; }
  void aquireLife_gem() { hp_limit += 50; }
  void aquireKey() { key++; }
  void setX(int _x) { x = _x; }
  void setY(int _y) { y = _y; }
  void setFloor(int floor) { floor = floor; }
  // clang-format on

private:
  std::string name;
  int hp;
  int hp_limit;
  int attack;
  int defence;
  Skill skill;
  int score;
  int key;
  int small_bottle;
  int big_bottle;
  int x;
  int y;
  int floor;
};

#endif // _HERO_HPP_
