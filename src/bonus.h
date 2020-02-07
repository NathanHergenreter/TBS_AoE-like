#ifndef BONUS_H

#define BONUS_H

#include <string>

enum bonus_type { bonus_default, bonus_unit, bonus_unit_class, bonus_bldg, bonus_age  };

enum mod_type { mod_default, mod_additive, mod_multiplier};

enum unit_bonus_type { unit_bonus_default, unit_bonus_hp, unit_bonus_armor, unit_bonus_move, unit_bonus_melee, unit_bonus_melee_ap, unit_bonus_ranged, unit_bonus_ranged_ap, unit_bonus_building, unit_bonus_range, unit_bonus_accuracy, unit_bonus_sight, unit_bonus_gold, unit_bonus_food, unit_bonus_wood, unit_bonus_stone };

enum building_bonus_type { bldg_bonus_default, bldg_bonus_hp, bldg_bonus_armor, bldg_bonus_gold, bldg_bonus_food, bldg_bonus_wood, bldg_bonus_stone, bldg_bonus_attack, bldg_bonus_ap, bldg_bonus_range, bldg_bonus_accuracy, bldg_bonus_sight, bldg_bonus_cost_gold, bldg_bonus_cost_food, bldg_bonus_cost_wood, bldg_bonus_cost_stone };

class bonus
{
  /*
   * type - Entity subclass bonus is applied to
   * target - Target unit building, or class it is applied
   * unit_bonus - The type of unit bonus (type is bonus_unit_type)
   * building_bonus - The type of building bonus (type is bonus_building_type)
   * mod - The modification the bonus applies
   */
  enum bonus_type mem_type;
  int mem_target;
  enum unit_bonus_type mem_unit_bonus;
  enum building_bonus_type mem_building_bonus;
  int mem_mod;
  enum mod_type mem_mod_type;
  std::string mem_desc;

  void construct_desc();

 public:
  bonus();
  //Bonus type, target stat type, target, mod, mod type
  bonus(enum bonus_type, int, int, int, enum mod_type);
  ~bonus();
  enum bonus_type type() { return mem_type; }
  int target() { return mem_target; }
  enum unit_bonus_type unit_bonus() { return mem_unit_bonus; }
  enum building_bonus_type building_bonus() { return mem_building_bonus; }
  int mod() { return mem_mod; }
  enum mod_type mod_type() { return mem_mod_type; }
  std::string desc() { return mem_desc; }
};

#endif
