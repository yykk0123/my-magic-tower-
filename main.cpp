#include <cctype>
#include <cstdlib>
#include <iostream>

#include "elements.hpp"
#include "operation.hpp"

void initialize() {
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

  hero.lct.floor = 0;
  update_hero_location(&hero);
}

void key_enter() {
  char input_order = toupper(getchar());
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
    hero = {"", 50, 50, 5, 20, 0, 0, 0, 0, 0};
    beelzebub = {100, 25, 15, 100};
    initialize();
    return; // don't print map and other informations
  case 'Z':
    exit(EXIT_SUCCESS);
    break;
  }

  print_screen();
}

int main() {
  initialize();
  while (1) {
    key_enter();
  }
  return 0;
}
