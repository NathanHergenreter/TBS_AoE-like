#ifndef BUILDING_TEMP_H

#define BUILDING_TEMP_H

#include <string>
#include <vector>

class building_template
{
 public:
  int init_gold;
  int init_food;
  int init_wood;
  int init_stone;

  std::string name;
  char symbol;
  int pop;
  int age;
  int prereq;
  int max_hp;
  int hp_bonus;
  int armor;
  int armor_bonus;
  bool can_garrison;
  int max_garrison;
  int range;
  int range_bonus;
  int accuracy;
  int accuracy_bonus;
  int sight;
  int sight_bonus;
  int deploy_dist;

  int type;
  int b_class;
  int terrain_type;
  bool passable;
  int out_gold;
  int out_gold_bonus;
  int out_food;
  int out_food_bonus;
  int out_wood;
  int out_wood_bonus;
  int out_stone;
  int out_stone_bonus;
  int attack;
  int attack_bonus;
  int attack_pierce;
  int attack_pierce_bonus;

  int recruit_class;
  std::vector<int> recruit_pool;
  std::vector<int> tech_pool;

  building_template(int);
};

std::vector<building_template*> get_building_templates();


#endif
