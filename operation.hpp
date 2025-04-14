#ifndef _OPERATION_HPP_
#define _OPERATION_HPP_

#define ROUND 50 // max rounds in battle

extern int end;

enum direction {
  UP,
  LEFT,
  DOWN,
  RIGHT,
};

int battle(struct player *hero, int monster_type);
void update_hero_location(struct player *hero);
int move(struct player *hero, int direction);
int use_bottle(struct player *hero, int small);

#endif // _OPERATION_HPP_
