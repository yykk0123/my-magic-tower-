#include "elements.hpp"

struct player hero = {
    "", // name
    50, // hp
    50, // hp_limit
    5,  // attack
    20, // defence
};

Monster slime("slime", 10, 5, 5, 5, NONE);
Monster skeleton("skeleton", 16, 8, 8, 8, NONE);
Monster bat("bat", 25, 15, 0, 10, BLOODSUCKING);
Monster apostle("apostle", 50, 30, 15, 25, MENTAL_POLLUTION);
Monster beelzebub("beelzebub", 100, 25, 15, 100, NONE);

// int map_original[LAYERS][HEIGHT][WIDTH] = {
//     // clang-format off
//     {
//         WALL, WALL,  WALL,     WALL,    WALL,         WALL,       WALL, WALL,
//         WALL,     WALL, WALL, HERO,  SPACE,    LAVA,    SMALL_BOTTLE,
//         BIG_BOTTLE, SWORD, SHIELD, LIFE_GEM, WALL, WALL, SPACE, UP_BLOCK,
//         APOSTLE, BAT,          SKELETON,   SLIME, DOOR,   KEY,      WALL,
//         WALL, WALL,  WALL,     WALL,    WALL,         WALL,       WALL, WALL,
//         WALL,     WALL, WALL, WALL,  WALL,     WALL,    WALL,         WALL,
//         WALL,  WALL,   WALL,     WALL, WALL, WALL,  WALL,     WALL,    WALL,
//         WALL,       WALL,  WALL,   WALL,     WALL, WALL, WALL,  WALL, WALL,
//         WALL,         WALL,       WALL,  WALL,   WALL,     WALL, WALL, WALL,
//         WALL,     WALL,    WALL,         WALL,       WALL,  WALL,   WALL,
//         WALL, WALL, WALL,  WALL,     WALL,    WALL,         WALL,       WALL,
//         WALL,   WALL,     WALL, WALL, WALL,  WALL,     WALL,    WALL, WALL,
//         WALL,  WALL,   WALL,     WALL,
//     },
//     {
//         WALL, WALL,       WALL,  WALL,  WALL,  WALL,      WALL, WALL, WALL,
//         WALL, WALL, HERO,       SPACE, SPACE, SPACE, BEELZEBUB, WALL, WALL,
//         WALL, WALL, WALL, DOWN_BLOCK, WALL,  WALL,  WALL,  WALL,      WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL, WALL, WALL,       WALL,  WALL,  WALL,  WALL, WALL,
//         WALL, WALL, WALL,
//     },
//     // clang-format on
// };
//
// // will copy from map_original in `initialize()`
// int map[LAYERS][HEIGHT][WIDTH] = {};
