#include "hero.hpp"

Hero::Hero(const char *name, int hp_limit, int attack, int defence,
           Skill skill) {
  name = name;
  hp_limit = hp_limit;
  attack = attack;
  defence = defence;
  skill = skill;
  hp = hp_limit;
  score = 0;
  key = 0;
  small_bottle = 0;
  big_bottle = 0;
}

int Hero::move(Map &map) { return 0; }

int battle(Monster &monster);
int use_samll_bottle();
int use_big_bottle();
void update_hero_location(Map &map);
