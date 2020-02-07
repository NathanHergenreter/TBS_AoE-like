#include <cstdlib>
#include <vector>
#include <ncurses.h>
#include "combat.h"

/********* CONTENTS **********/

//(A) Combat

//(B) Combat Calculations

//(C) Combat Results

//(Z) Get Distance
int get_distance(entity *, entity *);

/********* CONTENTS **********/


//(A) Combat
//Calculates damage and HP changes, removes an entity if it dies
//Damage is dealt in halves (if odd, dam/2+1 is first)
//If both are set to die, a will live
void combat(entity *a, entity *d, enum combat_type type)
{
  int a_dam, d_dam;

  combat_calc(a, d, a_dam, d_dam, type,-1);

  a->mod_hp(-d_dam);
  d->mod_hp(-a_dam);
}

//(B) Combat Calculations
void combat_calc(entity *a, entity *d, int &a_dam, int &d_dam, enum combat_type type, int accuracy)
{
  a_dam=0, d_dam=0;

  //First determines stats in use
  enum entity_type a_type=a->get_entity_type(), d_type = d->get_entity_type();
  int a_dam_base=0, a_ap=0, d_dam_base=0, d_ap=0;
  int dist=1;
  if(d->get_range()>0)
    {
      dist = get_distance(d,a);
    }

  //Attacker Damage Calc (NOTE - attacker is always within range)
  //Checks if attacker is building or unit
  //Buildings always use regular attack
  if(a_type==entity_building)
    {
      int a_acc;
      if(accuracy==-1) { a_acc =  a->get_accuracy() + rand() % (100-a->get_accuracy()); }
      else { a_acc = a->get_accuracy() + ( (100-a->get_accuracy() )*accuracy)/100; }
      a_dam_base = ((building*) a)->get_attack() + ((building*) a)->get_attack_bonus();
      a_dam_base = (a_dam_base*a_acc)/100;
      a_ap = ((building*) a)->get_attack_ap()+((building*) a)->ap_bonus();
    }
  //Attack is unit
  else
    {
      //Defender is building, uses attackers building damage
      if(d_type==entity_building)
	{
	  a_dam_base = ((unit*) a)->get_building_attack() + ((unit*) a)->get_building_attack_bonus();

	  //Determines ap on combat type
	  if(type==combat_melee) { a_ap = ((unit*) a)->get_melee_ap() + ((unit*) a)->get_melee_ap_bonus(); }
	  else { a_ap = ((unit*) a)->get_ranged_ap() + ((unit*) a)->get_ranged_ap_bonus(); }
	}
      //Defender is unit
      //Melee combat, uses melee stats
      else if(type==combat_melee)
	{
	  a_dam_base = ((unit*) a)->get_melee()+ ((unit*) a)->get_melee_bonus();
	  a_ap = ((unit*) a)->get_melee_ap() + ((unit*) a)->get_melee_ap_bonus();
	}
      //Otherwise, ranged stats
      else
	{
	  int a_acc;
	    if(accuracy==-1) { a_acc =  a->get_accuracy() + rand() % (100-a->get_accuracy()); }
	    else { a_acc = a->get_accuracy() + ( (100-a->get_accuracy() )*accuracy)/100; }
	  a_dam_base = ((unit*) a)->get_ranged()+ ((unit*) a)->get_ranged_bonus();
	  a_dam_base = (a_dam_base*a_acc)/100;
	  a_ap = ((unit*) a)->get_ranged_ap() + ((unit*) a)->get_ranged_ap_bonus();
	}
    }

  //Defender Damage Calc
  //Checks if defender is building or unit
  //Buildings always use regular attack
  if(d_type==entity_building)
    {
      //Checks if defender is within range of attacker, otherwise damage is 0
      if( d->get_range() >= dist )
	{
	  int d_acc;
	  if(accuracy==-1) { d_acc =  d->get_accuracy() + rand() % (100-d->get_accuracy()); }
	  else { d_acc = d->get_accuracy() + ( (100-d->get_accuracy() )*accuracy)/100; }
	  d_dam_base = ((building*) d)->get_attack() + ((building*) d)->get_attack_bonus();
	  d_dam_base = (d_dam_base*d_acc)/100;
	  d_ap = ((building*) d)->get_attack_ap()+((building*) d)->ap_bonus();
	}
    }
  //Defender is unit
  else
    {
      //Attacker is building, uses defenders building damage
      if(a_type==entity_building)
	{
	  //Checks if defender is within range of attacker, otherwise damage is 0
	  if( d->get_range() >= dist )
	    {
	      d_dam_base = ((unit*) d)->get_building_attack() + ((unit*) d)->get_building_attack_bonus();

	      //Determines ap on combat type
	      if(type==combat_melee) { d_ap = ((unit*) d)->get_melee_ap() + ((unit*) d)->get_melee_ap_bonus(); }
	      else { d_ap = ((unit*) d)->get_ranged_ap() + ((unit*) d)->get_ranged_ap_bonus(); }
	    }
	}
      //Attacker is unit
      //Melee combat, uses melee stats always in range
      else if(type==combat_melee)
	{
	  d_dam_base = ((unit*) d)->get_melee()+ ((unit*) d)->get_melee_bonus();
	  d_ap = ((unit*) d)->get_melee_ap() + ((unit*) d)->get_melee_ap_bonus();
	}
      //Otherwise, ranged stats
      else
	{
	  //Checks if defender is within range of attacker, otherwise damage is 0
	  if( d->get_range() >= dist )
	    {
	      int d_acc;
	      if(accuracy==-1) { d_acc =  d->get_accuracy() + rand() % (100-d->get_accuracy());}
	      else { d_acc = d->get_accuracy() + ( (100-d->get_accuracy() )*accuracy)/100; }
	      d_dam_base = ((unit*) d)->get_ranged()+ ((unit*) d)->get_ranged_bonus();
	      d_dam_base = (d_dam_base*d_acc)/100;
	      d_ap = ((unit*) d)->get_ranged_ap() + ((unit*) d)->get_ranged_ap_bonus();
	    }
	}
    }

  //Damage is base damage divided by effective armor
  //Effective armor is the difference between receiver's armor and dealer's armor pierce
  //If effective armor is less than 0, it is set to 0
  int a_arm = a->get_armor()-d_ap, d_arm = d->get_armor()-a_ap;
  if(a_arm<0) { a_arm=0; }
  if(d_arm<0) { d_arm=0; }

  //Calculates damages
  a_dam = a_dam_base/(d_arm+1);
  //Checks if defender is alive after first attack, if combat is ended
  if(d->get_hp()-a_dam > 0)
    {
      d_dam = d_dam_base/(a_arm+1);

      //Checks if attacker is alive after defender's first attack
      if(a->get_hp()-d_dam > 0)
	{
	  a_dam += a_dam;

	  //Checks if defender is still alive after attacker's second attack
	  if(d->get_hp()-a_dam > 0)
	    {
	      d_dam += d_dam;
	    }
	}
    }
}

//(C) Combat Results
void combat_results(entity *a, entity *d, enum combat_type type)
{
  //Initialization
  mvaddstr(SCR_H-1, 0, "                                     ");
  mvaddstr(SCR_H, 0, "                                     ");
  int a_dam, a_dam_max, a_hp, a_hp_max, d_dam, d_dam_max, d_hp, d_hp_max;
  std::string a_loc = a->get_name();
  std::string d_loc = d->get_name();

  //Calculates damage and resulting HP
  //If HP is below 0, displays as 0
  combat_calc(a, d, a_dam, d_dam, type, 0);
  combat_calc(a, d, a_dam_max, d_dam_max, type, 100);
  a_hp=a->get_hp()-d_dam;
  a_hp_max=a->get_hp()-d_dam_max;
  if(a_hp<0) { a_hp=0; }
  if(a_hp_max<0) { a_hp_max=0; }
  d_hp=d->get_hp()-a_dam;
  d_hp_max=d->get_hp()-a_dam_max;
  if(d_hp<0) { d_hp=0; }
  if(d_hp_max<0) { d_hp_max=0; }

  //Combat Result info
  //Attacker
  attron( COLOR_PAIR(210+a->get_owner()->get_color() ) );
  mvprintw(SCR_H-1, 0, a_loc.c_str());
  attron(COLOR_PAIR(255));
  printw(" %d->",a->get_hp());
  //Damage wasn't ranged
  if(a_hp==a_hp_max)
    {
      if(a_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d",a_hp);
    }
  //Damage was ranged and is variable, shows min and max
  else
    {
      if(a_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d-",a_hp);
      attron(COLOR_PAIR(255));
      if(a_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d",a_hp_max);
    }
  attron(COLOR_PAIR(255));

  //Defender
  attron( COLOR_PAIR(210+d->get_owner()->get_color() ) );
  mvprintw(SCR_H, 0, d_loc.c_str());
  attron(COLOR_PAIR(255));
  printw(" %d->",d->get_hp());
  //Damage wasn't ranged
  if(d_hp==d_hp_max)
    {
      if(d_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d",d_hp);
    }
  //Damage was ranged and is variable, shows min and max
  else
    {
      if(d_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d-",d_hp);
      attron(COLOR_PAIR(255));
      if(d_hp==0) { attron(COLOR_PAIR(210)); }
      printw("%d",d_hp_max);
    }
  attron(COLOR_PAIR(255));
}

//(Z) Get Distance
//Returns distance from entity u to v
int get_distance(entity *u, entity *v)
{
  int range=0;
  if(u->get_range()>v->get_range()) { range=u->get_range(); }
  else { range=v->get_range(); }

  //2D vector matrix of int distance
  std::vector< std::vector<int> > dist_map( (range*2)+1, std::vector<int>((range*2)+1, 999) );

  //Sets distance from u
  int kx, ky, dist;
  for(dist=0; dist<range; dist++)
    {
      //Top and bottom rows
      for(kx = range-dist; kx<range+dist+1; kx++)
	{
	  dist_map.at(range-dist).at(kx)=dist;
	  dist_map.at(range+dist).at(kx)=dist;
	}
      //Left and right columns
      for(ky = range-dist; ky<range+dist+1; ky++)
	{
	  dist_map.at(ky).at(range-dist)=dist;
	  dist_map.at(ky).at(range+dist)=dist;
	}
    }

  //Returns distance at v's position relative to x
  return dist_map[v->y()-u->y()+range][v->x()-u->x()+range];

}
