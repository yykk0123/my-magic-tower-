#include <iostream>
using namespace std;
// 0为墙 1为空地 2为岩浆 3为门 4为上层块 5为下层块
// 11为小血瓶 12为大血瓶 13为剑 14为盾 15为生命宝石 16为钥匙
// 勇士为h 104
struct player {
  char name[10];
  int hp;
  int hp_limit;
  int defence;
  int attack;
  int score;
  int key;
  int small_bottle;
  int big_bottle;
  int floor;
};
struct player hero = {"", 50, 50, 5, 20, 0, 0, 0, 0, 0};
int map_original[10][10][10] = {
    // clang-format off
    {
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 104, 1, 2, 11, 12, 13, 14, 15, 0,
        0, 1,   4, 9, 8,  7,  6,  3,  16, 0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
    },
    {
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 104, 1, 1, 1, 10, 0, 0, 0, 0,
        0, 5,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
};
int map[10][10][10] = {
    {
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 104, 1, 2, 11, 12, 13, 14, 15, 0,
        0, 1,   4, 9, 8,  7,  6,  3,  16, 0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
    },
    {
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 104, 1, 1, 1, 10, 0, 0, 0, 0,
        0, 5,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
        0, 0,   0, 0, 0, 0,  0, 0, 0, 0,
    },
    {
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    },
    // clang-format on
};
int monster_quantity[10][5];
struct monster {
  int hp;
  int attack;
  int defence;
  int score;
};
// 6 为史莱姆 7为骷髅 8为蝙蝠 9为使徒 10为魔王
struct monster slime = {10, 5, 5, 5};
struct monster skeleton = {16, 8, 8, 8};
struct monster bat = {25, 15, 0, 10};
struct monster apostle = {50, 30, 15, 25};
struct monster beelzebub = {100, 25, 15, 100};

void print_map() {
  cout << "第 " << hero.floor + 1 << " 层\n";
  cout << "钥匙数 " << hero.key << '\n';
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      switch (map[hero.floor][i][j]) {
      case 0:
        cout << "墙   ";
        break;
      case 1:
        cout << "空   ";
        break;
      case 2:
        cout << "岩   ";
        break;
      case 3:
        cout << "门   ";
        break;
      case 4:
        cout << "上   ";
        break;
      case 5:
        cout << "下   ";
        break;
      case 6:
        cout << "史   ";
        break;
      case 7:
        cout << "骷   ";
        break;
      case 8:
        cout << "蝠   ";
        break;
      case 9:
        cout << "使   ";
        break;
      case 10:
        cout << "王   ";
        break;
      case 11:
        cout << "小   ";
        break;
      case 12:
        cout << "大   ";
        break;
      case 13:
        cout << "剑   ";
        break;
      case 14:
        cout << "盾   ";
        break;
      case 15:
        cout << "石   ";
        break;
      case 16:
        cout << "钥   ";
        break;
      case 104:
        cout << "你   ";
        break;
      }
      if (j == 9)
        cout << '\n';
    }
  }
  cout << "名字：" << hero.name << '\n'
       << "生命值：" << hero.hp << '\n'
       << "生命值上限：" << hero.hp_limit << '\n'
       << "防御力：" << hero.defence << '\n'
       << "攻击力：" << hero.attack << '\n'
       << "小血瓶：" << hero.small_bottle << '\n'
       << "大血瓶：" << hero.big_bottle << '\n'
       << "分数：" << hero.score << '\n';
}
void Inputname() {
  cout << " 请输入你的名字：";
  cin >> hero.name;
  system("cls");
  print_map();
}
void monster_count() {
  for (int a = 0; a < 5; a++) {
    monster_quantity[hero.floor][a] = 0;
  }
  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {
      switch (map[hero.floor][i][j]) {
      case 6:
        monster_quantity[hero.floor][0] += 1;
        break;
      case 7:
        monster_quantity[hero.floor][1] += 1;
        break;
      case 8:
        monster_quantity[hero.floor][2] += 1;
        break;
      case 9:
        monster_quantity[hero.floor][3] += 1;
        break;
      case 10:
        monster_quantity[hero.floor][4] += 1;
        break;
      }
    }
  }
}
void reset_block(int i, int j, int p, int q) {
  if (map_original[hero.floor][i][j] == 2) {
    map[hero.floor][i][j] = 2;
    map[hero.floor][i + p][j + q] = 104;
  } else if (map_original[hero.floor][i][j] == 4) {
    map[hero.floor][i][j] = 4;
    map[hero.floor][i + p][j + q] = 104;
  } else if (map_original[hero.floor][i][j] == 5) {
    map[hero.floor][i][j] = 5;
    map[hero.floor][i + p][j + q] = 104;
  } else {
    map[hero.floor][i][j] = 1;
    map[hero.floor][i + p][j + q] = 104;
  }
}

void move(int i, int j, int p, int q) {
  if (map[hero.floor][i + p][j + q] == 0) {
  }
  if (map[hero.floor][i + p][j + q] == 1) {
    reset_block(i, j, p, q);
  }
  if (map[hero.floor][i + p][j + q] == 2) {
    hero.hp -= 1;
    reset_block(i, j, p, q);
  }
  if (map[hero.floor][i + p][j + q] == 3) {
    if (hero.key > 0) {
      reset_block(i, j, p, q);
      hero.key -= 1;
    }
  }
  if (map[hero.floor][i + p][j + q] == 4) {
    reset_block(i, j, p, q);
    hero.floor += 1;
  }
  if (map[hero.floor][i + p][j + q] == 5) {
    reset_block(i, j, p, q);
    hero.floor -= 1;
  }
  if (map[hero.floor][i + p][j + q] == 6) {
    struct monster slime_copy = slime;
    int round = 1;
    while (hero.hp > 0 && slime_copy.hp > 0) {
      if (round >= 50) {
        break;
      }
      if (round % 2 == 1) {
        if (hero.attack >= slime_copy.defence) {
          slime_copy.hp -= (hero.attack - slime_copy.defence);
        } else {
          slime_copy.hp -= 0;
        }
        round += 1;
      } else {
        if (slime_copy.attack >= hero.defence) {
          hero.hp -= (slime_copy.attack - hero.defence);
        } else {
          hero.hp -= 0;
        }
        round += 1;
      }
    }
    if (slime_copy.hp <= 0) {
      hero.score += slime_copy.score;
      reset_block(i, j, p, q);
    }
  }
  if (map[hero.floor][i + p][j + q] == 7) {
    struct monster skeleton_copy = skeleton;
    int round = 1;
    while (hero.hp > 0 && skeleton_copy.hp > 0) {
      if (round >= 50) {
        break;
      }
      if (round % 2 == 1) {
        if (hero.attack >= skeleton_copy.defence) {
          skeleton_copy.hp -= (hero.attack - skeleton_copy.defence);
        } else {
          skeleton_copy.hp -= 0;
        }
        round += 1;
      } else {
        if (skeleton_copy.attack >= hero.defence) {
          hero.hp -= (skeleton_copy.attack - hero.defence);
        } else {
          hero.hp -= 0;
        }
        round += 1;
      }
    }
    if (skeleton_copy.hp <= 0) {
      hero.score += skeleton_copy.score;
      reset_block(i, j, p, q);
    }
  }
  if (map[hero.floor][i + p][j + q] == 8) {
    struct monster bat_copy = bat;
    int round = 1;
    while (hero.hp > 0 && bat_copy.hp > 0) {
      if (round >= 50) {
        break;
      }
      if (round % 2 == 1) {
        if (hero.attack >= bat_copy.defence) {
          bat_copy.hp -= (hero.attack - bat_copy.defence);
        } else {
          bat_copy.hp -= 0;
        }
        round += 1;
      } else {
        if (bat_copy.attack >= hero.defence) {
          hero.hp -= (bat_copy.attack - hero.defence);
          bat.hp += (bat_copy.attack - hero.defence);
        } else {
          hero.hp -= 0;
        }
        round += 1;
      }
    }
    if (bat_copy.hp <= 0) {
      hero.score += bat_copy.score;
      reset_block(i, j, p, q);
    }
  }
  if (map[hero.floor][i + p][j + q] == 9) {
    struct monster apostle_copy = apostle;
    int round = 1;
    while (hero.hp > 0 && apostle_copy.hp > 0) {
      if (round >= 50) {
        break;
      }
      if (round % 2 == 1) {
        if (hero.attack >= apostle_copy.defence) {
          apostle_copy.hp -= (hero.attack - apostle_copy.defence);
        } else {
          apostle_copy.hp -= 0;
        }
        round += 1;
      } else {
        if (apostle_copy.attack >= hero.defence) {
          hero.hp -= (apostle_copy.attack - hero.defence);
        } else {
          hero.hp -= 0;
        }
        round += 1;
      }
    }
    if (apostle_copy.hp <= 0) {
      hero.score += apostle_copy.score;
      reset_block(i, j, p, q);
    }
  }
  if (map[hero.floor][i + p][j + q] == 10) {
    int round = 1;
    while (hero.hp > 0 && beelzebub.hp > 0) {
      if (round >= 50) {
        break;
      }
      if (round % 2 == 1) {
        if (hero.attack >= beelzebub.defence) {
          beelzebub.hp -= (hero.attack - beelzebub.defence);
        } else {
          beelzebub.hp -= 0;
        }
        round += 1;
      } else {
        if (beelzebub.attack >= hero.defence) {
          hero.hp -= (beelzebub.attack - hero.defence);
        } else {
          hero.hp -= 0;
        }
        round += 1;
      }
    }
    if (beelzebub.hp <= 0) {
      hero.score += beelzebub.score;
      reset_block(i, j, p, q);
    }
  }
  if (map[hero.floor][i + p][j + q] == 11) {
    reset_block(i, j, p, q);
    hero.small_bottle += 1;
  }
  if (map[hero.floor][i + p][j + q] == 12) {
    reset_block(i, j, p, q);
    hero.big_bottle += 1;
  }
  if (map[hero.floor][i + p][j + q] == 13) {
    reset_block(i, j, p, q);
    hero.attack += 20;
  }
  if (map[hero.floor][i + p][j + q] == 14) {
    reset_block(i, j, p, q);
    hero.defence += 10;
  }
  if (map[hero.floor][i + p][j + q] == 15) {
    reset_block(i, j, p, q);
    hero.hp_limit += 50;
  }
  if (map[hero.floor][i + p][j + q] == 16) {
    reset_block(i, j, p, q);
    hero.key += 1;
  }
}
void key_enter() {
  char input_order;
  int i = 0;
  int j = 0;
  for (i = 0; i < 10; i++) {
    for (j = 0; j < 10; j++) {
      if (map[hero.floor][i][j] == 104) {
        break;
      }
    }
    if (map[hero.floor][i][j] == 104) {
      break;
    }
  }
  input_order = getchar();
  switch (input_order) {
  case 'A':
  case 'a':
  case 75:
    move(i, j, 0, -1);
    system("cls");
    print_map();
    if (hero.hp <= 0) {
      cout << "胜败乃兵家常事，大侠请重新来过  " << hero.score << '\n';
    }
    if (beelzebub.hp <= 0) {
      cout << "你赢了！！！" << "  " << hero.score << endl;
    }
    break;

  case 'D':
  case 'd':
  case 77:
    move(i, j, 0, 1);
    system("cls");
    print_map();
    if (hero.hp <= 0) {
      cout << "胜败乃兵家常事，大侠请重新来过  " << hero.score << '\n';
    }
    if (beelzebub.hp <= 0) {
      cout << "你赢了！！！" << "  " << hero.score << endl;
    }
    break;
  case 'w':
  case 'W':
  case 72:
    move(i, j, -1, 0);
    system("cls");
    print_map();
    if (hero.hp <= 0) {
      cout << "胜败乃兵家常事，大侠请重新来过  " << hero.score << '\n';
    }
    if (beelzebub.hp <= 0) {
      cout << "你赢了！！！" << "  " << hero.score << endl;
    }
    break;
  case 's':
  case 'S':
  case 80:
    move(i, j, 1, 0);
    system("cls");
    print_map();
    if (hero.hp <= 0) {
      cout << "胜败乃兵家常事，大侠请重新来过  " << hero.score << '\n';
    }
    if (beelzebub.hp <= 0) {
      cout << "你赢了！！！" << "  " << hero.score << endl;
    }
    break;
  case 'Q':
  case 'q':
    if (hero.small_bottle > 0) {
      hero.small_bottle -= 1;
      hero.hp += 10;
      if (hero.hp > hero.hp_limit) {
        hero.hp = hero.hp_limit;
      }
      system("cls");
      print_map();
      break;
    }
  case 'E':
  case 'e':
    if (hero.big_bottle > 0) {
      hero.big_bottle -= 1;
      hero.hp += 25;
      if (hero.hp > hero.hp_limit) {
        hero.hp = hero.hp_limit;
      }
    }
    system("cls");
    print_map();
    break;
  case 'X':
  case 'x':
    system("cls");
    monster_count();
    cout << "名字：史莱姆酱\n"
         << "生命值：" << slime.hp << "\n"
         << "攻击力：" << slime.attack << "\n"
         << "防御力：" << slime.defence << "\n"
         << "特殊属性：无\n"
         << "本层数量：" << monster_quantity[hero.floor][0] << "\n"
         << "名字：骷髅士兵\n"
         << "生命值：" << skeleton.hp << "\n"
         << "攻击力：" << skeleton.attack << "\n"
         << "防御力：" << skeleton.defence << "\n"
         << "特殊属性：无\n"
         << "本层数量：" << monster_quantity[hero.floor][1] << "\n"
         << "名字：吸血蝙蝠\n"
         << "生命值：" << bat.hp << "\n"
         << "攻击力：" << bat.attack << "\n"
         << "防御力：" << bat.defence << "\n"
         << "特殊属性：吸血\n"
         << "本层数量：" << monster_quantity[hero.floor][2] << "\n"
         << "名字：深渊使徒\n"
         << "生命值：" << apostle.hp << "\n"
         << "攻击力：" << apostle.attack << "\n"
         << "防御力：" << apostle.defence << "\n"
         << "特殊属性：精神污染\n"
         << "本层数量：" << monster_quantity[hero.floor][3] << "\n"
         << "名字：魔王\n"
         << "生命值：" << beelzebub.hp << "\n"
         << "攻击力：" << beelzebub.attack << "\n"
         << "防御力：" << beelzebub.defence << "\n"
         << "特殊属性：无\n"
         << "本层数量：" << monster_quantity[hero.floor][4] << "\n";
    break;
  case 'Z':
  case 'z':
    system("cls");
    print_map();
    break;
  case 'R':
  case 'r':
    system("cls");
    hero = {"", 50, 50, 5, 20, 0, 0, 0, 0, 0};
    beelzebub = {100, 25, 15, 100};
    for (int i = 0; i < 10; i++) {
      for (int j = 0; j < 10; j++) {
        for (int k = 0; k < 10; k++) {
          map[i][j][k] = map_original[i][j][k];
        }
      }
    }
    Inputname();
    break;
  }
}
int main() {
  Inputname();
  while (1) {
    key_enter();
  }
  return 0;
}
