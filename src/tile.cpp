/********* CONTENTS **********/
//(A) Tile Constructor

//(B) Update Tile

//(C) Tile Output

//(D) Update Tile Info

/********* CONTENTS **********/

#include <ncurses.h>
#include "tile.h"

std::string tile_loc[] = { "Plains", "Forest", "Stone Deposit", "Gold Deposit", "Water", "Shallow Water", "Coast" };

//(A) Constructor
tile :: tile()
{
  type=tile_default;
  is_land=true;
  is_water=false;
}

//Is given a tile type, constructs tile depending on type
tile :: tile(enum tile_type type)
{
  this->type=type;
  if(type<4 || type==5 || type==6) { is_land=true; }
  else { is_land=false; }
  if(type==4 || type==5) { is_water=true; }
  else { is_water=false; }
  this->ent=NULL;
}
//(B) Update Tile
void tile :: update_tile(enum tile_type type)
{
  set_type(type);
  if(type<4 || type==5 || type==6) { set_land(true); }
  else { set_land(false);}
  if(type==4 || type==5) { set_water(true); }
  else { set_water(false); }
}

//(C) Tile Output
//Outputs the tile onto the screen
//If no entity is on tile, output is just tile color
void tile :: tile_output(int scr_x, int scr_y, player *p)
{
  //Checks if not in FOW
  if(p->has_sight(scr_x, scr_y-1))
    {
      //Entity is on tile
      if(ent)
	{
	  attron( COLOR_PAIR( (this->type*12)+10 + this->ent->get_owner()->get_color() ) );
	  mvaddch(scr_y, scr_x, ent->get_symbol());
	}
      //No entity
      else
	{
	  attron( COLOR_PAIR((type*12)+10) );
	  mvaddch(scr_y, scr_x, ' ');
	}
    }
  //Otherwise, prints tile as FOW
  else
    {
      attron( COLOR_PAIR(type+170) );
      mvaddch(scr_y, scr_x, ' ');
    }
}

//(D) Update Tile Info
//Updates tile and tile entity info in bottom left
void tile :: update_tile_info(int x, int y)
{
  //Clears Space
  mvaddstr(SCR_H-1, 0, "                                       ");
  mvaddstr(SCR_H, 0, "                                        ");

  //Tile info
  mvaddstr(SCR_H-1, 0, get_loc().c_str());
  mvprintw(SCR_H-1, get_loc().length()+1, "x: %d y: %d",x,y);

  //Outputs entity info if there is an entity
  if(ent)
    {
      std::string ent_loc = ent->get_name();
      std::string civ_adj_loc = ent->get_owner()->get_civ()->get_adj();

      //Entity info
      attron( COLOR_PAIR(210+ent->get_owner()->get_color() ) );
      mvprintw(SCR_H, 0, civ_adj_loc.c_str());
      mvprintw(SCR_H, civ_adj_loc.size()+1, ent_loc.c_str());
      attron(COLOR_PAIR(255));;
      printw(" HP: ");
      int hp_perc = (ent->get_hp()*100)/(ent->get_max_hp()+ent->get_hp_bonus());
      if(hp_perc<25) { attron(COLOR_PAIR(210));}
      else if(hp_perc<50) { attron(COLOR_PAIR(212));}
      else if(hp_perc<75) { attron(COLOR_PAIR(213));}
      else { attron(COLOR_PAIR(215));}
      printw("%d", ent->get_hp());
      attron(COLOR_PAIR(255));;
      printw("/%d", ent->get_max_hp()+ent->get_hp_bonus());
    }
}

//Returns localization for tile
std::string tile :: get_loc()
{
  return tile_loc[type];
}
