#include <ncurses.h>
#include <vector>
#include "building_commands.h"
#include "combat.h"

/********* CONTENTS **********/

//(A) Building Recruit

//(B) Building Research

//(C) Building Attack

//(D) Building Ungarrison

//(E) Building Info

//(F) Make Gate

/********* CONTENTS **********/


//(A) Building Recruit
void building_recruit(map *game_map, building *b, int cur_p)
{
  int i, j;

  WINDOW *win_cmd;
  player *p = b->get_owner();
  int uclass = b->get_recruit_class();
  int num_uclass = p->get_num_uclass(uclass);
  int unit_act[num_uclass];
  unit_template *u;

  //Turns off cursor
  curs_set(0);
  
  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(b->y()-BUILD_BOX_H-1>0) { cmd_y=b->y()-BUILD_BOX_H; }
  //Places below
  else { cmd_y=b->y()+2; }
  //Places mid
  cmd_x = b->x()-(BUILD_BOX_W/2);
  //Places right
  if(b->x()-(BUILD_BOX_W/2)<0) { cmd_x = b->x(); }
  //Places left
  else if(b->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = b->x()-BUILD_BOX_W;}

  win_cmd = newwin(BUILD_BOX_H, BUILD_BOX_W, cmd_y, cmd_x);
  wattron(win_cmd, COLOR_PAIR(253));
  for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }
  wrefresh(win_cmd);

  //If building is not recruiting, opens recruiting window
  if(!b->recruiting())
    {
      int num_u = 0;
      //Prints out units
      for(i=1; i<num_uclass; i++)
	{  
	  u=p->get_unit(uclass, i);

	  //Prints if unit age is not beyond player's, player has prereq tech, and unit type has not been upgraded
	  if(p->get_age() >= u->age && p->tech_researched(u->prereq) 
	     && (
		 !p->tech_researched( p->get_unit(uclass, p->get_unit_idx(uclass,u->upgrade))->prereq) 
		 || u->upgrade==unit_default
		 )
	     )
	    {
	      mvwaddstr(win_cmd, num_u, 1, u->name.c_str());
	      unit_act[num_u]=i;
	      num_u++;
	    }
	}
      mvwaddstr(win_cmd, num_u, 1, "Cancel");

      //Buildings Menu Loop
      int command=0;
      int  cur_u=0;
      bool can_construct=false;
      while(command!=' ')
	{
	  attron(COLOR_PAIR(255));
	  mvaddstr(SCR_H-1,0,"                         ");
	  mvaddstr(SCR_H,0,"                                                ");
	  if(cur_u!=num_u)
	    {
	      u = p->get_unit(uclass, unit_act[cur_u]);

	      //Current Recruitability
	      //Check if unit would put pop over capacity or costs too much resources
	      if(  (p->get_cur_pop() - p->get_max_pop()) > u->pop 
		   || p->get_gold() < u->init_gold 
		   || p->get_food() < u->init_food
		   || p->get_wood() < u->init_wood
		   || p->get_stone() < u->init_stone )
		{
		  can_construct=false;
		  mvaddstr(SCR_H-1,0, "Cannot Recruit");
		}
	      else
		{
		  can_construct=true;
		  mvaddstr(SCR_H-1,0, "Can Recruit");
		}

	      //Resources
	      move(SCR_H,0);
	      //Pop
	      if(u->pop!=0) { 
		printw("Pop:"); 
		if(p->get_cur_pop() - u->pop > p->get_max_pop()) { attron(COLOR_PAIR(210)); }
		else if(u->pop>0) { attron(COLOR_PAIR(215)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",u->pop);
		attron(COLOR_PAIR(255));
	      }
	      //Gold
	      if(u->init_gold!=0) { 
		printw("Gold:"); 
		if(p->get_gold() - u->init_gold < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",u->init_gold);
		attron(COLOR_PAIR(255));
	      }
	      //Food
	      if(u->init_food!=0) { 
		printw("Food:"); 
		if(p->get_food() - u->init_food < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",u->init_food);
		attron(COLOR_PAIR(255));
	      }
	      //Wood
	      if(u->init_wood!=0) { 
		printw("Wood:"); 
		if(p->get_wood() - u->init_wood < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",u->init_wood);
		attron(COLOR_PAIR(255));
	      }
	      //Stone
	      if(u->init_stone!=0) { 
		printw("Stone:"); 
		if(p->get_stone() - u->init_stone < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",u->init_stone);
		attron(COLOR_PAIR(255));
	      }
	    }
	  mvwaddch(win_cmd, cur_u, 0, '>');
	  wrefresh(win_cmd);
	  refresh();
	  command=getch();

	  //Input Switch
	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, cur_u, 0, ' ');
	      if(cur_u==0) { cur_u=num_u; }
	      else { cur_u-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, cur_u, 0, ' ');
	      if(cur_u==num_u) { cur_u=0; }
	      else { cur_u+=1; }
	      break;

	    case ' ':
	      //Construction
	      //If return was not selected, constructs chosen building if resources available
	      if(cur_u<num_u && can_construct)
		{
		  b->set_recruit(u->type);
		  b->mod_recruit_time(u->time);
		  game_map->get_player(cur_p)->purchase(u->init_gold, u->init_food, u->init_wood, u->init_stone );
		  game_map->get_player(cur_p)->resource_output();
		}
	      //Returned
	      else if(cur_u!=num_u)
		{
		  command=0;
		}
	      break;

	    default:
	      break;
	    }
	}
    }
  //Otherwise shows recruitment info
  else
    {
      u=p->get_unit(uclass, p->get_unit_idx(uclass, b->get_recruit()) );

      //Prints info
      mvwprintw(win_cmd, 0,0, "Recruiting:");
      mvwprintw(win_cmd, 1,0, "%s",u->name.c_str());
      mvwprintw(win_cmd, 2,0, "%d Turns", b->rem_recruit_time());
      int cnt=0;
      if( p->get_cur_pop()-p->get_max_pop() > u->pop ) 
	{
	  mvwprintw(win_cmd, 3+cnt, 0, "Insufficient Pop");
	  cnt++;
	}
      if( !b->garrisonable() ) 
	{
	  mvwprintw(win_cmd, 3+cnt, 0, "Garrison at max capacity");
	  cnt++;
	}
      mvwprintw(win_cmd, 4+cnt, 1, "Cancel");
      mvwprintw(win_cmd, 5+cnt, 1, "Return");

      //Command
      int command=0;
      int cur_cmd=0;
      while(command!=' ')
	{
	  mvwaddch(win_cmd, 4+cur_cmd+cnt, 0, '>');
	  wrefresh(win_cmd);
	  command=getch();

	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, 4+cur_cmd+cnt, 0, ' ');
	      if(cur_cmd==0) { cur_cmd=1; }
	      else { cur_cmd-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, 4+cur_cmd+cnt, 0, ' ');
	      if(cur_cmd==1) { cur_cmd=0; }
	      else { cur_cmd+=1; }
	      break;
	    }
	}

      //If recruitment was cancelled, updates building
      if(cur_cmd==0)
	{
	  b->set_recruit(unit_default);
	  b->mod_recruit_time( -(b->rem_recruit_time()) );
	  game_map->get_player(cur_p)->purchase(-u->init_gold, -u->init_food, -u->init_wood, -u->init_stone );
	  game_map->get_player(cur_p)->resource_output();
	}

    }

  //Commands menu no longer needed, restores output
  attron(COLOR_PAIR(255));
  delwin(win_cmd);
  game_map->output_map(cur_p);
  game_map->get_tile(b->x(),b->y())->update_tile_info(b->x(), b->y());
}

//(B) Building Research
void building_research(map *game_map, building *b, int cur_p)
{
  int i, j;

  WINDOW *win_cmd, *win_bon;
  player *p = b->get_owner();
  int num_tech = b->num_techs();
  int tech_act[num_tech];
  tech *t;

  //Turns off cursor
  curs_set(0);
  
  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(b->y()-BUILD_BOX_H-1>0) { cmd_y=b->y()-BUILD_BOX_H; }
  //Places below
  else { cmd_y=b->y()+2; }
  //Places mid
  cmd_x = b->x()-(BUILD_BOX_W/2);
  //Places right
  if(b->x()-(BUILD_BOX_W/2)<0) { cmd_x = b->x(); }
  //Places left
  else if(b->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = b->x()-BUILD_BOX_W;}

  win_cmd = newwin(BUILD_BOX_H, BUILD_BOX_W, cmd_y, cmd_x);
  wattron(win_cmd, COLOR_PAIR(253));
  for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }
  wrefresh(win_cmd);

  //Bonus window
  int bon_x;
  //Places placs right
  bon_x = cmd_x+BUILD_BOX_W;
  //Places left
  if(b->x()+BUILD_BOX_W+30>MAP_WIDTH) { cmd_x = b->x()-30; }

  win_bon = newwin(6, 30, cmd_y, bon_x);
  wattron(win_bon, COLOR_PAIR(253));
  for(i=0; i<6; i++) { for(j=0; j<30; j++) { mvwaddch(win_bon, i,j,' '); } }
  wrefresh(win_bon);

  //If building is not researching, opens researching window
  if(!b->researching())
    {
      int num_t = 0;
      //Prints out units
      for(i=0; i<num_tech; i++)
	{  
	  t = p->get_tech(b->get_tech(i));

	  //Adds if tech has not been researched, tech's age has been reached, and if prereq has been met
	  if(!p->tech_researched(t->technology()) && p->get_age() >= t->age() && p->tech_researched(t->prereq()) )
	    {
	      mvwaddstr(win_cmd, num_t, 1, t->name().c_str());
	      tech_act[num_t]= t->technology();
	      num_t++;
	    }
	}
      mvwaddstr(win_cmd, num_t, 1, "Cancel");

      //Buildings Menu Loop
      int command=0;
      int  cur_t=0;
      bool can_research=false;
      std::vector<bonus *> *bons;
      while(command!=' ')
	{
	  attron(COLOR_PAIR(255));
	  mvaddstr(SCR_H-1,0,"                         ");
	  mvaddstr(SCR_H,0,"                                                ");
	  for(i=0; i<6; i++) { for(j=0; j<30; j++) { mvwaddch(win_bon, i,j,' '); } }
	  wrefresh(win_bon);
	  if(cur_t!=num_t)
	    {
	      t = p->get_tech(tech_act[cur_t]);
	      bons = t->get_bonus();

	      for(i=0; i < (int) bons->size(); i++)
		{
		  mvwprintw(win_bon, i, 0, " * %s", bons->at(i)->desc().c_str());
		}
	      wrefresh(win_bon);

	      //Current Recruitability
	      //Check if unit would put pop over capacity or costs too much resources
	      if(  p->get_gold() < t->gold() 
		   || p->get_food() < t->food()
		   || p->get_wood() < t->wood()
		   || p->get_stone() < t->stone() )
		{
		  can_research=false;
		  mvaddstr(SCR_H-1,0, "Cannot Research");
		}
	      else
		{
		  can_research=true;
		  mvaddstr(SCR_H-1,0, "Can Research");
		}

	      //Resources
	      move(SCR_H,0);
	      //Gold
	      if(t->gold()!=0) { 
		printw("Gold:"); 
		if(p->get_gold() - t->gold() < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",t->gold());
		attron(COLOR_PAIR(255));
	      }
	      //Food
	      if(t->food()!=0) { 
		printw("Food:"); 
		if(p->get_food() - t->food() < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",t->food());
		attron(COLOR_PAIR(255));
	      }
	      //Wood
	      if(t->wood()!=0) { 
		printw("Wood:"); 
		if(p->get_wood() - t->wood() < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",t->wood());
		attron(COLOR_PAIR(255));
	      }
	      //Stone
	      if(t->stone()!=0) { 
		printw("Stone:"); 
		if(p->get_stone() - t->stone() < 0) { attron(COLOR_PAIR(210)); }
		else { attron(COLOR_PAIR(213)); }
		printw(" %d ",t->stone());
		attron(COLOR_PAIR(255));
	      }
	    }
	  mvwaddch(win_cmd, cur_t, 0, '>');
	  wrefresh(win_cmd);
	  refresh();
	  command=getch();

	  //Input Switch
	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, cur_t, 0, ' ');
	      if(cur_t==0) { cur_t=num_t; }
	      else { cur_t-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, cur_t, 0, ' ');
	      if(cur_t==num_t) { cur_t=0; }
	      else { cur_t+=1; }
	      break;

	    case ' ':
	      //Research
	      //If return was not selected, constructs chosen building if resources available
	      if(cur_t<num_t && can_research)
		{
		  b->set_research(t->technology());
		  b->mod_research_time(t->time());
		  game_map->get_player(cur_p)->purchase(t->gold(), t->food(), t->wood(), t->stone() );
		  game_map->get_player(cur_p)->resource_output();
		}
	      //Returned
	      else if(cur_t!=num_t)
		{
		  command=0;
		}
	      break;

	    default:
	      break;
	    }
	}
    }
  //Otherwise shows recruitment info
  else
    {
      t = p->get_tech(b->get_research());

      //Prints info
      mvwprintw(win_cmd, 0,0, "Researching:");
      mvwprintw(win_cmd, 1,0, "%s",t->name().c_str());
      mvwprintw(win_cmd, 2,0, "%d Turns", b->rem_research_time());
      mvwprintw(win_cmd, 3, 1, "Cancel");
      mvwprintw(win_cmd, 4, 1, "Return");

      //Command
      int command=0;
      int cur_cmd=0;
      while(command!=' ')
	{
	  mvwaddch(win_cmd, cur_cmd+3, 0, '>');
	  wrefresh(win_cmd);
	  command=getch();

	  switch(command)
	    {
	    case KEY_UP:
	      mvwaddch(win_cmd, cur_cmd+3, 0, ' ');
	      if(cur_cmd==0) { cur_cmd=1; }
	      else { cur_cmd-=1; }
	      break;

	    case KEY_DOWN:
	      mvwaddch(win_cmd, cur_cmd+3, 0, ' ');
	      if(cur_cmd==1) { cur_cmd=0; }
	      else { cur_cmd+=1; }
	      break;
	    }
	}

      //If recruitment was cancelled, updates building
      if(cur_cmd==0)
	{
	  b->set_research(tech_default);
	  b->mod_research_time( -(b->rem_research_time()) );
	  game_map->get_player(cur_p)->purchase(-t->gold(), -t->food(), -t->wood(), -t->stone() );
	  game_map->get_player(cur_p)->resource_output();
	}

    }

  //Commands menu no longer needed, restores output
  attron(COLOR_PAIR(255));
  delwin(win_cmd);
  delwin(win_bon);
  game_map->output_map(cur_p);
  game_map->get_tile(b->x(),b->y())->update_tile_info(b->x(), b->y());
}

//(C) Building Attack
void building_attack(map *game_map, building *b, int cur_p)
{
  player *p = game_map->get_player(cur_p);
  int range=b->get_range();

  std::vector< std::vector<bool> > potential( (range*2)+1, std::vector<bool>((range*2)+1,true) );

  /*Presently not used - maybe if elevation is added?
  //If unit is not indirect, updates potential targets matrix indicating line of sight
  if(!b->indirect())
    {
      game_map->line_of_sight(b, &potential, range, false);
    }
  */

  //Places target area around unit
  int y,x;
  for(y=b->y()-range; y < b->y()+range+1; y++)
    {
      for(x=b->x()-range; x < b->x()+range+1; x++)
	{
	  if(x>0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
	    {
	      tile *t = game_map->get_tile(x,y);
	      //If empty or enemy entity within range, colors their background as target
	      if( ( (!t->get_entity()) || ( t->get_entity() && t->get_entity()->get_owner()!=p) )
	      		   && potential[y-b->y()+range][x-b->x()+range] )
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
  int command=0, tar_x=b->x(), tar_y=b->y();
  tile *tar_t;
  while(command!=' ')
    {
      mvaddstr(SCR_H-1, 0, "                              ");
      mvaddstr(SCR_H, 0, "                              ");
      tar_t=game_map->get_tile(tar_x,tar_y);
      move(tar_y+1,tar_x);

      //Outputs combat results in bottom screen if target is enemy
      if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p && potential[tar_y-b->y()+range][tar_x-b->x()+range] )
	{
	  combat_results( (entity*)b, tar_t->get_entity(), combat_ranged);
	  move(tar_y+1, tar_x);
	}

      command=getch();

      //Command Switch
      switch(command)
	{
	  //Move Left
	case KEY_LEFT:
	  if( tar_x-b->x()+range>0 
	      && tar_x>0 ) 
	    { tar_x--; }
	  break;

	  //Move Right
	case KEY_RIGHT:
	  if( tar_x-b->x()<range 
	     && tar_x<MAP_WIDTH ) 
	    { tar_x++; }
	  break;

	  //Move Up
	case KEY_UP:
	  if( tar_y-b->y()+range>0 
	     && tar_y>0 ) 
	    { tar_y--; }
	  break;

	  //Move DOWN
	case KEY_DOWN:
	  if( tar_y-b->y()<range 
	     && tar_y<MAP_HEIGHT ) 
	    { tar_y++; }
	  break;
	    
	default:
	  break;
	}
    }

  //Checks if target is enemy entity, if so, partakes in combat
  if(tar_t->get_entity() && tar_t->get_entity()->get_owner()!=p && potential[tar_y-b->y()+range][tar_x-b->x()+range] )
    {
      //Calls combat function which updates HP of both entities and removes them if one dies
      combat( (entity*) b, tar_t->get_entity(), combat_ranged);
      b->set_action(false);

      //Checks if either combatant died, if so, removes them
      if(b->get_hp()<=0) { game_map->remove_building(cur_p, b); }
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
      game_map->get_tile(b->x(),b->y())->update_tile_info(b->x(), b->y());
    }

  game_map->output_map(cur_p);
}

//(D) Building Ungarrison
void building_ungarrison(map *game_map, building *b, int cur_p)
{
  WINDOW *win_cmd;
  int gar = b->get_garrison_size();

  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(b->y()-gar-1>1) { cmd_y=b->y()-gar-1; }
  //Places below
  else { cmd_y=b->y()+gar+1; }
  //Places mid
  cmd_x = b->x()-(BUILD_BOX_W/2);
  //Places right
  if(b->x()-(BUILD_BOX_W/2)<0) { cmd_x = b->x(); }
  //Places left
  else if(b->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = b->x()-BUILD_BOX_W;}

  win_cmd = newwin(gar+1, BUILD_BOX_W, cmd_y, cmd_x);

  //Initializes output
  int i;
  for(i=0; i<gar; i++)
    {
      mvwaddstr(win_cmd, i, 1, b->get_garrison(i)->get_name().c_str());
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
      mvprintw(SCR_H, 0, "                           ");
      if(cur_cmd<gar)
	{
	  entity *ent = b->get_garrison(cur_cmd);
	  attron(COLOR_PAIR(210+ent->get_owner()->get_color()));
	  mvprintw(SCR_H-1, 0, ent->get_name().c_str());
	  attron(COLOR_PAIR(255));;
	  mvprintw(SCR_H, 0, "HP: %d/%d", ent->get_hp(), ent->get_max_hp()+ent->get_hp_bonus());
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

  //Cancel was not chosen
  if(cur_cmd!=gar)
    {
      //Changes target color to white
      if(COLORS>8) { init_color(252, (206*200)/51, (221*200)/51, (221*200)/51); }

      unit *e = (unit*) b->get_garrison(cur_cmd);

      //Places target area around unit
      int y,x;
      for(y=b->y()-b->get_deploy(); y < b->y()+b->get_deploy()+1; y++)
	{
	  for(x=b->x()-b->get_deploy(); x < b->x()+b->get_deploy()+1; x++)
	    {
	      if(x>0 && x<MAP_WIDTH && y>0 && y<MAP_HEIGHT)
		{
		  tile *t = game_map->get_tile(x,y);


		  //If empty space highlights
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
      int  tar_x=b->x(), tar_y=b->y();
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
	      if(tar_x>0 && tar_x > b->x()-b->get_deploy()) { tar_x--; }
	      break;

	      //Move Right
	    case KEY_RIGHT:
	      if(tar_x<MAP_WIDTH-1 && tar_x < b->x()+b->get_deploy()) { tar_x++; }
	      break;

	      //Move Up
	    case KEY_UP:
	      if(tar_y>0  && tar_y > b->y()-b->get_deploy()) { tar_y--; }
	      break;

	      //Move DOWN
	    case KEY_DOWN:
	      if(tar_y<MAP_HEIGHT  && tar_y < b->y()+b->get_deploy()) { tar_y++; }
	      break;
	    
	    case ' ':
	      //If tile has an entity, cannot be placed there
	      if(tar_t->get_entity()  || ( (!tar_t->land() && e->land()) || (!tar_t->water() && e->naval()) )) { command=0; }
	      break;

	    default:
	      break;
	    }
	}

      //Changes target color back to red
      if(COLORS>8) { init_color(252, (193*200)/51, (67*200)/51, (67*200)/51); }

      //Removes unit from garrison and places onto target tile
      tar_t->set_entity(b->remove_garrison(cur_cmd));
      tar_t->get_entity()->set_coords(tar_x,tar_y);
    }

  game_map->output_map(cur_p);
  refresh();
}

//(E) Building Info
void building_info(building *b)
{
  int y,x;
  int cur_pos;

  player *p = b->get_owner();
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
  mvwprintw(win_info, 1, (INFO_BOX_W/2)-(b->get_name().length())/2, b->get_name().c_str());
  mvwprintw(win_info, 2, (INFO_BOX_W/2)-(p->get_civ()->get_name().length())/2, p->get_civ()->get_name().c_str());
  wattron(win_info,COLOR_PAIR(255));

  //Hitpoints
  mvwprintw(win_info, 4, 2, "Hitpoints: ");
  int hp_perc = (b->get_hp()*100)/(b->get_max_hp()+b->get_hp_bonus());
  if(hp_perc<25) { wattron(win_info,COLOR_PAIR(210));}
  else if(hp_perc<50) { wattron(win_info,COLOR_PAIR(212));}
  else if(hp_perc<75) { wattron(win_info,COLOR_PAIR(213));}
  else { wattron(win_info,COLOR_PAIR(215));}
  wprintw(win_info, "%d", b->get_hp());
  wattron(win_info,COLOR_PAIR(255));
  wprintw(win_info, "/%d",b->get_max_hp()+b->get_hp_bonus());

  //Armor
  mvwprintw(win_info, 5, 2, "Armor: %d+%d",b->get_armor(),b->get_armor_bonus());

  //Sight
  mvwprintw(win_info, 6, 2, "Sight: %d+%d",b->sight(),b->sight_bonus());

  //Attack
  if(b->get_attack()>0)
    {
      mvwprintw(win_info, 7, 2, "Attack: %d+%d", b->get_attack(),b->get_attack_bonus());
      mvwprintw(win_info, 8, 2, "Attack Pierce: %d+%d", b->get_attack_ap(),b->ap_bonus());
      mvwprintw(win_info, 9, 2, "Range: %d+%d", b->get_range(),b->get_range_bonus());
    }

  //Class info
  //Primary Class
  mvwprintw(win_info, 4, INFO_BOX_W/2, "Building Class: %s", get_bclass_loc(b->get_class()).c_str());

  cur_pos=5;

  //Secondary Classes
  if(b->can_recruit())
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Recruitment Class: %s", get_uclass_loc( (unit_class) b->get_recruit_class()).c_str());
      cur_pos++;
    }

  cur_pos++;

  //Resources
  //Pop
  if(b->get_pop()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Pop: %d", b->get_pop());
      cur_pos++;
    }
  if(b->get_gold()+b->get_gold_bonus()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Gold: %d+%d", b->get_gold(),b->get_gold_bonus());
      cur_pos++;
    }
  if(b->get_food()+b->get_food_bonus()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Food: %d+%d", b->get_food(),b->get_food_bonus());
      cur_pos++;
    }
  if(b->get_wood()+b->get_wood_bonus()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Wood %d+%d", b->get_wood(),b->get_wood_bonus());
      cur_pos++;
    }
  if(b->get_stone()+b->get_stone_bonus()>0)
    {
      mvwprintw(win_info, cur_pos, INFO_BOX_W/2, "Stone: %d+%d", b->get_stone(),b->get_stone_bonus());
      cur_pos++;
    }

  wattron(win_info, COLOR_PAIR(253));

  //Info Printed, press any key to close
  wrefresh(win_info);
  getch();
  delwin(win_info);
}

//(F) Building Make Gate
void building_make_gate(map *game_map, building *b, int cur_p)
{
  player *p = game_map->get_player(cur_p);
  building_template *tmp = p->get_bldg(b->get_class(), p->get_bldg_idx(b->get_class(), bldg_gate) );
  building_template *old = p->get_bldg(b->get_class(),  p->get_bldg_idx(b->get_class(), b->get_type()) );
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
      //if(!p->tech_researched(tmp->prereq)) { printw(": Need Tech %s", p->get_tech(tmp->prereq)->name().c_str()); }
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
  if(b->y()-2-1>0) { cmd_y=b->y()-2; }
  //Places below
  else { cmd_y=b->y()+2; }
  //Places mid
  cmd_x = b->x()-(BUILD_BOX_W/2);
  //Places right
  if(b->x()-(BUILD_BOX_W/2)<0) { cmd_x = b->x(); }
  //Places left
  else if(b->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = b->x()-BUILD_BOX_W;}

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
  game_map->get_tile(b->x(),b->y())->update_tile_info(b->x(), b->y());

  //If upgrade is available and upgrade was selected, upgrades unit
  if(p->get_gold()-cost_g>=0 && p->get_food()-cost_f>=0 && p->get_wood()-cost_w>=0 && p->get_stone()-cost_s>=0 && p->get_age()>=tmp->age && p->tech_researched(tmp->prereq) && cur_cmd==0 )
    {
      //HP Remains same percent
      int hp=( b->get_hp()* (tmp->max_hp+tmp->hp_bonus) ) / (old->max_hp+old->hp_bonus);
      building *up = new building(tmp, b->x(), b->y());
      up->mod_hp(-up->get_max_hp());
      up->mod_hp(hp);

      //Transfer garrison if any
      /*
      if(u->get_garrison_size() > 0)
	{
	  int i;
	  for(i=0; i < (int) u->get_garrison_size(); i++) { up->add_garrison(u->remove_garrison(i)); }
	}
      */
      //Adds unit to map
      up->set_action(false);
      game_map->remove_building(cur_p, b);
      game_map->add_building(cur_p, up);


      //Updates tile info
      game_map->get_tile(up->x(),up->y())->update_tile_info(up->x(), up->y());
    }

  //Commands menu no longer needed, restores output
  delwin(win_cmd);
  game_map->output_map(cur_p);
  refresh();
}
