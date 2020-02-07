/********* CONTENTS **********/
//(A) Player Con/Destructor

//(B) Apply Bonus

//(Z) Resource Output

/********* CONTENTS **********/

#include <ncurses.h>
#include "player.h"
#include "macros.h"


//(A) Constructor
player :: player(bool human, civilization *civ, int color)
{
  this->is_human=human;
  this->civ=civ;
  this->color=color;
  this->age=0;

  this->pop_cur=0;
  this->pop_max=0;
  this->gold_res=START_GOLD;
  this->gold_growth=0;
  this->food_res=START_FOOD;
  this->food_growth=0;
  this->wood_res=START_WOOD;
  this->wood_growth=0;
  this->stone_res=START_STONE;
  this->stone_growth=0;

  //Gets full pools
  std::vector<building_template*> building_pool = get_building_templates();
  std::vector<unit_template*> unit_pool = get_unit_templates();
  tech_pool = get_technologies();
  tech_research = std::vector<bool>(tech_pool.size(), false);
  tech_research[0] = true;

  //Pool is 2D vector array, one row for each class
  building_pools = std::vector< std::vector<building_template*> >(NUM_BLDG_CLASSES, std::vector<building_template*>(1, new building_template(0)) );

  unit_pools=std::vector< std::vector<unit_template*> >(NUM_UNIT_CLASSES, std::vector<unit_template*>(1, new unit_template(0)) );

  //Adds entities from full pool into class row pool
  int i;
  //Buildings
  for(i=1; i < (int) building_pool.size(); i++)
    {
      building_template *btemp = building_pool[i];
      building_pools[btemp->b_class].push_back(btemp);
    }
  //Units
  for(i=1; i < (int) unit_pool.size(); i++)
    {
      unit_template *utemp = unit_pool[i];
      unit_pools[utemp->u_class].push_back(utemp);
    }

  //Unique Unit
  unit_template *unique = new unit_template(civ->unique());
  unit_pools[unique->u_class].push_back(unique);

  //Applies bonuses
  for(i=0; i < (int) civ->bonus_1()->size(); i++) { apply_bonus(civ->bonus_1()->at(i)); }
  for(i=0; i < (int) civ->bonus_2()->size(); i++) { apply_bonus(civ->bonus_2()->at(i)); }

  //Initializes FOW map
  mem_fow_map= std::vector< std::vector<bool> > (MAP_HEIGHT, std::vector<bool>(MAP_WIDTH,false));
}

//(A) Destructor
player :: ~player() { }

//(B) Apply Bonus
//Applies bonus to templates
void player :: apply_bonus(bonus *bon)
{
  int e_class, idx, md;
  //Age Up
  if(bon->type()==bonus_age)
    {
      mod_age(1);
      //age_output();
    }

  //Building Bonus
  if(bon->type()==bonus_bldg)
    {
      //Finds building template
      for(e_class=0; e_class < (int) building_pools.size(); e_class++)
	{
	  for(idx=0; idx < (int) building_pools[e_class].size(); idx++)
	    {
	      //Target was found, updates template
	      if(building_pools[e_class][idx]->type==bon->target())
		{
		  switch(bon->building_bonus())
		    {
		      //Gold Cost
		    case bldg_bonus_cost_gold:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->init_gold+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->init_gold*bon->mod())/100;
			  building_pools[e_class][idx]->init_gold+=md;
			}
		      break;
		      //Food Cost
		    case bldg_bonus_cost_food:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->init_food+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->init_food*bon->mod())/100;
			  building_pools[e_class][idx]->init_food+=md;
			}
		      break;
		      //Wood Cost
		    case bldg_bonus_cost_wood:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->init_wood+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->init_wood*bon->mod())/100;
			  building_pools[e_class][idx]->init_wood+=md;
			}
		      break;
		      //Stone Cost
		    case bldg_bonus_cost_stone:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->init_stone+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->init_stone*bon->mod())/100;
			  building_pools[e_class][idx]->init_stone+=md;
			}
		      break;
		      //HP
		    case bldg_bonus_hp:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->hp_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->max_hp*bon->mod())/100;
			  building_pools[e_class][idx]->hp_bonus+=md;
			}
		      break;
		      //Armor
		    case bldg_bonus_armor:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->armor_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->armor*bon->mod())/100;
			  building_pools[e_class][idx]->armor_bonus+=md;
			}
		      break;
		      //Attack
		    case bldg_bonus_attack:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->attack_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->attack*bon->mod())/100;
			  building_pools[e_class][idx]->attack_bonus+=md;
			}
		      break;
		      //Attack Pierce
		    case bldg_bonus_ap:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->attack_pierce_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->attack_pierce*bon->mod())/100;
			  building_pools[e_class][idx]->attack_pierce_bonus+=md;
			}
		      break;
		      //Gold
		    case bldg_bonus_gold:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->out_gold_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->out_gold*bon->mod())/100;
			  building_pools[e_class][idx]->out_gold_bonus+=md;
			}
		      break;
		      //Food
		    case bldg_bonus_food:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->out_food_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->out_food*bon->mod())/100;
			  building_pools[e_class][idx]->out_food_bonus+=md;
			}
		      break;
		      //Wood
		    case bldg_bonus_wood:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->out_wood_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->out_wood*bon->mod())/100;
			  building_pools[e_class][idx]->out_wood_bonus+=md;
			}
		      break;
		      //Stone
		    case bldg_bonus_stone:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->out_stone_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->out_stone*bon->mod())/100;
			  building_pools[e_class][idx]->out_stone_bonus+=md;
			}
		      break;
		      //Range
		    case bldg_bonus_range:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->range_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->range*bon->mod())/100;
			  building_pools[e_class][idx]->range_bonus+=md;
			}
		      break;
		      //Accuracy
		    case bldg_bonus_accuracy:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->accuracy_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->accuracy*bon->mod())/100;
			  building_pools[e_class][idx]->accuracy_bonus+=md;
			}
		      break;
		      //Sight
		    case bldg_bonus_sight:
		      if(bon->mod_type()==mod_additive)
			{
			  building_pools[e_class][idx]->sight_bonus+=bon->mod();
			}
		      else
			{
			  md = (building_pools[e_class][idx]->sight*bon->mod())/100;
			  building_pools[e_class][idx]->sight_bonus+=md;
			}
		      break;

		      //Shouldn't Happen
		    default:
		      break;
		    }
		}
	    }
	}
    }

  //Unit Class Bonus
  if(bon->type()==bonus_unit_class)
    {
      //Applies bonus to all templates with target subclass
      for(e_class=0; e_class < (int) unit_pools.size(); e_class++)
	{
	  for(idx=0; idx < (int) unit_pools[e_class].size(); idx++)
	    {
	      //If unit at current idx has subclass, applies bonus
	      if(unit_pools[e_class][idx]->subclasses[bon->target()]==1)
		{
		  switch(bon->unit_bonus())
		    {
		      //Gold Cost
		    case unit_bonus_gold:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_gold+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_gold*bon->mod())/100;
			  unit_pools[e_class][idx]->init_gold+=md;
			}
		      break;
		      //Food Cost
		    case unit_bonus_food:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_food+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_food*bon->mod())/100;
			  unit_pools[e_class][idx]->init_food+=md;
			}
		      break;
		      //Wood Cost
		    case unit_bonus_wood:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_wood+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_wood*bon->mod())/100;
			  unit_pools[e_class][idx]->init_wood+=md;
			}
		      break;
		      //Stone Cost
		    case unit_bonus_stone:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_stone+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_stone*bon->mod())/100;
			  unit_pools[e_class][idx]->init_stone+=md;
			}
		      break;
		      //HP
		    case unit_bonus_hp:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->hp_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->max_hp*bon->mod())/100;
			  unit_pools[e_class][idx]->hp_bonus+=md;
			}
		      break;
		      //Armor
		    case unit_bonus_armor:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->armor_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->armor*bon->mod())/100;
			  unit_pools[e_class][idx]->armor_bonus+=md;
			}
		      break;
		      //Move
		    case unit_bonus_move:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->move_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->max_move*bon->mod())/100;
			  unit_pools[e_class][idx]->move_bonus+=md;
			}
		      break;
		      //Melee
		    case unit_bonus_melee:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->melee_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->melee_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->melee_bonus+=md;
			}
		      break;
		      //Melee Pierce
		    case unit_bonus_melee_ap:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->melee_pierce_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->melee_pierce*bon->mod())/100;
			  unit_pools[e_class][idx]->melee_pierce_bonus+=md;
			}
		      break;
		      //Ranged
		    case unit_bonus_ranged:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->ranged_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->ranged_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->ranged_bonus+=md;
			}
		      break;
		      //Ranged Pierce
		    case unit_bonus_ranged_ap:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->ranged_pierce_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->ranged_pierce*bon->mod())/100;
			  unit_pools[e_class][idx]->ranged_pierce_bonus+=md;
			}
		      break;
		      //Building Attack
		    case unit_bonus_building:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->building_attack_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->building_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->building_attack_bonus+=md;
			}
		      break;
		      //Range
		    case unit_bonus_range:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->range_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->range*bon->mod())/100;
			  unit_pools[e_class][idx]->range_bonus+=md;
			}
		      break;
		      //Accuracy
		    case unit_bonus_accuracy:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->accuracy_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->accuracy*bon->mod())/100;
			  unit_pools[e_class][idx]->accuracy_bonus+=md;
			}
		      break;
		      //Sight
		    case unit_bonus_sight:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->sight_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->sight*bon->mod())/100;
			  unit_pools[e_class][idx]->sight_bonus+=md;
			}
		      break;

		      //Shouldn't happen
		    default:
		      break;
		    }
		}
	    }
	}
    }


  //Unit Bonus
  if(bon->type()==bonus_unit)
    {
      //Unit class is the target
      int target=bon->target();
      int u_class;

      //Looks for target unit class
      //Upgrades are in same class so prevents looking through all templates for each upgrade
      for(u_class=0; u_class < (int) unit_pools.size(); u_class++)
	{
	  for(idx=0; idx < (int) unit_pools[u_class].size(); idx++)
	    {
	      if(unit_pools[u_class][idx]->type==target) { e_class = u_class; break; }
	    }
	  if(unit_pools[u_class][idx-1]->type==target) { break; }
	}

      //Applies bonus to unit and all its upgrades
      while(target!=0)
	{
	  //Looks unit template then applies bonus
	  for(idx=0; idx < (int) unit_pools[e_class].size(); idx++)
	    {
	      //Unit found
	      if(unit_pools[e_class][idx]->type==target) 
		{
		  switch(bon->unit_bonus())
		    {
		      //Gold Cost
		    case unit_bonus_gold:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_gold+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_gold*bon->mod())/100;
			  unit_pools[e_class][idx]->init_gold+=md;
			}
		      break;
		      //Food Cost
		    case unit_bonus_food:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_food+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_food*bon->mod())/100;
			  unit_pools[e_class][idx]->init_food+=md;
			}
		      break;
		      //Wood Cost
		    case unit_bonus_wood:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_wood+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_wood*bon->mod())/100;
			  unit_pools[e_class][idx]->init_wood+=md;
			}
		      break;
		      //Stone Cost
		    case unit_bonus_stone:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->init_stone+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->init_stone*bon->mod())/100;
			  unit_pools[e_class][idx]->init_stone+=md;
			}
		      break;
		      //HP
		    case unit_bonus_hp:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->hp_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->max_hp*bon->mod())/100;
			  unit_pools[e_class][idx]->hp_bonus+=md;
			}
		      break;
		      //Armor
		    case unit_bonus_armor:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->armor_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->armor*bon->mod())/100;
			  unit_pools[e_class][idx]->armor_bonus+=md;
			}
		      break;
		      //Move
		    case unit_bonus_move:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->move_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->max_move*bon->mod())/100;
			  unit_pools[e_class][idx]->move_bonus+=md;
			}
		      break;
		      //Melee
		    case unit_bonus_melee:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->melee_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->melee_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->melee_bonus+=md;
			}
		      break;
		      //Melee Pierce
		    case unit_bonus_melee_ap:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->melee_pierce_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->melee_pierce*bon->mod())/100;
			  unit_pools[e_class][idx]->melee_pierce_bonus+=md;
			}
		      break;
		      //Ranged
		    case unit_bonus_ranged:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->ranged_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->ranged_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->ranged_bonus+=md;
			}
		      break;
		      //Ranged Pierce
		    case unit_bonus_ranged_ap:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->ranged_pierce_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->ranged_pierce*bon->mod())/100;
			  unit_pools[e_class][idx]->ranged_pierce_bonus+=md;
			}
		      break;
		      //Building Attack
		    case unit_bonus_building:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->building_attack_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->building_attack*bon->mod())/100;
			  unit_pools[e_class][idx]->building_attack_bonus+=md;
			}
		      break;
		      //Range
		    case unit_bonus_range:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->range_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->range*bon->mod())/100;
			  unit_pools[e_class][idx]->range_bonus+=md;
			}
		      break;
		      //Accuracy
		    case unit_bonus_accuracy:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->accuracy_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->accuracy*bon->mod())/100;
			  unit_pools[e_class][idx]->accuracy_bonus+=md;
			}
		      break;
		      //Sight
		    case unit_bonus_sight:
		      if(bon->mod_type()==mod_additive)
			{
			  unit_pools[e_class][idx]->sight_bonus+=bon->mod();
			}
		      else
			{
			  md = (unit_pools[e_class][idx]->sight*bon->mod())/100;
			  unit_pools[e_class][idx]->sight_bonus+=md;
			}
		      break;

		      //Shouldn't happen
		    default:
		      break;
		    }
		  break;
		}
	    }
	  //Updates target to be unit upgrade
	  target=unit_pools[e_class][idx]->upgrade;
	}
    }
}

//(Z) Resource Output
//Outputs current player info
void player :: resource_output()
{
  int k;

  //Sets top bar
  for(k=0; k<SCR_W; k++) { mvaddch(0,k, ' '); }

  //Resource Bar
  mvprintw(0, 0, "Pop: %d/%d  Gold: %d+%d  Food: %d+%d  Wood: %d+%d  Stone: %d+%d", pop_cur, pop_max, gold_res, gold_growth, food_res, food_growth, wood_res, wood_growth, stone_res, stone_growth);
  mvaddstr(0, SCR_W-5, "<ESC>");

  //Sets bottom bars
  for(k=0; k<SCR_W; k++) { mvaddch(SCR_H-1,k, ' '); mvaddch(SCR_H,k, ' '); }
}
