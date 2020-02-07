#ifndef UNIT_TEMPLATES_H

#define UNIT_TEMPLATES_H

#include <string>
#include <vector>
#include "macros.h"

class unit_template
{
 public:
  int init_gold;
  int init_food;
  int init_wood;
  int init_stone;
  int time;

  std::string name;
  char symbol;
  int pop;
  int age;
  int prereq;
  int max_hp;
  int hp_bonus;
  int armor;
  int armor_bonus;
  int range;
  int range_bonus;
  int accuracy;
  int accuracy_bonus;
  int sight;
  int sight_bonus;
  bool can_garrison;
  int max_garrison;
  int deploy_dist;

  int type;
  int u_class;
  int subclasses[NUM_UNIT_CLASSES];
  bool is_upgradable;
  int upgrade;
  bool is_land;
  bool is_naval;
  bool is_indirect;
  int building_attack;
  int building_attack_bonus;
  int melee_attack;
  int melee_bonus;
  int melee_pierce;
  int melee_pierce_bonus;
  int ranged_attack;
  int ranged_bonus;
  int ranged_pierce;
  int ranged_pierce_bonus;
  int max_move;
  int move_bonus;

  unit_template(int);
};

std::vector<unit_template*> get_unit_templates();

#endif
