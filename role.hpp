#ifndef _ROLE_H_
#define _ROLE_H_

#include <string>

enum Skill {
  NONE,
  BLOODSUCKING,
  MENTAL_POLLUTION,
};

class Role {
public:
  Role() {}
  Role(const char *name, int hp, int attack, int defence, int score,
       Skill skill) {
    name = name;
    hp = hp;
    attack = attack;
    defence = defence;
    score = score;
    skill = skill;
  };
  ~Role() {}
  int getHp() { return hp; }
  int getAttack() { return attack; }
  int getDefence() { return defence; }
  int getScore() { return score; }
  Skill getSkill() { return skill; }

private:
  std::string name;
  int hp;
  int attack;
  int defence;
  int score;
  Skill skill;
};

#endif // _ROLE_H_
