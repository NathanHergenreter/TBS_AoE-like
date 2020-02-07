#ifndef PLAYER_H

#define PLAYER_H

#include <vector>
#include "civilization.h"
#include "building_templates.h"
#include "unit_templates.h"
#include "technology.h"

class player
{
  //Players traits
  bool is_human;
  civilization *civ;
  int color;
  int age;

  //Resources
  int pop_cur;
  int pop_max;
  int gold_res;
  int gold_growth;
  int food_res;
  int food_growth;
  int wood_res;
  int wood_growth;
  int stone_res;
  int stone_growth;

  //Pools
  std::vector< std::vector<building_template*> > building_pools;
  std::vector< std::vector<unit_template*> > unit_pools;
  std::vector<tech*> tech_pool;
  std::vector<bool> tech_research;

  //FOW
  std::vector< std::vector<bool> > mem_fow_map;

 public:
  //Con/Destructors
  player();
  player(bool, civilization*, int);
  ~player();

  //Traits Functions
  bool human() { return is_human; }
  civilization * get_civ() { return civ; }
  int get_color() { return color; }
  int get_age() { return age; }
  void mod_age(int mod) { age+=mod; }

  //Resources Functions
  int get_cur_pop() { return pop_cur;}
  void mod_cur_pop(int mod) { pop_cur+=mod; }
  int get_max_pop() { return pop_max; }
  void mod_max_pop(int mod) { pop_max+=mod; }
  int get_gold() { return gold_res; }
  int get_gold_growth() { return gold_growth; }
  void mod_gold_growth(int mod) { gold_growth+=mod; }
  int get_food() { return food_res; }
  int get_food_growth() { return food_growth; }
  void mod_food_growth(int mod) { food_growth+=mod; }
  int get_wood() { return wood_res; }
  int get_wood_growth() { return wood_growth; }
  void mod_wood_growth(int mod) { wood_growth+=mod; }
  int get_stone() { return stone_res; }
  int get_stone_growth() { return stone_growth; }
  void mod_stone_growth(int mod) { stone_growth+=mod; }
  void purchase(int gold, int food, int wood, int stone) { gold_res-=gold; food_res-=food; wood_res-=wood; stone_res-=stone; }

  //Pool Functions
  int get_num_bclasses() { return building_pools.size(); }
  building_template * get_bldg(int b_class, int idx) 
  { 
    return building_pools[b_class][idx]; 
  }
  int get_bldg_idx(int b_class, int type) 
  {
    int idx=0;
    for(idx=0; idx < (int) building_pools[b_class].size(); idx++)
      {
	if(building_pools[b_class][idx]->type==type) { break; }
      }
    return idx;
  }
  int get_num_bclass(int b_class) { return building_pools[b_class].size(); }
  int get_num_uclasses() { return unit_pools.size(); }
  int get_unit_idx(int u_class, int type) 
  {
    int idx=0;
    for(idx=0; idx < (int) unit_pools[u_class].size(); idx++)
      {
	if(unit_pools[u_class][idx]->type==type) { break; }
      }
    return idx;
  }
  unit_template * get_unit(int u_class, int idx) 
  { 
    return unit_pools[u_class][idx]; 
  }
  int get_num_uclass(int u_class) { return unit_pools[u_class].size(); }
  int num_tech() { return tech_pool.size(); }
  tech * get_tech(int type) { return tech_pool[type]; }
  void set_researched(int type) { tech_research[type] = true; }
  bool tech_researched(int type) { return tech_research[type]; }

  //Player Changes
  void apply_bonus(bonus *);
  void update_resources() { gold_res+=gold_growth; food_res+=food_growth; wood_res+=wood_growth; stone_res+=stone_growth; }

  //Output
  void resource_output();

  //FOW
  std::vector < std::vector<bool> > * fow_map() { return &mem_fow_map; }
  bool has_sight(int x, int y) { return mem_fow_map[y][x]; }
};

#endif
