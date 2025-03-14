#ifndef _OPERATION_CPP_
#define _OPERATION_CPP_

#include <cstdlib>
#include <iostream>

#include "elements.cpp"

#define ROUND 50 // max rounds in battle

// use correct command to clean screen
#if defined(__linux__)
#define CLEAR system("clear")
#else
#define CLEAR system("cls")
#endif // __linux__

int win = 0; // win or continue?

int battle(struct player *hero, int monster_type);

void update_hero_location(struct player *hero) {
  // get the location of the hero originally
  for (int i = 0; i < HEIGHT; i++)
    for (int j = 0; j < WIDTH; j++)
      if (map[hero->lct.floor][i][j] == HERO) {
        hero->lct.y = i;
        hero->lct.x = j;
      }
}

enum move_around {
  UP,
  LEFT,
  DOWN,
  RIGHT,
};

// reset block to the origin if the block was lava, up_block or down_block
// else set it to blank block
#define move_forward(block)                                                    \
  {                                                                            \
    *current_block = block;                                                    \
    *new_block = HERO;                                                         \
    hero->lct.x += dx;                                                         \
    hero->lct.y += dy;                                                         \
  }

// direction can be UP, DOWN, LEFT, or RIGHT
void move(struct player *hero, int direction) {
  int *current_block = &map[hero->lct.floor][hero->lct.y][hero->lct.x];
  int dx = (direction == LEFT) ? -1 : ((direction == RIGHT) ? 1 : 0);
  int dy = (direction == DOWN) ? 1 : ((direction == UP) ? -1 : 0);
  int *new_block = &map[hero->lct.floor][hero->lct.y + dy][hero->lct.x + dx];
#ifdef DEBUG
  printf("moving from (%d, %d) to (%d, %d)\n", hero->lct.x, hero->lct.y,
         hero->lct.x + dx, hero->lct.y + dy);
  printf("the cureent block is %d, the new is %d\n", *current_block,
         *new_block);
#endif

  switch (*new_block) {
  case WALL: // do nothing
    break;
  case SPACE: // move forward
    move_forward(SPACE);
    break;
  case LAVA: // lose 1 hp in lava
    hero->hp -= 1;
    move_forward(LAVA);
    break;
  case DOOR: // move forward if have key(s), else do nothing
    if (hero->key) {
      hero->key -= 1;
      move_forward(SPACE);
    }
    break;
  case UP_BLOCK: // go to up floor
    hero->lct.floor += 1;
    update_hero_location(hero);
    break;
  case DOWN_BLOCK: // go to down floor
    hero->lct.floor -= 1;
    update_hero_location(hero);
    break;
  case SLIME:
  case SKELETON:
  case BAT:
  case APOSTLE:
  case BEELZEBUB:
    if (battle(hero, *new_block))
      move_forward(SPACE); // defeat the monster
    break;
  case SMALL_BOTTLE:
    hero->small_bottle += 1;
    move_forward(SPACE);
    break;
  case BIG_BOTTLE:
    hero->big_bottle += 1;
    move_forward(SPACE);
    break;
  case SWORD:
    hero->attack += 20;
    move_forward(SPACE);
    break;
  case SHIELD:
    hero->defence += 10;
    move_forward(SPACE);
    break;
  case LIFE_GEM:
    hero->hp_limit += 50;
    move_forward(SPACE);
    break;
  case KEY:
    hero->key += 1;
    move_forward(SPACE);
    break;
  }
}

// use the small bottle if small==1 else big bottle
void use_bottle(struct player *hero, int small) {
  if (small) {
    if (hero->small_bottle == 0)
      return;
    hero->small_bottle -= 1;
    hero->hp += 10;
  } else {
    if (hero->big_bottle == 0)
      return;
    hero->big_bottle -= 1;
    hero->hp += 25;
  }

  if (hero->hp > hero->hp_limit)
    hero->hp = hero->hp_limit;
}

// fight with the monster, return 1 if win, else 0
int battle(struct player *hero, int monster_type) {

  // copy the property of monster
  struct monster mst;
  switch (monster_type) {
    // clang-format off
    case SLIME: mst=slime; break;
    case SKELETON: mst=skeleton; break;
    case BAT: mst=bat; break;
    case APOSTLE: mst=apostle; break;
    case BEELZEBUB: mst=beelzebub; break;
    // clang-format on
  }

  int attack = hero->attack - mst.defence;
  int hurt = mst.attack - hero->defence;
#ifdef DEBUG
  printf("fighting with %d, attack is %d, hurt is %d\n", monster_type, attack,
         hurt);
#endif
  if (attack <= 0 && hurt <= 0)
    return 0;
  else if (attack <= 0)
    hero->hp -= hurt * ROUND;
  else if (hurt <= 0)
    mst.hp -= attack * ROUND;
  else
    for (int round = 0; round < ROUND; round++) {
#ifdef DEBUG
      printf("hero's hp: %d, monster's hp: %d\n", hero->hp, mst.hp);
#endif
      mst.hp -= attack;
      if (mst.hp <= 0) {
        hero->score += mst.score;
        if (monster_type == BEELZEBUB)
          win = 1;
        return 1; // defeat the monster
      }
      hero->hp -= hurt;
      if (hero->hp <= 0)
        return 0;
    }

  if (mst.hp <= 0) {
    hero->score += mst.score;
    if (monster_type == BEELZEBUB)
      win = 1;
    return 1; // defeat the monster
  }
  return 0;
}

// print floor number, key number, map and properties
void print_screen() {
#ifndef DEBUG
  CLEAR;
#endif
  std::cout << "第 " << hero.lct.floor + 1 << " 层\n";
  std::cout << "钥匙数 " << hero.key << '\n';
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      switch (map[hero.lct.floor][i][j]) {
        // clang-format off
        case 0:   std::cout << "墙   "; break;
        case 1:   std::cout << "空   "; break;
        case 2:   std::cout << "岩   "; break;
        case 3:   std::cout << "门   "; break;
        case 4:   std::cout << "上   "; break;
        case 5:   std::cout << "下   "; break;
        case 6:   std::cout << "史   "; break;
        case 7:   std::cout << "骷   "; break;
        case 8:   std::cout << "蝠   "; break;
        case 9:   std::cout << "使   "; break;
        case 10:  std::cout << "王   "; break;
        case 11:  std::cout << "小   "; break;
        case 12:  std::cout << "大   "; break;
        case 13:  std::cout << "剑   "; break;
        case 14:  std::cout << "盾   "; break;
        case 15:  std::cout << "石   "; break;
        case 16:  std::cout << "钥   "; break;
        case 104: std::cout << "你   "; break;
        // clang-format on
      }
      if (j == 9)
        std::cout << '\n';
    }
  }
  std::cout << "名字：" << hero.name << '\n'
            << "生命值：" << hero.hp << '\n'
            << "生命值上限：" << hero.hp_limit << '\n'
            << "防御力：" << hero.defence << '\n'
            << "攻击力：" << hero.attack << '\n'
            << "小血瓶：" << hero.small_bottle << '\n'
            << "大血瓶：" << hero.big_bottle << '\n'
            << "分数：" << hero.score << '\n';

  if (hero.hp <= 0)
    std::cout << "胜败乃兵家常事，大侠请重新来过  " << hero.score << '\n';

  if (win) {
    std::cout << "你赢了！！！" << "  " << hero.score << std::endl;
    exit(EXIT_SUCCESS);
  }
}

// print monsters' properties and numbers on current floor
void print_monster_information() {
  // count monsters
  int monster_quantity[5] = {};
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      switch (map[hero.lct.floor][i][j]) {
        // clang-format off
      case SLIME:     monster_quantity[0]++; break;
      case SKELETON:  monster_quantity[1]++; break;
      case BAT:       monster_quantity[2]++; break;
      case APOSTLE:   monster_quantity[3]++; break;
      case BEELZEBUB: monster_quantity[4]++; break;
        // clang-format on
      }
    }
  }

  std::cout << "名字：史莱姆酱\n"
            << "生命值：" << slime.hp << "\n"
            << "攻击力：" << slime.attack << "\n"
            << "防御力：" << slime.defence << "\n"
            << "特殊属性：无\n"
            << "本层数量：" << monster_quantity[0] << "\n"
            << "\n"
            << "名字：骷髅士兵\n"
            << "生命值：" << skeleton.hp << "\n"
            << "攻击力：" << skeleton.attack << "\n"
            << "防御力：" << skeleton.defence << "\n"
            << "特殊属性：无\n"
            << "本层数量：" << monster_quantity[1] << "\n"
            << "\n"
            << "名字：吸血蝙蝠\n"
            << "生命值：" << bat.hp << "\n"
            << "攻击力：" << bat.attack << "\n"
            << "防御力：" << bat.defence << "\n"
            << "特殊属性：吸血\n"
            << "本层数量：" << monster_quantity[2] << "\n"
            << "\n"
            << "名字：深渊使徒\n"
            << "生命值：" << apostle.hp << "\n"
            << "攻击力：" << apostle.attack << "\n"
            << "防御力：" << apostle.defence << "\n"
            << "特殊属性：精神污染\n"
            << "本层数量：" << monster_quantity[3] << "\n"
            << "\n"
            << "名字：魔王\n"
            << "生命值：" << beelzebub.hp << "\n"
            << "攻击力：" << beelzebub.attack << "\n"
            << "防御力：" << beelzebub.defence << "\n"
            << "特殊属性：无\n"
            << "本层数量：" << monster_quantity[4] << "\n";
}

#endif // _OPERATION_CPP_
