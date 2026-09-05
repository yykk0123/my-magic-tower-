#include "hero.hpp"
#include "elements.hpp"
#include "global.hpp"

#define ROUND 50

void Hero::init(const char *_name, int _hp_limit, int _attack, int _defence,
                Skill _skill) {
  name = _name;
  hp = _hp_limit;
  hp_limit = _hp_limit;
  attack = _attack;
  defence = _defence;
  skill = _skill;
  score = 0;
  floor = 0;
  key = 0;
  health_bottle = 0;
  blue_bottle = 0;
  experience=0;
  coin=0;
}

static inline int min(int a, int b) { return (a < b ? a : b); }

int Hero::use_health_bottle() {
  if (health_bottle) {
    health_bottle--;
    hp += 10;
    hp = min(hp, hp_limit);
    return 1;
  }
  return 0;
}

int Hero::use_blue_bottle() {
  if (blue_bottle) {
    blue_bottle--;
    hp += 25;
    hp = min(hp, hp_limit);
    return 1;
  }
  return 0;
}

bool Hero::update_location(elements spawn_element) {
  for (int h = 0; h < map.getHeight(); h++)
    for (int w = 0; w < map.getWidth(); w++)
      if (map_original.getCell(w, h, hero.getFloor()) == spawn_element) {
        hero.setX(w);
        hero.setY(h);
        map.setCell(w, h, hero.getFloor(), HERO);
        return true;
      }
  return false;
}

bool Hero::battle(elements monster_type) {
  // copy the property of monster
  Monster *mst;
  switch (monster_type) {
    // clang-format off
    case SLIME_GREEN:     mst=&slime;     break;
    case SKELETON:  mst=&skeleton;  break;
    case BAT:       mst=&bat;       break;
    case APOSTLE_RED:   mst=&apostle;   break;
    case BEELZEBUB: mst=&beelzebub; break;
    default:;
    // clang-format on
  }

  int mst_hp = mst->getHp();
  Skill mst_skill = mst->getSkill();
  int attack = hero.attack - mst->getDefence();
  int hurt = mst->getAttack() - hero.defence;

  // they can't hurt each other
  if (attack <= 0 && hurt <= 0)
    return false;

  // hero can't attack monsters
  else if (attack <= 0)
    hero.hp -= hurt * ROUND;

  // monsters can't hurt hero
  else if (hurt <= 0)
    mst_hp -= attack * ROUND * (mst_skill == MENTAL_POLLUTION ? 2 / 3 : 1);

  // they can hurt each other
  else
    for (int round = 1; round < ROUND && hero.hp > 0 && mst_hp > 0; round++) {
      if (mst_skill == MENTAL_POLLUTION && round % 3 == 0)
        mst_hp += attack; // hero is interfered and can't attack monsters
      mst_hp -= attack;
      hero.hp -= hurt;
      if (mst_skill == BLOODSUCKING)
        mst_hp += hurt; // monsters can suck blood if have the skill
    }

  if (mst_hp <= 0) {
    hero.score += mst->getScore();
    if (monster_type == BEELZEBUB)
      end = 1;
    return true; // defeat the monster
  } else if (hero.hp <= 0) {
    end = -1;
    return false;
  }
  return true;
}
