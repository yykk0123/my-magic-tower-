#ifndef _OPERATION_HPP_
#define _OPERATION_HPP_

#define ROUND 50 // max rounds in battle

// use correct command to clean screen
#if defined(__linux__)
#define CLEAR system("clear")
#else
#define CLEAR system("cls")
#endif // __linux__

extern int win;

enum move_around {
  UP,
  LEFT,
  DOWN,
  RIGHT,
};

int battle(struct player *hero, int monster_type);
void update_hero_location(struct player *hero);
void move(struct player *hero, int direction);
void use_bottle(struct player *hero, int small);
void print_screen();
void print_monster_information();

#endif // _OPERATION_HPP_
