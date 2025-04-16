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
