#include "elements.hpp"

struct player hero = {
    "", // name
    50, // hp
    50, // hp_limit
    5,  // attack
    20, // defence
};

struct monster slime = {10, 5, 5, 5, NONE};
struct monster skeleton = {16, 8, 8, 8, NONE};
struct monster bat = {25, 15, 0, 10, BLOODSUCKING};
struct monster apostle = {50, 30, 15, 25, MENTAL_POLLUTION};
struct monster beelzebub = {100, 25, 15, 100, NONE};

int map_original[LAYERS][HEIGHT][WIDTH] = {
    // clang-format off
    {
        0, 0,   0, 0, 0,  0,  0,  0,  0,  0,
        0, 104, 1, 2, 11, 12, 13, 14, 15, 0,
        0, 1,   4, 9, 8,  7,  6,  3,  16, 0,
        0, 10,  0, 0, 0,  0,  0,  0,  0,  0,
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
    // clang-format on
};

// will copy from map_original in `initialize()`
int map[LAYERS][HEIGHT][WIDTH] = {};
