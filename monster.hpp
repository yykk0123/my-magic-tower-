#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

#include "role.hpp"

class Monster : public Role {
public:
  Monster() {}
  ~Monster() {}

  void init(const char *_name, int _hp, int _attack, int _defence, int _score,
            Skill _skill) {
    name = _name;
    hp = _hp;
    attack = _attack;
    defence = _defence;
    score = _score;
    skill = _skill;
  };
};

#endif // _MONSTER_HPP_
