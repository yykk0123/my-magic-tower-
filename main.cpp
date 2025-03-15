#include <cctype>
#include <cstdlib>
#include <iostream>

#ifdef __linux__
#include "getch.cpp"
#else
#include <conio.h>
#endif // __linux__

#include "elements.hpp"
#include "operation.hpp"

void initialize() {
  CLEAR;
  win = 0;
  hero = {
      "", // name
      50, // hp
      50, // hp_limit
      5,  // attack
      20, // defence
  };
  std::cout << "请输入你的名字：";
  std::cin >> hero.name;

  // set current map to the origin
  for (int i = 0; i < LAYERS; i++) {
    for (int j = 0; j < HEIGHT; j++) {
      for (int k = 0; k < WIDTH; k++) {
        map[i][j][k] = map_original[i][j][k];
      }
    }
  }

  // initialize hero's location
  hero.lct.floor = 0;
  update_hero_location(&hero);
}

void key_enter() {
#ifdef __linux__
  char input_order = toupper(getch());
#else
  char input_order = toupper(_getch());
#endif // __linux__
  if (hero.hp > 0) {
    switch (input_order) {
    case 'A':
      move(&hero, LEFT);
      break;
    case 'D':
      move(&hero, RIGHT);
      break;
    case 'W':
      move(&hero, UP);
      break;
    case 'S':
      move(&hero, DOWN);
      break;
    case 'Q':
      use_bottle(&hero, 1);
      break;
    case 'E':
      use_bottle(&hero, 0);
      break;
    case 'X':
      print_monster_information();
      return; // don't print map and other informations
    case 'R':
      CLEAR;
      initialize();
      return; // don't print map and other informations
    case 'Z':
      exit(EXIT_SUCCESS);
      break;
    }
  }
  if (input_order == 'R') {
    CLEAR;
    initialize();
    return; // don't print map and other informations
  } else if (input_order == 'Z')
    exit(EXIT_SUCCESS);
  print_screen();
}

int main() {
  initialize();
  while (1) {
    key_enter();
  }
  return 0;
}
