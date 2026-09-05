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
  int use_health_bottle();
  int use_blue_bottle();
  bool update_location(elements spawn_element = HERO);

  std::string getName() { return name; }
  int getHp() { return hp; }
  int getHp_limit() { return hp_limit; }
  int getAttack() { return attack; }
  int getDefence() { return defence; }
  int getScore() { return score; }
  Skill getSkill() { return skill; }
  int getHealth_bottle() { return health_bottle; }
  int getBlue_bottle() { return blue_bottle; }
  int getCoin(){ return coin;}
  int getExperience(){ return experience;}
  int getX() { return x; }
  int getY() { return y; }
  int getFloor() { return floor; }

  // clang-format off
  void goLava() { hp--; }
  bool goDoor() { if (key) { key--; return true; } return false; }
  void goUp_block() { floor++; update_location(DOWNSTAIR); }
  void goDown_block() { floor--; update_location(UPSTAIR); }
  void aquireHealth_bottle() { health_bottle++; }
  void aquireBlue_bottle() { blue_bottle++; }
  void aquireSword() { attack += 20; }
  void aquireShield() { defence += 10; }
  void aquireLife_gem() { hp_limit += 50; }
  void aquireKey() { key++; }
  void setX(int _x) { x = _x; }
  void setY(int _y) { y = _y; }
  void setFloor(int _floor) { floor = _floor; }
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
  int health_bottle;
  int blue_bottle;
  int coin;
  int experience;
  int x;
  int y;
  int floor;
};

#endif // _HERO_HPP_
