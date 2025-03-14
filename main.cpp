#include <cctype>
#include <cstdlib>
#include <iostream>

#include "elements.hpp"
#include "operation.hpp"

//   if (map[hero.floor][i + p][j + q] == 8) {
//     struct monster bat_copy = bat;
//     int round = 1;
//     while (hero.hp > 0 && bat_copy.hp > 0) {
//       if (round >= 50) {
//         break;
//       }
//       if (round % 2 == 1) {
//         if (hero.attack >= bat_copy.defence) {
//           bat_copy.hp -= (hero.attack - bat_copy.defence);
//         } else {
//           bat_copy.hp -= 0;
//         }
//         round += 1;
//       } else {
//         if (bat_copy.attack >= hero.defence) {
//           hero.hp -= (bat_copy.attack - hero.defence);
//           bat.hp += (bat_copy.attack - hero.defence);
//         } else {
//           hero.hp -= 0;
//         }
//         round += 1;
//       }
//     }
//     if (bat_copy.hp <= 0) {
//       hero.score += bat_copy.score;
//       reset_block(i, j, p, q);
//     }
//   }

//   if (map[hero.floor][i + p][j + q] == 9) {
//     struct monster apostle_copy = apostle;
//     int round = 1;
//     while (hero.hp > 0 && apostle_copy.hp > 0) {
//       if (round >= 50) {
//         break;
//       }
//       if (round % 2 == 1) {
//         if (hero.attack >= apostle_copy.defence) {
//           apostle_copy.hp -= (hero.attack - apostle_copy.defence);
//         } else {
//           apostle_copy.hp -= 0;
//         }
//         round += 1;
//       } else {
//         if (apostle_copy.attack >= hero.defence) {
//           hero.hp -= (apostle_copy.attack - hero.defence);
//         } else {
//           hero.hp -= 0;
//         }
//         round += 1;
//       }
//     }
//     if (apostle_copy.hp <= 0) {
//       hero.score += apostle_copy.score;
//       reset_block(i, j, p, q);
//     }
//   }

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
