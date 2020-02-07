/********* CONTENTS **********/
//(A) Map Constructor and Destructor

//(B) Output Map
//void map::output_map()

//(C) Unit Functions

//(D) Building Functions

//(E) Line of Sight
//(Ea) Sight Corner
//(Eb) Sight Flat

//(F) Update Building Queue

//(G) Apply Bonus

//(H) Update Line of Sight
//(Ha) Update Line of Sight - Unit

//(AA) Construct Map - Plains
//(AB) Construct Map - River Rhine

//(ZA) Map Type Loc
//(ZB) Map Type Desc

/********* CONTENTS **********/

#include <ncurses.h>
#include "map.h"

//Map Types Localization
std::string map_type_names[] = { "Grassy Plains", "Rhine River", "Caspian Sea" };

//(A) Map Constructor
map :: map(enum map_type type)
{
  int x,y;
  //Adds Default Terrain, constructs tile matrix
  for(y=0; y<MAP_HEIGHT; y++)
    {
      std::vector<tile*> row;
      for(x=0; x<MAP_WIDTH; x++)
	{
	  row.push_back(new tile(tile_default));
	}
      tiles.push_back(row);
    }

  units = std::vector< std::vector<unit*> >(2, std::vector<unit*>(0, NULL));
  buildings = std::vector< std::vector<building*> >(2, std::vector<building*>(0, NULL));
  this->type=type;

  //Constructs the map randomly based on type
  switch(type)
    {
    case map_plains:
      this->bld_plains();
      break;

    case map_rhine:
      this->bld_rhine();
      break;

    case map_caspian:
      this->bld_caspian();
      break;

      //Shouldn't happen
    default:
      break;
    }
}

//(A) Map Destructor
map :: ~map()
{
  int k;
  for(k=0; k < (int) tiles.size(); k++)
    {
      tiles[k].clear();
    }
}

//(B) Map Output
void map :: output_map(int cur_p)
{
  int y,x;

  //Outputs tiles and entities
  for( y=0; y<MAP_HEIGHT; y++ )
    {
      std::vector< tile* > row = this->tiles[y];
      for(x=0; x<MAP_WIDTH; x++)
	{
	  row[x]->tile_output(x, y+1, players[cur_p]);
	}
    }
  attron(COLOR_PAIR(255));
}

//(C) Unit Function
//Add Unit
void map :: add_unit(int p, unit *u) 
{ 
  u->set_owner(players[p]);
  units[p].push_back(u); 
  get_tile( u->x(), u->y() )->set_entity( (entity*) u); 
  if(u->get_pop()<0) { players[p]->mod_cur_pop( -(u->get_pop()) ); }
  else { players[p]->mod_max_pop( u->get_pop() ); }
    
}
//Recruit Unit - Add but does not place on map
void map :: recruit_unit(int p, unit *u) 
{ 
  u->set_owner(players[p]);
  units[p].push_back(u); 
  if(u->get_pop()<0) { players[p]->mod_cur_pop( -(u->get_pop()) ); }
  else { players[p]->mod_max_pop( u->get_pop() ); }
    
}
//Remove Unit
void map :: remove_unit(int p, unit* u)
{
  int i;
  for(i=0; i < (int) units[p].size(); i++)
    {
      if(units[p][i]==u)
	{
	  remove_unit(p,i);
	  break;
	}
    }
}
//Remove Unit (Known idx)
void map :: remove_unit(int p, int i) 
{ 
  unit *u = units[p][i];
  units[p].erase(units[p].begin()+i); 
  if(u->get_pop()<0) { players[p]->mod_cur_pop( u->get_pop() ); }
  else { players[p]->mod_max_pop( -(u->get_pop()) ); }
  tiles[u->y()][u->x()]->set_entity(NULL);
  delete u;
  output_map(p);
}

//(D) Building Functions
//Add Building
void map :: add_building(int p, building *b) 
{ 
  b->set_owner(players[p]); 
  buildings[p].push_back(b); 
  get_tile( b->x(), b->y() )->set_entity( (entity*) b); 
  if(b->get_pop()<0) { players[p]->mod_cur_pop( -(b->get_pop()) ); }
  else { players[p]->mod_max_pop( b->get_pop() ); }
  players[p]->mod_gold_growth( b->get_gold()+b->get_gold_bonus() );
  players[p]->mod_food_growth( b->get_food()+b->get_food_bonus() );
  players[p]->mod_wood_growth( b->get_wood()+b->get_wood_bonus() );
  players[p]->mod_stone_growth( b->get_stone()+b->get_stone_bonus() );
  output_map(p);
}
//Remove Building
void map :: remove_building(int p, building* b)
{
  int i;
  for(i=0; i < (int) buildings[p].size(); i++)
    {
      if(buildings[p][i]==b)
	{
	  remove_building(p,i);
	  break;
	}
    }
}
//Remove Building (Known idx)
void map :: remove_building(int p, int i) 
{ 
  building *b = buildings[p][i];
  buildings[p].erase(buildings[p].begin()+i); 
  if(b->get_pop()<0) { players[p]->mod_cur_pop( b->get_pop() ); }
  else { players[p]->mod_max_pop( -(b->get_pop()) ); }
  players[p]->mod_gold_growth( -(b->get_gold()+b->get_gold_bonus()) );
  players[p]->mod_food_growth( -(b->get_food()+b->get_food_bonus()) );
  players[p]->mod_wood_growth( -(b->get_wood()+b->get_wood_bonus()) );
  players[p]->mod_stone_growth( -(b->get_stone()+b->get_stone_bonus()) );
  tiles[b->y()][b->x()]->set_entity(NULL);
  delete b;
  output_map(p);
}

//(D) Line of Sight
//Gets line of sight for given entity
//Buildings will block sight behind them
void map :: line_of_sight(entity *u, std::vector< std::vector<bool> > *potential, int reach, bool is_FOW)
{
  //Circles around u
  int kx, ky, dist;
  entity *top, *bottom, *left, *right;
  for(dist=1; dist<reach+1; dist++)
    {
      //Top and bottom rows
      for(kx = reach-dist; kx<reach+dist+1; kx++)
	{
	  //Checks if kx is within bounds
	  if( kx-reach+u->x() > 0 && kx-reach+u->x() < MAP_WIDTH )
	    {
	      //Checks if top column is in bound and there is an entity there
	      if(reach-dist-reach+u->y() > 0 && 
		 (top = get_tile(kx-reach+u->x(),reach-dist-reach+u->y())->get_entity()) ) 
		{ 
		  //Checks if building of different owner and building hasn't already been set as false
		  if(top->get_owner()!=u->get_owner()
		     && ( (top->get_entity_type()==entity_building && is_FOW) || !is_FOW )
		     && potential->at(reach-dist).at(kx) )
		    {
		      if(kx==reach) { 
			sight_flat(u, potential, kx, 0, reach-dist, -1, reach-dist);
		      }
		      else
			{
			  //Sets direction from u
			  int dx, dy=-1;
			  if(kx<reach) { dx=-1; }
			  else { dx=1; }
			  sight_corner(u, potential, kx, dx, reach-dist, dy, reach-dist); 
			}
		    }
		}
	      //Checks if bottom column is in bound
	      if(reach+dist-reach+u->y() < MAP_HEIGHT && 
		 (bottom = get_tile(kx-reach+u->x(),reach+dist-reach+u->y())->get_entity()) ) 
		{ 
		  //Checks if building of different owner and building hasn't already been set as false
		  if(bottom->get_owner()!=u->get_owner() 
		     && ( (bottom->get_entity_type()==entity_building && is_FOW) || !is_FOW )
		     && potential->at(reach+dist).at(kx)  )
		    {
		      if(kx==reach) { 
			sight_flat(u, potential, kx, 0, reach+dist, 1, reach-dist);
		      }
		      else
			{
			  //Sets direction from u
			  int dx, dy=1;
			  if(kx<reach) { dx=-1; }
			  else { dx=1; }
			  sight_corner(u, potential, kx, dx, reach+dist, dy, reach-dist); 
			}
		    }
		}
	    }
	}
      //Left and right columns
      for(ky = 0; ky<reach+dist+1; ky++)
	{
	  //Checks if ky is within bounds
	  if( ky-reach+u->y() > 0 && ky-reach+u->y() < MAP_HEIGHT )
	    {
	      //Checks if left column is in bound and there is an entity there
	      if(reach-dist-reach+u->x() > 0 && 
		 (left = get_tile(reach-dist-reach+u->x(),ky-reach+u->y())->get_entity()) ) 
		{ 
		  //Checks if building of different owner and building hasn't already been set as false
		  if(left->get_owner()!=u->get_owner() 
		     && ( (left->get_entity_type()==entity_building && is_FOW) || !is_FOW )
		     && potential->at(ky).at(reach-dist) )
		    {
		      if(ky==reach) { 
			sight_flat(u, potential, reach-dist, -1, ky, 0, reach-dist);
		      }
		      else
			{
			  //Sets direction from u
			  int dx=-1, dy;
			  if(ky<reach) { dy=-1; }
			  else { dy=1; }
			  sight_corner(u, potential, reach-dist, dx, ky, dy, reach-dist); 
			}
		    }
		}
	      //Checks if right column is in bound
	      if(reach+dist-reach+u->x() < MAP_WIDTH && 
		 (right = get_tile(reach+dist-reach+u->x(),ky-reach+u->y())->get_entity()) ) 
		{ 
		  //Checks if building of different owner and building hasn't already been set as false
		  if(right->get_owner()!=u->get_owner() 
		     && ( (right->get_entity_type()==entity_building && is_FOW) || !is_FOW )
		     && potential->at(ky).at(reach+dist)  )
		    {
		      if(ky==reach) { 
			sight_flat(u, potential, reach+dist, 1, ky, 0, reach-dist);
		      }
		      else
			{
			  //Sets direction from u
			  int dx=1, dy;
			  if(ky<reach) { dy=-1; }
			  else { dy=1; }
			  sight_corner(u, potential, reach+dist, dx, ky, dy, reach-dist); 
			}
		    }
		}
	    }
	}
    }
}

//(Ea) Sight Corner
void map :: sight_corner(entity *u, std::vector< std::vector<bool> > *potential, int x, int dx, int y, int dy, int rem_dist)
{
  //dx and dy
  if(x+dx>=0 && x+dx < (int) potential->size() && y+dy>=0 && y+dy < (int) potential->size()) 
    { 
      potential->at(y+dy).at(x+dx)=false;
      potential->at(y).at(x+dx)=false;
      potential->at(y+dy).at(x)=false;

      //If distance remains, call on idx with shift dx, dy
      if(rem_dist>0)
	{
	  sight_corner(u, potential, x+dx, dx, y+dy, dy, rem_dist-1);
	  sight_corner(u, potential, x+dx, dx, y+2*dy, dy, rem_dist-1);
	  sight_corner(u, potential, x+2*dx, dx, y+dy, dy, rem_dist-1);
	}
    }
}

//(Eb) Sight Flat
void map :: sight_flat(entity *u, std::vector< std::vector<bool> > *potential, int x, int dx, int y, int dy, int rem_dist)
{
  //dx and dy
  if(x>0 && x < (int) potential->size()-1 && y>0 && y < (int) potential->size()-1) 
    { 
      potential->at(y+dy).at(x+dx)=false;

      //Looking horizontally
      if(dx!=0)
	{
	  //Does above
	  if(y-1>0) { potential->at(y-1).at(x+dx)=false; }

	  //Does Below
	  if(y+1 < (int) potential->size()) { potential->at(y+1).at(x+dx)=false; }
	}

      //Looking vertically
      else
	{
	  //Does above
	  if(x-1>0) { potential->at(y+dy).at(x-1)=false; }

	  //Does Below
	  if(x+1 < (int) potential->size()) { potential->at(y+dy).at(x+1)=false; }
	}

      //If distance remains, call on idx with shift dx, dy
      if(rem_dist>0)
	{
	  sight_flat(u, potential, x+dx, dx, y+dy, dy, rem_dist-1);

	  //Calls on one further out
	  //Horizontal
	  if(dy==0) 
	    { 
	      sight_flat(u, potential, x+dx, dx, y-1, dy, rem_dist-1);
	      sight_flat(u, potential, x+dx, dx, y+1, dy, rem_dist-1);
	    }
	  //Vertical
	  else
	    {
	      sight_flat(u, potential, x-1, dx, y+dy, dy, rem_dist-1);
	      sight_flat(u, potential, x+1, dx, y+dy, dy, rem_dist-1);
	    }
	}
    }
}

//(F) Update Building Queue
//Updates recruit and research remaining turnscounters
//Handles recruitment and research completion
//Heals units in garrison by 15% (Garrison heal may become a variable in the future)
void map :: update_building_queue(int cur_p)
{
  int i;
  player *p = get_player(cur_p);
  building *b;


  //Loops through every building owned by the player
  //Decrements recruitment and research turns by 1
  //If they reach 0 it is completed
  for(i=0; i < (int) buildings[cur_p].size(); i++)
    {
      b = buildings[cur_p][i];

      //Research effects are always carried out when completed
      if(b->researching())
	{
	  b->mod_research_time(-1);
	  int t = b->get_research();

	  //If another building completed research, sets as completed
	  if(p->tech_researched(t))
	    {
	      b->mod_research_time(-b->rem_research_time());
	      b->set_research(tech_default);

	      //Gets tech player back research costs
	      tech *tch = p->get_tech(t);
	      p->purchase(-tch->gold(), -tch->food(), -tch->wood(), -tch->stone());
	    }

	  //If research was complete, sets research as completed
	  else if(b->rem_research_time()==0)
	    {
	      p->set_researched(t);
	      //If tech has a bonus/es, applies them
	      if(p->get_tech(t)->get_bonus()->size() > 0)
		{
		  int q;
		  for(q=0; q < (int) p->get_tech(t)->get_bonus()->size(); q++)
		    {
		      apply_bonus( p->get_tech(t)->get_bonus()->at(q), cur_p );
		    }
		}
	      b->set_research(tech_default);
	    }
	}

      //Recruitment is only finished if the building garrison is not full and player has available pop
      if(b->recruiting())
	{
	  b->mod_recruit_time(-1);

	  //Checks if recruitment was finished
	  if(b->rem_recruit_time()==0)
	    {
	      int uclass = b->get_recruit_class();
	      unit_template *u = p->get_unit(uclass, p->get_unit_idx(uclass, b->get_recruit()) );

	      //If building is garrisonable and player has enough pop, recruits
	      if(b->garrisonable() 
		 && p->get_cur_pop()-p->get_max_pop() <= u->pop )
		{
		  recruit_unit(cur_p, new unit(u, b->x(), b->y()));
		  b->add_garrison( (entity*) get_unit(cur_p, num_units(cur_p)-1));
		}
	      //Otherwise, adds another turn to time
	      else
		{
		  b->mod_recruit_time(1);
		}
	    }
	}
      /* Broken for some reason
       * Seg faults when attempting to access entity* gar's data members 
      //Heals garrison if any
      if(b->get_garrison_size()>0)
	{
	  int k, end;

	  if(!just_recruited) { end=b->get_garrison_size(); }
	  else { end=b->get_garrison_size()-1; }
	  for(k=0; k<end; k++)
	    {
	      entity *gar = b->get_garrison(i);
  //REMOVE
	      mvprintw(SCR_H,0, "check ");
  refresh();
  getch();

	      //If HP is below full, adds 10% to HP
	      if(gar->get_hp() < gar->get_max_hp() + gar->get_hp_bonus())
		{
		  int hp_heal = ((gar->get_max_hp()+gar->get_hp_bonus())*10)/100;

		  gar->mod_hp(hp_heal);

		  //If hp went over, reduces it to max
		  if(gar->get_hp() > gar->get_max_hp() + gar->get_hp_bonus())
		    {
		      gar->mod_hp(gar->get_hp() -(gar->get_max_hp() + gar->get_hp_bonus()));
		    }
		}
	    }
	}
      */
    }
}

//(G) Apply bonus
//Applies bonus to all entites if needed
//Then call player apply_bonus() function, updating age/entity templates
void map :: apply_bonus(bonus *bon, int cur_p)
{

  players[cur_p]->apply_bonus(bon);

  //Applies bonus to exiting units/buildings - Probably should have used pointers but oh well
  int idx, md;

  //Building Bonus
  if(bon->type()==bonus_bldg)
    {
      //Finds building
      for(idx=0; idx < (int) buildings[cur_p].size(); idx++)
	{
	  //Target was found, updates template
	  if(buildings[cur_p][idx]->get_type()==bon->target())
	    {
	      building *cur_b = buildings[cur_p][idx];
	      switch(bon->building_bonus())
		{
		  //HP
		case bldg_bonus_hp:
		  if(bon->mod_type()==mod_additive)
		    {
		      cur_b->mod_hp_bonus(bon->mod());
		      cur_b->mod_hp(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_max_hp()*bon->mod())/100;
		      cur_b->mod_hp_bonus(md);
		      cur_b->mod_hp(md);
		    }
		  break;
		  //Armor
		case bldg_bonus_armor:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_armor_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_armor()*bon->mod())/100;
		      cur_b->mod_armor_bonus(md);
		    }
		  break;
		  //Attack
		case bldg_bonus_attack:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_attack_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_attack()*bon->mod())/100;
		      cur_b->mod_attack_bonus(md);
		    }
		  break;
		  //Attack Pierce
		case bldg_bonus_ap:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_ap_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_attack_ap()*bon->mod())/100;
		      cur_b->mod_ap_bonus(md);
		    }
		  break;
		  //Gold
		case bldg_bonus_gold:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_gold_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_gold()*bon->mod())/100;
		      cur_b->mod_gold_bonus(md);
		    }
		  break;
		  //Food
		case bldg_bonus_food:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_food_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_food()*bon->mod())/100;
		      cur_b->mod_food_bonus(md);
		    }
		  break;
		  //Wood
		case bldg_bonus_wood:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_wood_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_wood()*bon->mod())/100;
		      cur_b->mod_wood_bonus(md);
		    }
		  break;
		  //Stone
		case bldg_bonus_stone:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_stone_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_stone()*bon->mod())/100;
		      cur_b->mod_stone_bonus(md);
		    }
		  break;
		  //Range
		case bldg_bonus_range:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_range_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_range()*bon->mod())/100;
		      cur_b->mod_range_bonus(md);
		    }
		  break;
		  //Accuracy
		case bldg_bonus_accuracy:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_accuracy_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->get_accuracy()*bon->mod())/100;
		      cur_b->mod_accuracy_bonus(md);
		    }
		  break;
		  //Sight
		case bldg_bonus_sight:
		  if(bon->mod_type()==mod_additive)
		    {
		      buildings[cur_p][idx]->mod_sight_bonus(bon->mod());
		    }
		  else
		    {
		      md = (cur_b->sight()*bon->mod())/100;
		      cur_b->mod_sight_bonus(md);
		    }
		  break;

		  //Shouldn't Happen
		default:
		  break;
		}
	    }
	}
    }

  //Unit or Unit Class bonus
  if(bon->type()==bonus_unit || bon->type()==bonus_unit_class)
    {
      //Finds building
      for(idx=0; idx < (int) units[cur_p].size(); idx++)
	{
	  //Target was found, updates template
	  if( ( bon->type()==bonus_unit &&
	        units[cur_p][idx]->get_type()==bon->target() )
	      ||
	      ( bon->type()==bonus_unit_class &&
		units[cur_p][idx]->has_subclass( (unit_class) bon->target()) )
	     ) {
	    //Applies update
	    switch(bon->unit_bonus())
		{
		  //HP
		case unit_bonus_hp:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_hp_bonus(bon->mod());
		      units[cur_p][idx]->mod_hp(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_max_hp()*bon->mod())/100;
		      units[cur_p][idx]->mod_hp_bonus(md);
		      units[cur_p][idx]->mod_hp(md);
		    }
		  break;
		  //Armor
		case unit_bonus_armor:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_armor_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_armor()*bon->mod())/100;
		      units[cur_p][idx]->mod_armor_bonus(md);
		    }
		  break;
		  //Move
		case unit_bonus_move:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_move_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_max_move()*bon->mod())/100;
		      units[cur_p][idx]->mod_move_bonus(md);
		    }
		  break;
		  //Melee
		case unit_bonus_melee:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_melee_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_melee()*bon->mod())/100;
		      units[cur_p][idx]->mod_melee_bonus(md);
		    }
		  break;
		  //Melee Pierce
		case unit_bonus_melee_ap:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_melee_ap_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_melee_ap()*bon->mod())/100;
		      units[cur_p][idx]->mod_melee_ap_bonus(md);
		    }
		  break;
		  //Ranged
		case unit_bonus_ranged:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_ranged_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_ranged()*bon->mod())/100;
		      units[cur_p][idx]->mod_ranged_bonus(md);
		    }
		  break;
		  //Ranged Pierce
		case unit_bonus_ranged_ap:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_ranged_ap_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_ranged_ap()*bon->mod())/100;
		      units[cur_p][idx]->mod_ranged_ap_bonus(md);
		    }
		  break;
		  //Building Attack
		case unit_bonus_building:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_building_attack_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_building_attack()*bon->mod())/100;
		      units[cur_p][idx]->mod_building_attack_bonus(md);
		    }
		  break;
		  //Range
		case unit_bonus_range:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_range_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_range()*bon->mod())/100;
		      units[cur_p][idx]->mod_range_bonus(md);
		    }
		  break;
		  //Accuracy
		case unit_bonus_accuracy:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_accuracy_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->get_accuracy()*bon->mod())/100;
		      units[cur_p][idx]->mod_accuracy_bonus(md);
		    }
		  break;
		  //Sight
		case unit_bonus_sight:
		  if(bon->mod_type()==mod_additive)
		    {
		      units[cur_p][idx]->mod_sight_bonus(bon->mod());
		    }
		  else
		    {
		      md = (units[cur_p][idx]->sight()*bon->mod())/100;
		      units[cur_p][idx]->mod_sight_bonus(md);
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

//(H) Update Line of Sight
void map :: update_los(int cur_p)
{
  int i,j;
  //FOW map for player
  std::vector< std::vector<bool> > *fow_map = players[cur_p]->fow_map();

  //Sets everything to false
  for(i=0; i < (int) fow_map->size(); i++)
    {
      for(j=0; j < (int) fow_map->at(i).size(); j++)
	{
	  fow_map->at(i).at(j) = false;
	}
    }

  //Goes through every building
  for(i=0; i < (int) buildings[cur_p].size(); i++)
    {
      update_los_entity( (entity *) buildings[cur_p][i], cur_p);
    }

  //Goes through every unit
  for(i=0; i < (int) units[cur_p].size(); i++)
    {
      update_los_entity( (entity *) units[cur_p][i], cur_p);
    }
}

//(Ha) Update Line of Sight - Entity
void map :: update_los_entity(entity *e, int cur_p)
{
  int x,y;

  int ex=e->x(), ey=e->y();
  int sight=e->sight()+e->sight_bonus();

  //FOW map for player
  std::vector< std::vector<bool> > *fow_map = players[cur_p]->fow_map();

  //FOW map for current entity
  //LoS algorithm needs all values set to true initially but that results in more LoS than desired
  std::vector< std::vector<bool> > fow_true( (sight*2)+1, std::vector<bool>((sight*2)+1,false) );

  std::vector< std::vector<bool> > fow_calc( (sight*2)+1, std::vector<bool>((sight*2)+1,true) );
  line_of_sight(e, &fow_calc, sight, true);

  //Goes through building's sight array and updates player FOW map
  for(y = ey-sight; y < ey+sight+1; y++)
    {
      for( x=ex-sight; x < ex+sight+1; x++)
	{
	  //Updates true FoW
	  if(fow_calc[y-ey+sight][x-ex+sight]) { fow_true[y-ey+sight][x-ex+sight]=true; }

	  //Checks if not out of bounds
	  if(x>=0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      //If tile is in FOW, updates
	      if(!players[cur_p]->has_sight(x,y))
		{
		  fow_map->at(y).at(x) = fow_true[y-ey+sight][x-ex+sight];
		}
	    }
	}
    }
}


/*************** MAP DEFINITIONS ******************/

//(AA) Plains
void map :: bld_plains()
{
  int x,y;

  //Sets player starting positions
  start[0][0]=5, start[0][1]=MAP_HEIGHT-MAP_HEIGHT/4;
  start[1][0]=MAP_WIDTH-5, start[1][1]=MAP_HEIGHT/4;
  
  //Adds base resources
  //Woods Base Vertical
  for(y=start[1][1]+4; y<start[1][1]+6; y++)
    {
      for(x=start[0][0]-1; x<start[0][0]+2; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Woods Base Horizontal
  for(y=start[1][1]-1; y<start[1][1]+2; y++)
    {
      for(x=start[0][0]+10; x<start[0][0]+12; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Gold Base
  y=start[1][1]-2;
  for(x=start[0][0]; x<start[0][0]+2; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
    }
  //Stone Base
  x=start[0][0]-2;
  for(y=start[1][1]; y<start[1][1]+3; y++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
    }

  //Expansion resources
  //Woods Expansion
  for(y=start[1][1]+10; y<start[1][1]+12; y++)
    {
      for(x=start[0][0]-1; x<start[0][0]+2; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Gold Expansion
  y=start[1][1]+14;
  for(x=start[0][0]; x<start[0][0]+2; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
    }
  //Stone Expansion
  y=start[1][1]+12;
  for(x=start[0][0]+6; x<start[0][0]+8; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
    }

  //Center Resources
  //Woods Center
  for(y=(MAP_HEIGHT/2)-7; y<(MAP_HEIGHT/2)-3; y++)
    {
      for(x=(MAP_WIDTH/2)-2; x<(MAP_WIDTH/2)+3; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
	}
    }
  //Gold Center
  for(y=(MAP_HEIGHT/2)-1; y<(MAP_HEIGHT/2); y++)
    {
      for(x=(MAP_WIDTH/2)-1; x<(MAP_WIDTH/2)+1; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
	}
    }
  //Stone Center
  for(y=(MAP_HEIGHT/2)-1; y<(MAP_HEIGHT/2)+1; y++)
    {
      for(x=(MAP_WIDTH/2)-5; x<(MAP_WIDTH/2)-3; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
	}
    }
}


//(AB) River Rhine
void map :: bld_rhine()
{
  int x,y;

  //Sets player starting positions
  start[0][0]=5, start[0][1]=MAP_HEIGHT-MAP_HEIGHT/4;
  start[1][0]=MAP_WIDTH-5, start[1][1]=MAP_HEIGHT/4;
  
  //Adds base resources
  //Woods Base Vertical
  for(y=start[1][1]+4; y<start[1][1]+6; y++)
    {
      for(x=start[0][0]-1; x<start[0][0]+2; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Woods Base Horizontal
  for(y=start[1][1]-1; y<start[1][1]+2; y++)
    {
      for(x=start[0][0]+10; x<start[0][0]+12; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Gold Base
  y=start[1][1]-2;
  for(x=start[0][0]; x<start[0][0]+2; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
    }
  //Stone Base
  x=start[0][0]-2;
  for(y=start[1][1]; y<start[1][1]+3; y++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
    }

  //River
  x=MAP_WIDTH/2 - 10;
  for(y=0; y<MAP_HEIGHT; y++)
    {
      tiles[y][x-6]->update_tile(tile_coast); 
      tiles[y][x-5]->update_tile(tile_water); 
      tiles[y][x-4]->update_tile(tile_water); 
      tiles[y][x-3]->update_tile(tile_water); 
      tiles[y][x-2]->update_tile(tile_water); 
      tiles[y][x-1]->update_tile(tile_water); 
      tiles[y][x]->update_tile(tile_water); 
      tiles[y][x+1]->update_tile(tile_water); 
      tiles[y][x+2]->update_tile(tile_water); 
      tiles[y][x+3]->update_tile(tile_water); 
      tiles[y][x+4]->update_tile(tile_water); 
      tiles[y][x+5]->update_tile(tile_water); 
      tiles[y][x+6]->update_tile(tile_coast); 
      x+=1;
    }
  //River Crossing
  for(y=6; y<9; y++)
    {
      for(x=0; x<11; x++)
	{
	  tiles[y][x+31+(y-6)]->update_tile(tile_water_shallow); 
	  tiles[MAP_HEIGHT-y][MAP_WIDTH-(x+31+(y-6))+1]->update_tile(tile_water_shallow); 
	}
    }

  
  //Expansion resources
  //Woods Expansion
  for(y=start[1][1]+10; y<start[1][1]+13; y++)
    {
      for(x=start[0][0]-1; x<start[0][0]+4; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
      }
    }
  //Gold Expansion
  y=start[1][1]+14;
  for(x=start[0][0]; x<start[0][0]+2; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
    }
  //Stone Expansion
  y=start[1][1]+12;
  for(x=start[0][0]+6; x<start[0][0]+8; x++)
    {
      tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
      tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
    }
  
  //Center Resources
  //Woods Center
  for(y=(MAP_HEIGHT/2)-7; y<(MAP_HEIGHT/2)-3; y++)
    {
      for(x=(MAP_WIDTH/2)-2-20; x<(MAP_WIDTH/2)+3-20; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_forest); 
	}
    }
  //Gold Center
  for(y=(MAP_HEIGHT/2)-1; y<(MAP_HEIGHT/2); y++)
    {
      for(x=(MAP_WIDTH/2)-1-10; x<(MAP_WIDTH/2)+1-10; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_gold); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
	}
    }
  //Stone Center
  for(y=(MAP_HEIGHT/2)-1; y<(MAP_HEIGHT/2)+1; y++)
    {
      for(x=(MAP_WIDTH/2)-5-10; x<(MAP_WIDTH/2)-3-10; x++)
	{
	  tiles[MAP_HEIGHT-y][x]->update_tile(tile_stone); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_stone); 
	}
    }
  
}

//(AC) Caspian
void map :: bld_caspian()
{
  int x,y;

  //Sets player starting positions
  start[0][0]=5, start[0][1]=MAP_HEIGHT-MAP_HEIGHT/4;
  start[1][0]=MAP_WIDTH-5, start[1][1]=MAP_HEIGHT/4;
  

  //Coast
  int offset = 15;
  for(y=3; y<4; y++)
    {
      for(x=offset; x<MAP_WIDTH-offset; x++)
	{
	  tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_coast);
	  tiles[y][x]->update_tile(tile_coast);
	}
    }
  for(y=4; y<MAP_HEIGHT/2 + 1; y++)
    {
      tiles[MAP_HEIGHT-y-1][offset-1]->update_tile(tile_coast);
      tiles[y][offset-1]->update_tile(tile_coast);
      tiles[MAP_HEIGHT-y-1][MAP_WIDTH-offset]->update_tile(tile_coast);
      tiles[y][MAP_WIDTH-offset]->update_tile(tile_coast);
      for(x=offset; x<MAP_WIDTH-offset; x++)
	{
	  tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_water);
	  tiles[y][x]->update_tile(tile_water);
	}
      offset--;
    }

  
  //Adds base resources
  //Woods Base Vertical
  for(y=start[1][1]+3; y<start[1][1]+6; y++)
    {
      for(x=start[0][0]-3; x<start[0][0]+1; x++) { 
	tiles[MAP_HEIGHT-y][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x-1]->update_tile(tile_forest); 
      }
    }
  //Woods Base Horizontal
  for(y=start[1][1]-4; y<start[1][1]-1; y++)
    {
      for(x=start[0][0]+3; x<start[0][0]+6; x++) { 
	tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_forest); 
	tiles[y][MAP_WIDTH-x-1]->update_tile(tile_forest); 
      }
    }
  //Gold Base
  y=start[1][1]-3;
  for(x=start[0][0]-3; x<start[0][0]; x++)
    {
      tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_gold); 
      tiles[y][MAP_WIDTH-x-1]->update_tile(tile_gold); 
    }
  //Stone Base
  x=start[0][0]-4;
  for(y=start[1][1]-1; y<start[1][1]+2; y++)
    {
      tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_stone); 
      tiles[y][MAP_WIDTH-x-1]->update_tile(tile_stone); 
    }

  //Expansion
  //Woods Expansion
  for(y=start[1][1]-4; y<start[1][1]-1; y++)
    {
      for(x=start[0][0]; x<start[0][0]+5; x++) { 
	tiles[y][x]->update_tile(tile_forest); 
	tiles[MAP_HEIGHT-y-1][MAP_WIDTH-x-1]->update_tile(tile_forest); 
      }
    }
  //Gold Expansion
  y=start[1][1]-3;
  for(x=start[0][0]-4; x<start[0][0]-2; x++)
    {
      tiles[y][x]->update_tile(tile_gold); 
      tiles[MAP_HEIGHT-y-1][MAP_WIDTH-x-1]->update_tile(tile_gold); 
    }
  //Stone Expansion
  x=start[0][0]-4;
  for(y=start[1][1]-1; y<start[1][1]+2; y++)
    {
      tiles[y][x]->update_tile(tile_stone); 
      tiles[MAP_HEIGHT-y-1][MAP_WIDTH-x-1]->update_tile(tile_stone); 
    }

  //Gold Center
  for(y=1; y<2; y++)
    {
      for(x=(MAP_WIDTH/2)-2; x<(MAP_WIDTH/2)+2; x++)
	{
	  tiles[MAP_HEIGHT-y-1][x]->update_tile(tile_gold); 
	  tiles[y][MAP_WIDTH-x]->update_tile(tile_gold); 
	}
    }
  
}


//(ZA) Map Type Loc
std::string map_type_loc(enum map_type type) { return map_type_names[type]; }

//(ZB) Map Type Desc
std::vector<std::string> get_map_desc(enum map_type type)
{
  std::vector<std::string> ret;
  switch(type)
    {
    case map_plains:
      ret.push_back("A simple map featuring average");
      ret.push_back("but adequate resource amounts.");
      ret.push_back("There are no bodies of water to");
      ret.push_back("be found in this land.");
      ret.push_back("This map provides the most pure");
      ret.push_back("land-ony skirmish experience.");
      break;

    case map_rhine:
      ret.push_back("Divided by a great river down");
      ret.push_back("the center of the map, both");
      ret.push_back("players have an opportunity to");
      ret.push_back("gain control of the river");
      ret.push_back("through its crossings on land or");
      ret.push_back("through a river fleet.");
      break;

    case map_caspian:
      ret.push_back("Centerd around a great sea, this");
      ret.push_back("map offers much in the way of");
      ret.push_back("naval combat. Naval-based");
      ret.push_back("civilizations will do well to");
      ret.push_back("focus on controlling this sea,");
      ret.push_back("otherwise the coast is the goal.");
      break;

    default:
      ret.push_back("NO LOCALIZATION FOUND");
      break;
    }
  return ret;
}

