#ifndef _MONSTER_HPP_
#define _MONSTER_HPP_

#include "role.hpp"

class Monster : public Role {
public:
  // inherite constructor functions,
  // https://stackoverflow.com/questions/347358/inheriting-constructors
  using Role::Role;
  ~Monster() {}
};

#endif // _MONSTER_HPP_
