#include <sstream>
#include "bonus.h"
#include "entity.h"

/********* CONTENTS **********/

//(A) Bonus Constructor

//(Z) Bonus Description
std::string bonus_desc(enum bonus_type, int, int, int, enum mod_type);

/********* CONTENTS **********/

//(A) Constructor
bonus :: bonus() { }

bonus:: bonus(enum bonus_type type, int mod_type, int target, int mod, enum mod_type modification_type)
{
  this->mem_type=type;
  this->mem_target=target;
  this->mem_mod=mod;
  this->mem_mod_type=modification_type;
  this->mem_desc=bonus_desc(type, mod_type, target, mod, modification_type);

  //Initializes to 0
  this->mem_unit_bonus=unit_bonus_default;
  this->mem_building_bonus=bldg_bonus_default;

  //Determines unit_bonus and building_bonus depending on bonus_type
  if(type==bonus_unit || type==bonus_unit_class)
    {
      this->mem_unit_bonus = (enum unit_bonus_type) mod_type;
    }
  //Determines unit_bonus and building_bonus depending on bonus_type
  if(type==bonus_bldg)
    {
      this->mem_building_bonus =(enum building_bonus_type) mod_type;
    }
}

std::string bonus_desc(enum bonus_type type, int mod_type, int target, int mod, enum mod_type modification_type)
{
  std::string ret="";
  //Default - Used for unlocks
  if(type==bonus_default)
    {
      ret+="Unlock";
    }
  //Age Up
  else if(type==bonus_age)
    {
      ret+="Age Up";
    }
  //Building Bonus
  else if(type==bonus_bldg)
    {
      //Gets Target
      ret+=get_bldg_loc( (enum building_type) target);
      ret+=" ";

      //+ or -
      if(mod>=0) { ret+="+"; } 

      //Mod
      std::stringstream sstm;
      sstm << mod;
      ret+=sstm.str();
      if(modification_type==mod_additive) { ret+=" "; }
      else if(modification_type==mod_multiplier) { ret+="% "; }

      //Stat Target
      switch(mod_type)
	{
	case bldg_bonus_hp:
	  ret+="HP";
	  break;
	case bldg_bonus_armor:
	  ret+="Armor";
	  break;
	case bldg_bonus_gold:
	  ret+="Gold Output";
	  break;
	case bldg_bonus_food:
	  ret+="Food Output";
	  break;
	case bldg_bonus_wood:
	  ret+="Wood Output";
	  break;
	case bldg_bonus_stone:
	  ret+="Stone Output";
	  break;
	case bldg_bonus_attack:
	  ret+="Attack";
	  break;
	case bldg_bonus_ap:
	  ret+="AP";
	  break;
	case bldg_bonus_range:
	  ret+="Range";
	  break;
	case bldg_bonus_accuracy:
	  ret+="Accuracy";
	  break;
	case bldg_bonus_sight:
	  ret+="Sight";
	  break;
	case bldg_bonus_cost_gold:
	  ret+="Gold Cost";
	  break;
	case bldg_bonus_cost_food:
	  ret+="Food Cost";
	  break;
	case bldg_bonus_cost_wood:
	  ret+="Wood Cost";
	  break;
	case bldg_bonus_cost_stone:
	  ret+="Stone Cost";
	  break;
	}
    }
  //Unit/Unit Class Bonus
  else if(type==bonus_unit || type==bonus_unit_class)
    {
      //Gets Target
      if(type==bonus_unit) { ret+=get_unit_loc( (enum unit_type) target); }
      else { ret+=get_uclass_loc( (enum unit_class) target); }
      ret+=" ";

      //+ or -
      if(mod>=0) { ret+="+"; } 

      //Mod
      std::stringstream sstm;
      sstm << mod;
      ret+=sstm.str();
      if(modification_type==mod_additive) { ret+=" "; }
      else if(modification_type==mod_multiplier) { ret+="% "; }

      //Stat Target
      switch(mod_type)
	{
	case unit_bonus_hp:
	  ret+="HP";
	  break;
	case unit_bonus_armor:
	  ret+="Armor";
	  break;
	case unit_bonus_move:
	  ret+="Move";
	  break;
	case unit_bonus_melee:
	  ret+="Melee Attk";
	  break;
	case unit_bonus_melee_ap:
	  ret+="Melee AP";
	  break;
	case unit_bonus_ranged:
	  ret+="Ranged Attk";
	  break;
	case unit_bonus_ranged_ap:
	  ret+="Ranged AP";
	  break;
	case unit_bonus_building:
	  ret+="Bldg Attk";
	  break;
	case unit_bonus_range:
	  ret+="Range";
	  break;
	case unit_bonus_accuracy:
	  ret+="Accuracy";
	  break;
	case unit_bonus_sight:
	  ret+="Sight";
	  break;
	case unit_bonus_gold:
	  ret+="Gold Cost";
	  break;
	case unit_bonus_food:
	  ret+="Food Cost";
	  break;
	case unit_bonus_wood:
	  ret+="Wood Cost";
	  break;
	case unit_bonus_stone:
	  ret+="Stone Cost";
	  break;
	}
    }

  return ret;
}
