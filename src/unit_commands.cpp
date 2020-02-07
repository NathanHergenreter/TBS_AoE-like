#include <ncurses.h>
#include <vector>
#include "unit_commands.h"
#include "combat.h"

/********* CONTENTS **********/

//(A) Unit Move
//(Aa) Possible Moves
void get_possible_moves(map *, unit *, std::vector< std::vector<bool> > *, int, int, int);

//(B) Unit Construct
//(Ba) Can Construct
bool can_construct(map *, int, building_template *, int, int);

//(C) Unit Melee Attack

//(D) Unit Ranged Attack

//(E) Unit Garrison

//(F) Unit Ungarrison

//(G) Unit Upgrade

//(H) Unit Info

/********* CONTENTS **********/

//(A) Unit Move
//Allows a unit to be moved
void unit_move(map *game_map, unit *u, int cur_p)
{
  //Potential move distance
  int moves = u->get_cur_move();

  //2D array of possible moves within move distance
  std::vector< std::vector<bool> > potential( (moves*2)+1, std::vector<bool>((moves*2)+1, false) );

  //Recursively determines which tiles can be moved to
  get_possible_moves(game_map, u, &potential, moves, u->x(), u->y());

  //Changes target color to white
  if(COLORS>8) { init_color(252, (206*200)/51, (221*200)/51, (221*200)/51); }

  //Outupts '*' onto tiles which can be moved to
  int kx,ky;
  for(ky=0; ky<(moves*2)+1; ky++)
    {
      for(kx=0; kx<(moves*2)+1; kx++)
	{
	  //If unit can move to tile, places '*'
	  if(potential[ky][kx])
	    {
	      int rx=kx-moves+u->x(), ry=ky-moves+u->y();
	      attron(COLOR_PAIR(190));
	      mvaddch(ry+1,rx, ' '); 
	      attron(COLOR_PAIR(255));
	    }
	}
    }
  game_map->get_tile(u->x(),u->y())->tile_output(u->x(),u->y()+1, u->get_owner());
  attron(COLOR_PAIR(255));
  move(u->y()+1,u->x());


  //Cursor Move Loop
  int cur_x=u->x(), cur_y=u->y();
  int py = cur_y-u->y()+moves, px = cur_x-u->x()+moves;
  tile *curs_tile = game_map->get_tile(cur_x, cur_y);
  int command=0;
  while(command!=' ')
    {
      command=getch();

      //Commands list
      switch(command)
	{
	  //Move cursor up
	  //Updates tile info
	case KEY_UP:
	  //Cannot move above map or move dist
	  if(cur_y+1>1) 
	  if(cur_y+1>1 && py>0 &&
	     potential[py-1][px] ) 
	    { cur_y-=1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  move(cur_y+1, cur_x);
	  py = cur_y-u->y()+moves, px = cur_x-u->x()+moves;
	  break;

	  //Move cursor down
	  //Updates tile info
	case KEY_DOWN:
	  //Cannot move below map or move dist
	  if(cur_y+1<MAP_WIDTH-1 && py<(moves*2) &&
	     potential[py+1][px] ) 
	    { cur_y+=1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  move(cur_y+1, cur_x);
	  py = cur_y-u->y()+moves, px = cur_x-u->x()+moves;
	  break;

	  //Move cursor right
	  //Updates tile info
	case KEY_RIGHT:
	  //Cannot move beyond map or move dist
	  if(cur_x<MAP_WIDTH-1 && px<(moves*2) &&
	     potential[py][px+1] ) 
	    { cur_x+=1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  move(cur_y+1, cur_x);
	  py = cur_y-u->y()+moves, px = cur_x-u->x()+moves;
	  break;

	  //Move cursor left
	  //Updates tile info
	case KEY_LEFT:
	  //Cannot move beyond map or move dist
	  if(cur_x>0 && px>0 &&
	     potential[py][px-1] ) 
	    { cur_x-=1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  move(cur_y+1, cur_x);
	  py = cur_y-u->y()+moves, px = cur_x-u->x()+moves;
	  break;

	  //Checks if unit is not on passable building
	case ' ':
	  if(game_map->get_tile(cur_x,cur_y)->get_entity() && game_map->get_tile(cur_x,cur_y)->get_entity()!=u )
	    {
	      mvprintw(SCR_H-1, 0, "%s in way!    ", game_map->get_tile(cur_x,cur_y)->get_entity()->get_name().c_str());
	  command=0;
	    }
	  break;

	default:
	  break;
	}
    }

  game_map->get_tile(u->x(),u->y())->set_entity(NULL);
  game_map->get_tile(cur_x,cur_y)->set_entity(u);
  u->mod_cur_move( -(std::abs(u->x()-cur_x)+std::abs(u->y()-cur_y)) );
  u->set_coords(cur_x,cur_y);

  //Changes target color back to red
  if(COLORS>8) { init_color(252, (193*200)/51, (67*200)/51, (67*200)/51); }

  game_map->update_los_entity((entity*)u, cur_p);
  game_map->output_map(cur_p);
}

//(Aa) Get Possible Moves
//Recursive, updates 2D possible moves matrix for unit move
void get_possible_moves(map *game_map, unit *u, std::vector< std::vector<bool> > *potential, int rem, int x, int y)
{
  //Potential move distance
  int ux=u->x(), uy=u->y();
  int moves = u->get_cur_move();

  //Sets current tile move potential as true
  potential->at(y-uy+moves).at(x-ux+moves)=true;

  //Recursively calls upon neighboring tiles
  //Checks if remaining moves
  if(rem>0)
    {
      //Up
      if( y>0 && 
	  ( !(game_map->get_tile(x,y-1)->get_entity() ) ||
	    ( game_map->get_tile(x,y-1)->get_entity() && 
	     game_map->get_tile(x,y-1)->get_entity()->get_entity_type()==entity_building
	     && ((building *)game_map->get_tile(x,y-1)->get_entity())->passable() 
	     && game_map->get_tile(x,y-1)->get_entity()->get_owner()==u->get_owner() ) 
	    )
	  && (
        ( game_map->get_tile(x,y-1)->land()==u->land() ) ||
        ( game_map->get_tile(x,y-1)->water()==u->naval() ) ) ) 
	{ get_possible_moves(game_map, u, potential, rem-1, x, y-1); }

      //Down
      if( y<MAP_HEIGHT-1 && 
	  ( !(game_map->get_tile(x,y+1)->get_entity() ) ||
	    (game_map->get_tile(x,y+1)->get_entity() && 
	     game_map->get_tile(x,y+1)->get_entity()->get_entity_type()==entity_building
	     && ((building *)game_map->get_tile(x,y+1)->get_entity())->passable()
	     && game_map->get_tile(x,y+1)->get_entity()->get_owner()==u->get_owner() ) )
	  && (
        ( game_map->get_tile(x,y+1)->land()==u->land() ) ||
        ( game_map->get_tile(x,y+1)->water()==u->naval() ) ) ) 
	{ get_possible_moves(game_map, u, potential, rem-1, x, y+1); }

      //Left
      if( x>0 && 
	  ( !(game_map->get_tile(x-1,y)->get_entity() ) ||
	    (game_map->get_tile(x-1,y)->get_entity() && 
	     game_map->get_tile(x-1,y)->get_entity()->get_entity_type()==entity_building
	     && ((building *)game_map->get_tile(x-1,y)->get_entity())->passable() 
	     && game_map->get_tile(x-1,y)->get_entity()->get_owner()==u->get_owner() ) )
	  && (
        ( game_map->get_tile(x-1,y)->land()==u->land() ) ||
        ( game_map->get_tile(x-1,y)->water()==u->naval() ) ) ) 
	{ get_possible_moves(game_map, u, potential, rem-1, x-1, y); }

      //Right
      if( x<MAP_WIDTH && 
	  ( !(game_map->get_tile(x+1,y)->get_entity() ) ||
	    (game_map->get_tile(x+1,y)->get_entity() && 
	     game_map->get_tile(x+1,y)->get_entity()->get_entity_type()==entity_building
	     && ((building *)game_map->get_tile(x+1,y)->get_entity())->passable() 
	     && game_map->get_tile(x+1,y)->get_entity()->get_owner()==u->get_owner() ) )
	  && (
        ( game_map->get_tile(x+1,y)->land()==u->land() ) ||
        ( game_map->get_tile(x+1,y)->water()==u->naval() ) ) ) 
	{ get_possible_moves(game_map, u, potential, rem-1, x+1, y); }
    }
}

//(B) Unit Construct
void unit_construct(map *game_map, unit *u, int cur_p)
{
  int i, j;

  WINDOW *win_cmd;
  player *p = u->get_owner();

  //Turns off cursor
  curs_set(0);
  
  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(u->y()-BUILD_BOX_H-1>0) { cmd_y=u->y()-BUILD_BOX_H; }
  //Places below
  else { cmd_y=u->y()+2; }
  //Places mid
  cmd_x = u->x()-(BUILD_BOX_W/2);
  //Places right
  if(u->x()-(BUILD_BOX_W/2)<0) { cmd_x = u->x(); }
  //Places left
  else if(u->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = u->x()-BUILD_BOX_W;}

  win_cmd = newwin(BUILD_BOX_H, BUILD_BOX_W, cmd_y, cmd_x);
  wattron(win_cmd, COLOR_PAIR(253));
  for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }
  wrefresh(win_cmd);

  //Exit flag
  bool exit=false;

  //Construct Loop
  while(!exit)
    {
      //Prints out building classes
      for(i=1; i<p->get_num_bclasses(); i++)
	{
	  mvwprintw(win_cmd, i-1, 1, get_bclass_loc( (enum building_class) i).c_str());
	}
      mvwprintw(win_cmd, p->get_num_bclasses()-1, 1, "Cancel");

      int command=0, cur_class=0;
      //Class Menu Loop
      while(command!=' ')
	{
	  mvwaddch(win_cmd, cur_class, 0, '>');
	  wrefresh(win_cmd);
	  command=getch();

	  //Input Switch
	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, cur_class, 0, ' ');
	      if(cur_class==0) { cur_class=p->get_num_bclasses()-1; }
	      else { cur_class-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, cur_class, 0, ' ');
	      if(cur_class==p->get_num_bclasses()-1) { cur_class=0; }
	      else { cur_class+=1; }
	      break;

	      //Cancels construction
	    case ' ':
	      if(cur_class==p->get_num_bclasses()-1) { exit=true; }
	      break;

	    default:
	      break;
	    }
	}

      //Doesn't do rest of now unnecessary stuff
      if(exit) { break; }

      //Increment to ignore default
      cur_class++;
      wclear(win_cmd);
      for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }

      int num_bldg=1;
      int bldg_act[p->get_num_bclass(cur_class)];
      //Outputs buildings in class (and return)
      for(i=1; i<p->get_num_bclass(cur_class); i++)
	{
	  building_template *b_cur = p->get_bldg(cur_class, i);
	  //If player is at building age and has building prereq tech, adds to construct options
	  if( p->get_age() >=  b_cur->age && p->tech_researched(b_cur->prereq) )
	    {
	      mvwprintw(win_cmd, num_bldg-1, 1, b_cur->name.c_str());
	      bldg_act[num_bldg]=i;
	      num_bldg++;
	    }
	}
      mvwprintw(win_cmd, num_bldg-1, 1, "Return");

      //Buildings Menu Loop
      command=0;
      int  cur_bldg=1;
      building_template *b;
      while(!exit && command!=' ')
	{
	  attron(COLOR_PAIR(255));
	  mvaddstr(SCR_H-1,0,"                         ");
	  mvaddstr(SCR_H,0,"                                                ");
	  if(cur_bldg!=num_bldg)
	    {
	      b = p->get_bldg(cur_class, bldg_act[cur_bldg]);

	      //Current Constructability
	      if(can_construct(game_map, cur_p, b, u->x(), u->y())) { mvaddstr(SCR_H-1,0, "Can Construct"); }
	      else { mvaddstr(SCR_H-1,0, "Cannot Construct"); }

	      //Resources
	      move(SCR_H,0);
	      //Pop
	      if(b->pop!=0) { 
		printw("Pop:"); 
		if(p->get_cur_pop() - b->pop > p->get_max_pop()) { attron(COLOR_PAIR(210)); }
		else if(b->pop>0) { attron(COLOR_PAIR(215)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",b->pop);
		attron(COLOR_PAIR(255));
	      }
	      //Gold
	      if(b->init_gold!=0) { 
		printw("Gold:"); 
		if(p->get_gold() - b->init_gold < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",b->init_gold);
		attron(COLOR_PAIR(255));
	      }
	      //Food
	      if(b->init_food!=0) { 
		printw("Food:"); 
		if(p->get_food() - b->init_food < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",b->init_food);
		attron(COLOR_PAIR(255));
	      }
	      //Wood
	      if(b->init_wood!=0) { 
		printw("Wood:"); 
		if(p->get_wood() - b->init_wood < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",b->init_wood);
		attron(COLOR_PAIR(255));
	      }
	      //Stone
	      if(b->init_stone!=0) { 
		printw("Stone:"); 
		if(p->get_stone() - b->init_stone < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",b->init_stone);
		attron(COLOR_PAIR(255));
	      }
	    }
	  mvwaddch(win_cmd, cur_bldg-1, 0, '>');
	  wrefresh(win_cmd);
	  refresh();
	  command=getch();

	  //Input Switch
	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, cur_bldg-1, 0, ' ');
	      if(cur_bldg==1) { cur_bldg=num_bldg; }
	      else { cur_bldg-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, cur_bldg-1, 0, ' ');
	      if(cur_bldg==num_bldg) { cur_bldg=1; }
	      else { cur_bldg+=1; }
	      break;

	    case ' ':
	      //Construction
	      //If return was not selected, constructs chosen building if resources available
	      if(cur_bldg<num_bldg && can_construct(game_map, cur_p, game_map->get_player(cur_p)->get_bldg(cur_class, bldg_act[cur_bldg]), u->x(), u->y()))
		{
		  int ux=u->x(), uy=u->y();
		  game_map->remove_unit(cur_p, u);
		  game_map->add_building(cur_p, new building( b, ux, uy));
		  game_map->get_player(cur_p)->purchase(b->init_gold, b->init_food, b->init_wood, b->init_stone );
		  game_map->get_player(cur_p)->resource_output();
		  exit=true;
		}
	      //Returned
	      else if(cur_bldg!=num_bldg)
		{
		  command=0;
		}
	      break;

	    default:
	      break;
	    }
	}
      wclear(win_cmd);
      for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }
    }

  //Commands menu no longer needed, restores output
  attron(COLOR_PAIR(255));
  delwin(win_cmd);
  game_map->output_map(cur_p);
  game_map->get_tile(u->x(),u->y())->update_tile_info(u->x(), u->y());
}

//(Ba) Can Construct
//Looks at resources and determines if can construct building or not
bool can_construct(map *game_map, int cur_p, building_template *b, int x, int y)
{
  player *p = game_map->get_player(cur_p);
  //First checks if current tile isn't same as building tile
  if(game_map->get_tile(x,y)->get_type()!=b->terrain_type)
    { 
      return false;
    }
  //Then checks if pop change is non-negative, if so ignores pop
  //Otherwise, checks if difference between cur_pop and max is less building pop
  if( b->pop >= 0 || (p->get_cur_pop() - p->get_max_pop()) <= b->pop )
    {
      //Compares player's resource reserves to building costs
      return p->get_gold()>=b->init_gold && p->get_food()>=b->init_food && p->get_wood()>=b->init_wood && p->get_stone()>=b->init_stone;
    }
  else
    {
      return false;
    }
}

//(C) Unit Melee Attack
void unit_melee(map *game_map, unit *u, int cur_p)
{
  player *p = game_map->get_player(cur_p);

  //Places target area around unit
  int y,x;
  for(y=u->y()-1; y < u->y()+2; y++)
    {
      for(x=u->x()-1; x < u->x()+2; x++)
	{
	  if(x>0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      tile *t = game_map->get_tile(x,y);
	      //If empty or enemy entity, colors their background as target
	      if( (!t->get_entity()) || (t->get_entity() && t->get_entity()->get_owner()!=p) )
		{
		  //Is an entity
		  if(t->get_entity()) 
		    { 
		      attron( COLOR_PAIR(190+t->get_entity()->get_owner()->get_color() ) );
		      mvaddch(y+1,x, t->get_entity()->get_symbol()); 
		    }
		  //Empty
		  else 
		    { 
		      attron(COLOR_PAIR(190));
		      mvaddch(y+1,x, ' '); 
		    }
		}
	    }
	}
    }
  attron(COLOR_PAIR(255));

  curs_set(1);

  //Target Select Loop
  int command=0, tar_x=u->x(), tar_y=u->y();
  tile *tar_t;
  while(command!=' ')
    {
      mvaddstr(SCR_H-1, 0, "                           ");
      mvaddstr(SCR_H, 0, "                           ");
      tar_t=game_map->get_tile(tar_x,tar_y);
      move(tar_y+1,tar_x);

      //Outputs combat results in bottom screen if target is enemy
      if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p)
	{
	  combat_results( (entity*)u, tar_t->get_entity(), combat_melee);
	  move(tar_y+1, tar_x);
	}

      command=getch();

      //Command Switch
      switch(command)
	{
	  //Move Left
	case KEY_LEFT:
	  if(tar_x-u->x()>=0) { tar_x--; }
	  break;

	  //Move Right
	case KEY_RIGHT:
	  if(u->x()-tar_x>=0) { tar_x++; }
	  break;

	  //Move Up
	case KEY_UP:
	  if(tar_y-u->y()>=0) { tar_y--; }
	  break;

	  //Move DOWN
	case KEY_DOWN:
	  if(u->y()-tar_y>=0) { tar_y++; }
	  break;
	    
	default:
	  break;
	}
    }

  //Checks if target is enemy entity, if so, partakes in combat
  if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p)
    {
      //Calls combat function which updates HP of both entities and removes them if one dies
      combat( (entity*) u, tar_t->get_entity(), combat_melee);
      u->set_action(false);

      //Checks if either combatant died, if so, removes them
      if(u->get_hp()<=0) { game_map->remove_unit(cur_p, u); }
      if(tar_t->get_entity()->get_hp()<=0)
	{
	  //Determines which player the target's owner is
	  if(cur_p==0) { game_map->remove_unit(1, (unit*)tar_t->get_entity()); }
	  else { game_map->remove_unit(0, (unit*)tar_t->get_entity()); }
	}

      //Updates tile info
      game_map->get_tile(u->x(),u->y())->update_tile_info(u->x(), u->y());
    }

  game_map->output_map(cur_p);
}

//(D) Unit Ranged Attack
void unit_ranged(map *game_map, unit *u, int cur_p)
{
  player *p = game_map->get_player(cur_p);
  int range=u->get_range();

  std::vector< std::vector<bool> > potential( (range*2)+1, std::vector<bool>((range*2)+1,true) );


  //If unit is not indirect, updates potential targets matrix indicating line of sight
  if(!u->indirect())
    {
      game_map->line_of_sight(u, &potential, range, false);
    }

  //Places target area around unit
  int y,x;
  for(y=u->y()-range; y < u->y()+range+1; y++)
    {
      for(x=u->x()-range; x < u->x()+range+1; x++)
	{
	  if(x>=0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      tile *t = game_map->get_tile(x,y);
	      //If empty or enemy entity within range, colors their background as target
	      if( ( (!t->get_entity()) || ( t->get_entity() && t->get_entity()->get_owner()!=p) )
		  && potential[y-u->y()+range][x-u->x()+range]
		  && p->has_sight(x,y) )
		{
		  //Is an entity
		  if(t->get_entity()) 
		    { 
		      attron( COLOR_PAIR(190+t->get_entity()->get_owner()->get_color() ) );
		      mvaddch(y+1,x, t->get_entity()->get_symbol()); 
		    }
		  //Empty
		  else 
		    { 
		      attron(COLOR_PAIR(190));
		      mvaddch(y+1,x, ' '); 
		    }
		}
	    }
	}
    }
  attron(COLOR_PAIR(255));

  curs_set(1);


  //Target Select Loop
  int command=0, tar_x=u->x(), tar_y=u->y();
  tile *tar_t;
  while(command!=' ')
    {
      mvaddstr(SCR_H-1, 0, "                              ");
      mvaddstr(SCR_H, 0, "                              ");
      tar_t=game_map->get_tile(tar_x,tar_y);
      move(tar_y+1,tar_x);

      //Outputs combat results in bottom screen if target is enemy
      if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p && potential[tar_y-u->y()+range][tar_x-u->x()+range] && p->has_sight(tar_x,tar_y) )
	{
	  combat_results( (entity*)u, tar_t->get_entity(), combat_ranged);
	  move(tar_y+1, tar_x);
	}

      command=getch();

      //Command Switch
      switch(command)
	{
	  //Move Left
	case KEY_LEFT:
	  if( tar_x-u->x()+range>0 
	      && tar_x>0 ) 
	    { tar_x--; }
	  break;

	  //Move Right
	case KEY_RIGHT:
	  if( tar_x-u->x()<range 
	     && tar_x<MAP_WIDTH ) 
	    { tar_x++; }
	  break;

	  //Move Up
	case KEY_UP:
	  if( tar_y-u->y()+range>0 
	     && tar_y>0 ) 
	    { tar_y--; }
	  break;

	  //Move DOWN
	case KEY_DOWN:
	  if( tar_y-u->y()<range 
	     && tar_y<MAP_HEIGHT ) 
	    { tar_y++; }
	  break;
	    
	default:
	  break;
	}
    }

  //Checks if target is enemy entity outside FOW, if so, partakes in combat
  if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p && potential[tar_y-u->y()+range][tar_x-u->x()+range] && p->has_sight(tar_x,tar_y) )
    {
      //Calls combat function which updates HP of both entities and removes them if one dies
      combat( (entity*) u, tar_t->get_entity(), combat_ranged);
      u->set_action(false);

      //Checks if either combatant died, if so, removes them
      if(u->get_hp()<=0) { game_map->remove_unit(cur_p, u); }
      if(tar_t->get_entity()->get_hp()<=0)
	{
	  //Determines which player the target's owner is
	  int tar_p;
	  if(cur_p==0) { tar_p=1;}
	  else { tar_p=0; }

	  //Removes depending on unit or building
	  if(tar_t->get_entity()->get_entity_type()==entity_unit)
	    {
	      game_map->remove_unit(tar_p, (unit*)tar_t->get_entity());
	    }
	  else
	    {
	      game_map->remove_building(tar_p, (building*)tar_t->get_entity());
	    }
	}

      //Updates tile info
      game_map->get_tile(u->x(),u->y())->update_tile_info(u->x(), u->y());
    }

  game_map->output_map(cur_p);
}

//(E) Unit Garrison
void unit_garrison(map *game_map, unit *u, int cur_p)
{
  player *p = game_map->get_player(cur_p);

  //Changes target color to white
  if(COLORS>8) { init_color(252, (206*200)/51, (221*200)/51, (221*200)/51); }

  //Places target area around unit
  int y,x;
  for(y=u->y()-1; y < u->y()+2; y++)
    {
      for(x=u->x()-1; x < u->x()+2; x++)
	{
	  if(x>0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      tile *t = game_map->get_tile(x,y);
	      //If friendly entity that can garrison and is not at max capacity, colors their background as target
	      if( t->get_entity() && t->get_entity()->get_owner()==p && t->get_entity()->garrisonable()
		  && ( !u->naval() || t->get_entity()->get_entity_type()==entity_building
		       || (t->get_entity()->get_entity_type()==entity_unit && !((unit*)t->get_entity())->land()) ) )
		{
		  attron( COLOR_PAIR(190+t->get_entity()->get_owner()->get_color() ) );
		  mvaddch(y+1,x, t->get_entity()->get_symbol()); 
		}
	    }
	}
    }

  attron(COLOR_PAIR(255));

  curs_set(1);

  //Target Select Loop
  int command=0, tar_x=u->x(), tar_y=u->y();
  tile *tar_t;
  while(command!=' ')
    {
      mvaddstr(SCR_H-1, 0, "                           ");
      mvaddstr(SCR_H, 0, "                                 ");
      tar_t=game_map->get_tile(tar_x,tar_y);

      //Outputs entity info if friendly and can garrison
      if( tar_t->get_entity() && tar_t->get_entity()->get_owner()==p && tar_t->get_entity()->get_max_garrison()>0 )
	{
	  //If entity is not at max capacity, indicates in output
	  if(tar_t->get_entity()->garrisonable() 
	     && ( !u->naval() || tar_t->get_entity()->get_entity_type()==entity_building
		 || (tar_t->get_entity()->get_entity_type()==entity_unit && !((unit*)tar_t->get_entity())->land()) ) ) 
	    { mvaddstr(SCR_H-1, 0, "Can Garrison"); }
	  else { mvaddstr(SCR_H-1, 0, "Cannot Garrison"); }
	  mvprintw(SCR_H, 0, "Capacity: %d/%d", tar_t->get_entity()->get_garrison_size(), tar_t->get_entity()->get_max_garrison());
	}

      move(tar_y+1,tar_x);

      command=getch();

      //Command Switch
      switch(command)
	{
	  //Move Left
	case KEY_LEFT:
	  if(tar_x-u->x()>=0) { tar_x--; }
	  break;

	  //Move Right
	case KEY_RIGHT:
	  if(u->x()-tar_x>=0) { tar_x++; }
	  break;

	  //Move Up
	case KEY_UP:
	  if(tar_y-u->y()>=0) { tar_y--; }
	  break;

	  //Move DOWN
	case KEY_DOWN:
	  if(u->y()-tar_y>=0) { tar_y++; }
	  break;
	    
	default:
	  break;
	}
    }

  //If friendly entity that can garrison and is not at max capacity, puts into entity's garrison
  if( tar_t->get_entity() && tar_t->get_entity()->get_owner()==p && tar_t->get_entity()->garrisonable()
      && ( !u->naval() || tar_t->get_entity()->get_entity_type()==entity_building
	   || (tar_t->get_entity()->get_entity_type()==entity_unit && !((unit*)tar_t->get_entity())->land()) ) )
    {
      u->set_action(false);

      tar_t->get_entity()->add_garrison( (entity*) u);
      game_map->get_tile(u->x(),u->y())->set_entity(NULL);

      //Updates tile info
      game_map->get_tile(u->x(),u->y())->update_tile_info(u->x(), u->y());
    }

  //Changes target color back to red
  if(COLORS>8) { init_color(252, (193*200)/51, (67*200)/51, (67*200)/51); }

  game_map->output_map(cur_p);
}

//(F) Unit Ungarrison
void unit_ungarrison(map *game_map, unit *u, int cur_p)
{
  WINDOW *win_cmd;
  int gar = u->get_garrison_size();

  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(u->y()-gar-1>1) { cmd_y=u->y()-gar-1; }
  //Places below
  else { cmd_y=u->y()+gar+1; }
  //Places mid
  cmd_x = u->x()-(BUILD_BOX_W/2);
  //Places right
  if(u->x()-(BUILD_BOX_W/2)<0) { cmd_x = u->x(); }
  //Places left
  else if(u->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = u->x()-BUILD_BOX_W;}

  win_cmd = newwin(gar+1, BUILD_BOX_W, cmd_y, cmd_x);

  //Initializes output
  int i;
  for(i=0; i<gar; i++)
    {
      mvwaddstr(win_cmd, i, 1, u->get_garrison(i)->get_name().c_str());
    }
  mvwaddstr(win_cmd, gar, 1, "Cancel");
  wrefresh(win_cmd);

  int command=0, cur_cmd=0;
  //Menu Loop
  while(command!=' ')
    {
      //Updates selection cursor on window
      mvwaddch(win_cmd, cur_cmd, 0, '>');
      wrefresh(win_cmd);

      //Outputs current unit info
      mvprintw(SCR_H-1, 0, "                    ");
      mvprintw(SCR_H, 0, "                    ");
      if(cur_cmd<gar)
	{
	  entity *ent = u->get_garrison(cur_cmd);
	  attron(COLOR_PAIR(210+ent->get_owner()->get_color()));
	  mvprintw(SCR_H-1, 0, ent->get_name().c_str());
	  attron(COLOR_PAIR(255));;
	  mvprintw(SCR_H, 0, "HP: %d/%d", ent->get_hp(), ent->get_max_hp());
	}

      command=getch();

      //Input Switch
      switch(command)
	{
	case KEY_UP:
	  mvwaddch(win_cmd, cur_cmd, 0, ' ');
	  if(cur_cmd==0) { cur_cmd=gar; }
	  else { cur_cmd-=1; }
	  break;

	case KEY_DOWN:
	  mvwaddch(win_cmd, cur_cmd, 0, ' ');
	  if(cur_cmd==gar) { cur_cmd=0; }
	  else { cur_cmd+=1; }
	  break;

	default:
	  break;
	}
    }

  //Commands menu no longer needed, restores output
  delwin(win_cmd);
  game_map->output_map(cur_p);
  refresh();

  //Changes target color to white
  if(COLORS>8) { init_color(252, (206*200)/51, (221*200)/51, (221*200)/51); }

  unit *e = (unit*) u->get_garrison(cur_cmd);

  //Places target area around unit
  int y,x;
  for(y=u->y()-u->get_deploy(); y < u->y()+u->get_deploy()+1; y++)
    {
      for(x=u->x()-u->get_deploy(); x < u->x()+u->get_deploy()+1; x++)
	{
	  if(x>0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      tile *t = game_map->get_tile(x,y);


	      //If empty space which unit can be placed upon (ie land tile for land unit) highlights
	      if(!t->get_entity() && ( (t->land() && e->land()) || (t->water() && e->naval()) ) )
		{
		  attron(COLOR_PAIR(190));
		  mvaddch(y+1,x, ' '); 
		}
	    }
	}
    }

  attron(COLOR_PAIR(255));


  curs_set(1);

  //Target Select Loop
  command=0;
  int  tar_x=u->x(), tar_y=u->y();
  tile *tar_t;
  while(command!=' ')
    {
      tar_t=game_map->get_tile(tar_x,tar_y);
      tar_t->update_tile_info(tar_x,tar_y);
      refresh();

      move(tar_y+1,tar_x);

      command=getch();

      //Command Switch
      switch(command)
	{
	  //Move Left
	case KEY_LEFT:
	  if(tar_x>0 && tar_x > u->x()-u->get_deploy()) { tar_x--; }
	  break;

	  //Move Right
	case KEY_RIGHT:
	  if(tar_x<MAP_WIDTH-1 && tar_x < u->x()+u->get_deploy()) { tar_x++; }
	  break;

	  //Move Up
	case KEY_UP:
	  if(tar_y>0  && tar_y > u->y()-u->get_deploy()) { tar_y--; }
	  break;

	  //Move DOWN
	case KEY_DOWN:
	  if(tar_y<MAP_HEIGHT  && tar_y < u->y()+u->get_deploy()) { tar_y++; }
	  break;
	    
	case ' ':
	  //If tile has an entity, cannot be placed there
	  if(tar_t->get_entity() || ( (!tar_t->land() && e->land()) || (!tar_t->water() && e->naval()) )) { command=0; }
	  break;

	default:
	  break;
	}
    }

  //Changes target color back to red
  if(COLORS>8) { init_color(252, (193*200)/51, (67*200)/51, (67*200)/51); }

  //Removes unit from garrison and places onto target tile
  tar_t->set_entity(u->remove_garrison(cur_cmd));
  tar_t->get_entity()->set_coords(tar_x,tar_y);
  game_map->output_map(cur_p);
  refresh();
}

//(G) Unit Upgrade
void unit_upgrade(map *game_map, unit *u, int cur_p)
{
  player *p = game_map->get_player(cur_p);
  unit_template *tmp = p->get_unit(u->get_class(), p->get_unit_idx(u->get_class(), u->get_upgrade()) );
  unit_template *old = p->get_unit(u->get_class(),  p->get_unit_idx(u->get_class(), u->get_type()) );
  int cost_g= tmp->init_gold-old->init_gold, cost_f=tmp->init_food-old->init_food, cost_w=tmp->init_wood-old->init_wood, cost_s=tmp->init_stone-old->init_stone;

  //Updates upgrade info on bottom of screen
  mvaddstr(SCR_H-1, 0, "                           ");
  mvaddstr(SCR_H, 0, "                                 ");
  if(p->get_gold()-cost_g>=0 && p->get_food()-cost_f>=0 && p->get_wood()-cost_w>=0 && p->get_stone()-cost_s>=0 && p->get_age()>=tmp->age && p->tech_researched(tmp->prereq) )
    {
      mvaddstr(SCR_H-1, 0, "Can Upgrade");
    }
  else
    {
      mvaddstr(SCR_H-1, 0, "Cannot Upgrade");
      //Not correct age
      if(p->get_age()<tmp->age)
	{
	  printw(": Must be in ");
	  switch(tmp->age)
	    {
	    case 0:
	      printw("Early Middle Ages ");
	      break;
	    case 1:
	      printw("High Middle Ages ");
	      break;
	    case 2:
	      printw("Late Middle Ages ");
	      break;
	    default:
	      break;
	    }
	}
      //Lacking prereq tech
      if(!p->tech_researched(tmp->prereq)) { printw(": Need Tech %s", p->get_tech(tmp->prereq)->name().c_str()); }
    }
  mvprintw(SCR_H, 0, "Gold:");
  if(p->get_gold()-cost_g<0) { attron(COLOR_PAIR(210)); }
  printw(" %d ", cost_g);
  attron(COLOR_PAIR(255));
  printw(" Food:");
  if(p->get_food()-cost_f<0) { attron(COLOR_PAIR(210)); }
  printw(" %d ", cost_f);
  attron(COLOR_PAIR(255));
  printw(" Wood:");
  if(p->get_wood()-cost_w<0) { attron(COLOR_PAIR(210)); }
  printw(" %d ", cost_w);
  attron(COLOR_PAIR(255));
  printw(" Stone:");
  if(p->get_stone()-cost_s<0) { attron(COLOR_PAIR(210)); }
  printw(" %d ", cost_s);
  attron(COLOR_PAIR(255));
  refresh();

  //Turns off cursor
  curs_set(0);
  WINDOW *win_cmd;

  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(u->y()-2-1>0) { cmd_y=u->y()-2; }
  //Places below
  else { cmd_y=u->y()+2; }
  //Places mid
  cmd_x = u->x()-(BUILD_BOX_W/2);
  //Places right
  if(u->x()-(BUILD_BOX_W/2)<0) { cmd_x = u->x(); }
  //Places left
  else if(u->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = u->x()-BUILD_BOX_W;}

  win_cmd = newwin(2, BUILD_BOX_W, cmd_y, cmd_x);
  mvwaddstr(win_cmd, 0, 1, tmp->name.c_str());
  mvwaddstr(win_cmd, 1, 1, "Cancel");
  wrefresh(win_cmd);

  int num_cmds=2;
  int command=0, cur_cmd=0;
  //Menu Loop
  while(command!=' ')
    {
      //Updates selection cursor on window
      mvwaddch(win_cmd, cur_cmd, 0, '>');
      wrefresh(win_cmd);

      command=getch();

      //Input Switch
      switch(command)
	{
	case KEY_UP:
	  mvwaddch(win_cmd, cur_cmd, 0, ' ');
	  if(cur_cmd==0) { cur_cmd=num_cmds-1; }
	  else { cur_cmd-=1; }
	  break;

	case KEY_DOWN:
	  mvwaddch(win_cmd, cur_cmd, 0, ' ');
	  if(cur_cmd==num_cmds-1) { cur_cmd=0; }
	  else { cur_cmd+=1; }
	  break;

	default:
	  break;
	}
    }

  //Updates tile info
  game_map->get_tile(u->x(),u->y())->update_tile_info(u->x(), u->y());

  //If upgrade is available and upgrade was selected, upgrades unit
  if(p->get_gold()-cost_g>=0 && p->get_food()-cost_f>=0 && p->get_wood()-cost_w>=0 && p->get_stone()-cost_s>=0 && p->get_age()>=tmp->age && p->tech_researched(tmp->prereq) && cur_cmd==0 )
    {
      //HP Remains same percent
      int hp=( u->get_hp()* (tmp->max_hp+tmp->hp_bonus) ) / (old->max_hp+old->hp_bonus);
      unit *up = new unit(tmp, u->x(), u->y());
      up->mod_hp(-up->get_max_hp());
      up->mod_hp(hp);

      //Transfer garrison if any
      if(u->get_garrison_size() > 0)
	{
	  int i;
	  for(i=0; i < (int) u->get_garrison_size(); i++) { up->add_garrison(u->remove_garrison(i)); }
	}

      //Adds unit to map
      up->set_action(false);
      game_map->remove_unit(cur_p, u);
      game_map->add_unit(cur_p, up);


      //Updates tile info
      game_map->get_tile(up->x(),up->y())->update_tile_info(up->x(), up->y());
    }

  //Commands menu no longer needed, restores output
  delwin(win_cmd);
  game_map->output_map(cur_p);
  refresh();
}

//(H) Unit Info
void unit_info(unit *u)
{
  int y,x;

  player *p = u->get_owner();
  curs_set(0);
  WINDOW *win_info;

  win_info = newwin(INFO_BOX_H, INFO_BOX_W, MAP_HEIGHT-INFO_BOX_H, (MAP_WIDTH-INFO_BOX_W)/2);

  wrefresh(win_info);

  //Initialization
  wattron( win_info,COLOR_PAIR(254));
  wclear(win_info);
  wborder(win_info, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
  wattron( win_info,COLOR_PAIR(210) );
  for(y=1; y<INFO_BOX_H-1; y++) { for(x=1; x<INFO_BOX_W-1; x++) { mvwprintw(win_info,y,x, " "); } }

  //Name and Civ
  wattron( win_info,COLOR_PAIR(210+p->get_color() ) );
  mvwprintw(win_info, 1, (INFO_BOX_W/2)-(u->get_name().length())/2, u->get_name().c_str());
  mvwprintw(win_info, 2, (INFO_BOX_W/2)-(p->get_civ()->get_name().length())/2, p->get_civ()->get_name().c_str());
  wattron(win_info,COLOR_PAIR(255));

  //Hitpoints
  mvwprintw(win_info, 4, 2, "Hitpoints: ");
  int hp_perc = (u->get_hp()*100)/(u->get_max_hp()+u->get_hp_bonus());
  if(hp_perc<25) { wattron(win_info,COLOR_PAIR(210));}
  else if(hp_perc<50) { wattron(win_info,COLOR_PAIR(212));}
  else if(hp_perc<75) { wattron(win_info,COLOR_PAIR(213));}
  else { wattron(win_info,COLOR_PAIR(215));}
  wprintw(win_info, "%d", u->get_hp());
  wattron(win_info,COLOR_PAIR(255));
  wprintw(win_info, "/%d",u->get_max_hp()+u->get_hp_bonus());

  //Amror
  mvwprintw(win_info, 5, 2, "Armor: %d+%d",u->get_armor(),u->get_armor_bonus());

  //Movement
  mvwprintw(win_info, 6, 2, "Movement: %d+%d",u->get_max_move(),u->get_move_bonus());

  //Sight
  mvwprintw(win_info, 7, 2, "Sight: %d+%d",u->sight(),u->sight_bonus());

  int cur_pos=9;

  //Class info
  //Primary Class
  mvwprintw(win_info, cur_pos, 2, "Primary Class: %s", get_uclass_loc(u->get_class()).c_str());

  //Secondary Classes
  mvwprintw(win_info, cur_pos+2, 2, "Secondary Classes:");

  int k;
  for(k=0; k<NUM_UNIT_CLASSES; k++)
    {
      //Prints subclass if it is not the primary
      if(k!=u->get_class()  && u->has_subclass((enum unit_class) k)==1 )
	{
	  mvwprintw(win_info, cur_pos+3, 2, "%s", get_uclass_loc((enum unit_class) k).c_str());
	  cur_pos++;
	}
    }

  cur_pos = 4;

  //Melee
  if(u->get_melee()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Melee Attack: %d+%d", u->get_melee(),u->get_melee_bonus());
      mvwprintw(win_info, cur_pos+1, INFO_BOX_W/2, "Melee Pierce: %d+%d", u->get_melee_ap(),u->get_melee_ap_bonus());

      //Building Damage
      mvwprintw(win_info, cur_pos+2, INFO_BOX_W/2, "Building Damage: %d+%d", u->get_building_attack(),u->get_building_attack_bonus());
      //Garrison Capacity
      if(u->garrisonable())
	{
	  mvwprintw(win_info, cur_pos+2, INFO_BOX_W/2, "Capacity: %d", u->get_max_garrison());
	}
    }

  cur_pos=9;

  //Ranged
  if(u->get_ranged()>0)
    {
      if(u->indirect()) { mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Indirect"); }
      else { mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Direct"); }
      mvwprintw(win_info, cur_pos+1, INFO_BOX_W/2, "Range: %d+%d", u->get_range(), u->get_range_bonus());
      mvwprintw(win_info, cur_pos+2, INFO_BOX_W/2, "Accuracy: %d+%d", u->get_accuracy(), u->get_accuracy_bonus());
      mvwprintw(win_info, cur_pos+3, INFO_BOX_W/2, "Ranged Attack: %d+%d", u->get_ranged(),u->get_ranged_bonus());
      mvwprintw(win_info, cur_pos+4, INFO_BOX_W/2, "Ranged Pierce: %d+%d", u->get_ranged_ap(),u->get_ranged_ap_bonus());
      cur_pos+=6;
    }


  wattron(win_info, COLOR_PAIR(253));

  //Info Printed, press any key to close
  wrefresh(win_info);
  getch();
  delwin(win_info);
}
