#include <string>
#include <vector>
#include <ncurses.h>
#include "skirmish.h"
#include "macros.h"
#include "map.h"
#include "player.h"
#include "entity.h"
#include "building_templates.h"
#include "unit_commands.h"
#include "building_commands.h"

/********* CONTENTS **********/
//(A) Initialize Game

//(B) Game Main
void game_main(map*);
//(C) Player Turn
void player_turn(map*, int);

//(D) Human Turn
void human_turn(map*, int);

//(E) Entity Command
void entity_command(map*, entity*, int);

//(F) Unit Command
void unit_command(map*, unit*, int, WINDOW*);

//(G) Building Command
void building_command(map*, building*, int, WINDOW*);

//(ZA) Is Alive
bool is_alive(map*, int);

//(ZB) Entity Reset
void entity_reset(map *, int);

/********* CONTENTS **********/

//Turn Counter
int turn;
//Game
bool exit_game;

//Shortcuts for player access
int start[2][2] = { {0,0}, {0,0} };
#define p1 0
#define p2 1
#define p1x start[0][0]
#define p1y start[0][1]
#define p2x start[1][0]
#define p2y start[1][1]

//(A) Initialize Game
//Initializes the players using the given information as well as the map
void initialize_game(int map_type, bool h_p1, civilization *civ_p1, int c_p1, bool h_p2, civilization *civ_p2, int c_p2)
{
  //Initializes Globals
  turn=1;
  exit_game=false;

  //Initializes game map
  map *game_map = new map( (enum map_type) map_type);
  start[0][0]=game_map->get_start_x(p1), start[0][1]=game_map->get_start_y(p1);
  start[1][0]=game_map->get_start_x(p2), start[1][1]=game_map->get_start_y(p2);
  game_map->add_player( new player(h_p1, civ_p1, c_p1) );
  game_map->add_player( new player(h_p2, civ_p2, c_p2) );

  //Gives each player starting castle and builders
  //Player 1
  game_map->add_building( p1, new building(new building_template(bldg_castle), p1x, p1y) );
  game_map->add_unit( p1, new unit(new unit_template(unit_builders), p1x, p1y-2) );
  game_map->add_unit( p1, new unit(new unit_template(unit_builders), p1x+2, p1y-2) );
  game_map->add_unit( p1, new unit(new unit_template(unit_builders), p1x+2, p1y) );
  //Player 2
  game_map->add_building( p2, new building(new building_template(bldg_castle), p2x, p2y) );
  game_map->add_unit( p2, new unit(new unit_template(unit_builders), p2x, p2y+2) );
  game_map->add_unit( p2, new unit(new unit_template(unit_builders), p2x-2, p2y+2) );
  game_map->add_unit( p2, new unit(new unit_template(unit_builders), p2x-2, p2y) );

  //Outputs Starting Map
  clear();

  //Calls core game function
  game_main(game_map);
}

//(B) Game Main
//Runs the core of the game, determines when to exit, player turns, etc.
void game_main(map *game_map)
{
  //Turn information
  int cur_p;

  //Game Loop
  while( is_alive(game_map, p1) && is_alive(game_map, p2) && !exit_game)
    {
      for(cur_p=0; cur_p<game_map->get_player_count() && !exit_game; cur_p++)
	{
	  game_map->update_los(cur_p);
	  game_map->output_map(cur_p);
	  player_turn(game_map, cur_p);
	  game_map->get_player(cur_p)->update_resources();
	  game_map->update_building_queue(cur_p);
	}
      turn++;
    }
}

//(C) Player Turn
//Gives control to current player
//Player makes commands until end turn command input
  void player_turn(map *game_map, int cur_p)
{
  player *p = game_map->get_player(cur_p);

  //Resets entity action flag and movement
  entity_reset(game_map, cur_p);

  game_map->output_map(cur_p);

  p->resource_output();

  //Player Info
  std::string civ_loc = p->get_civ()->get_name();
  std::string ages[] = {"Early", "High", "Late" };
  attron(COLOR_PAIR(210+p->get_color()));
  mvprintw(SCR_H-1, MAP_WIDTH-civ_loc.length()-11, "Player %d: ", cur_p+1);
  mvprintw(SCR_H-1, MAP_WIDTH-civ_loc.length()-1, civ_loc.c_str());
  attron(COLOR_PAIR(255));
  mvprintw(SCR_H, MAP_WIDTH-14-ages[p->get_age()].length(), "Age: %s", ages[p->get_age()].c_str());
  mvprintw(SCR_H, MAP_WIDTH-8, "Turn %d", turn);
  
  //If human, goes to commands function
  if(p->human()) { human_turn(game_map, cur_p); }
  //Otherwise, executes AI determined moves
}

//(D) Human Turn
//Has commands for human player
void human_turn(map *game_map, int cur_p)
{
  int command;
  int cur_x = game_map->get_start_x(cur_p);
  int cur_y = game_map->get_start_y(cur_p);
  tile *curs_tile = game_map->get_tile(cur_x, cur_y);
  curs_tile->get_type();

  //Initializes Tile Info
  curs_tile->update_tile_info(cur_x, cur_y);

  //Makes cursor visible and moves it to player starting point
  curs_set(1);

  //Command Loop
  bool end_turn=false;
  while(!end_turn)
    {
      move(cur_y+1, cur_x);
      command=getch();

      //Commands list
      switch(command)
	{
	  //Move cursor up
	  //Updates tile info
	case KEY_UP:
	  //Cannot move above map
	  if(cur_y+1>1) { cur_y-=1; }
	  else { cur_y = MAP_HEIGHT-1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  break;

	  //Move cursor down
	  //Updates tile info
	case KEY_DOWN:
	  //Cannot move below map
	  if(cur_y+1<MAP_HEIGHT) { cur_y+=1; }
	  else { cur_y=0; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  break;

	  //Move cursor right
	  //Updates tile info
	case KEY_RIGHT:
	  //Cannot move beyond map
	  if(cur_x<MAP_WIDTH-1) { cur_x+=1; }
	  else { cur_x=0; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  break;

	  //Move cursor left
	  //Updates tile info
	case KEY_LEFT:
	  //Cannot move beyond map
	  if(cur_x>0) { cur_x-=1; }
	  else { cur_x = MAP_WIDTH-1; }
	  curs_tile = game_map->get_tile(cur_x, cur_y);
	  curs_tile->update_tile_info(cur_x, cur_y);
	  break;

	  //Select
	case ' ':
	  //First checks if tile has an entity
	  if(curs_tile->get_entity()) 
	    { 
	      entity_command(game_map, curs_tile->get_entity(), cur_p); 
	      curs_set(1);
	    }
	  break;

	  //End Turn - Enter
	case 10:
	  end_turn=true;
	  break;

	  //TEMP-Quit - Escape
	case 27:
	  exit_game=true;
	  end_turn=true;
	  break;
	default:
	  break;
	}
      refresh();
    } 

  //Turns off cursor
  curs_set(0);
}

//(E) Entity command
void entity_command(map *game_map, entity *ent, int cur_p)
{
  WINDOW *win_cmd;

  //Turns off cursor
  curs_set(0);

  //Menu window
  int cmd_x, cmd_y;
  //Places above
  if(ent->y()-BUILD_BOX_H-1>0) { cmd_y=ent->y()-BUILD_BOX_H; }
  //Places below
  else { cmd_y=ent->y()+2; }
  //Places mid
  cmd_x = ent->x()-(BUILD_BOX_W/2);
  //Places right
  if(ent->x()-(BUILD_BOX_W/2)<0) { cmd_x = ent->x(); }
  //Places left
  else if(ent->x()+(BUILD_BOX_W/2)>MAP_WIDTH-1){ cmd_x = ent->x()-BUILD_BOX_W;}

  win_cmd = newwin(CMD_BOX_H, CMD_BOX_W, cmd_y, cmd_x);
  //Colors background
  int i,j;
  wattron(win_cmd, COLOR_PAIR(253));
  for(i=0; i<BUILD_BOX_H; i++) { for(j=0; j<BUILD_BOX_W; j++) { mvwaddch(win_cmd, i,j,' '); } }

  wrefresh(win_cmd);

  //Selected entity is unit
  if(ent->get_entity_type()==entity_unit)
    {
      unit_command(game_map, (unit*) ent, cur_p, win_cmd);
    }
  //Selected entity is building
  else if(ent->get_entity_type()==entity_building)
    {
      building_command(game_map, (building*) ent, cur_p, win_cmd);
    }
}

//(F) Unit command
void unit_command(map*game_map, unit *u, int cur_p, WINDOW *win_cmd)
{
  //List of all commands
  enum cmd { cmd_move, cmd_construct, cmd_melee, cmd_ranged, cmd_garrison, cmd_ungarrison, cmd_upgrade, cmd_disband, cmd_info, cmd_cancel };
  int cmds[10];

  int num_cmds=0;
  //Populates command list

  //Non-owned entitites can only have their info looked at
  if(u->get_owner()==game_map->get_player(cur_p))
    {
      //Checks if can move - Does not use action
      if(u->get_cur_move()>0 && (u->has_action() || u->has_subclass(unit_class_skirmisher) ) ) 
	{
	  cmds[num_cmds]=cmd_move;
	  mvwprintw(win_cmd,num_cmds,0, " Move");
	  num_cmds++;
	}
      //Checks if builder and can construct
      if(u->has_action() && u->get_type()==unit_builders ) 
	{
	  cmds[num_cmds]=cmd_construct;
	  mvwaddstr(win_cmd,num_cmds,0, " Construct");
	  num_cmds++;
	}
      //Checks if has melee capabilities
      if(u->has_action() && u->get_melee()>0 ) 
	{
	  cmds[num_cmds]=cmd_melee;
	  mvwaddstr(win_cmd,num_cmds,0, " Melee Atk");
	  num_cmds++;
	}
      //Checks if has ranged capabilities
      if(u->has_action() && u->get_ranged()>0 ) 
	{
	  cmds[num_cmds]=cmd_ranged;
	  mvwaddstr(win_cmd,num_cmds,0, " Ranged Atk");
	  num_cmds++;
	}
      //Checks if there is a nearby entity in which unit can garrison
      //Units with a garrison cannot garrison to prevent infinite space
      //NOTE - Naval units cannot garrison land units
      if(u->has_action() && u->get_garrison_size()==0 )
	{
	  cmds[num_cmds]=cmd_garrison;
	  mvwaddstr(win_cmd,num_cmds,0, " Garrison");
	  num_cmds++;
	}
      //Checks if unit is garrisonable and if it has a garrison
      if(u->get_max_garrison()>0 )
	{
	  cmds[num_cmds]=cmd_ungarrison;
	  if(u->get_garrison_size()>0)
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " Ungarrison");
	    }
	  else
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " <Empty>");
	    }
	  num_cmds++;
	}
      //Checks if there is a nearby entity in which unit can garrison
      if(u->has_action() && u->upgradable() )
	{
	  cmds[num_cmds]=cmd_upgrade;
	  mvwaddstr(win_cmd,num_cmds,0, " Upgrade");
	  num_cmds++;
	}
      //Always added regardless
      //Disband
      cmds[num_cmds]=cmd_disband;
      mvwaddstr(win_cmd,num_cmds,0, " Disband");
      num_cmds++;
    }

  //Any player can use these two commands
  //Info
  cmds[num_cmds]=cmd_info;
  mvwaddstr(win_cmd,num_cmds,0, " Info");
  num_cmds++;
  //Cancel
  cmds[num_cmds]=cmd_cancel;
  mvwaddstr(win_cmd,num_cmds,0, " Cancel");
  num_cmds++;

  int command=0, cur_cmd=0;
  //Menu Loop
  while(command!=' ')
    {
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

  //Commands menu no longer needed, restores output
  delwin(win_cmd);
  game_map->output_map(cur_p);
  refresh();

  //Command Switch
  switch(cmds[cur_cmd])
    {
      //Move
    case cmd_move:
      curs_set(1);
      unit_move(game_map, u, cur_p);
      break;

      //Construct
    case cmd_construct:
      unit_construct(game_map, u, cur_p);
      break;

      //Melee
    case cmd_melee:
      unit_melee(game_map, u, cur_p);
      break;

      //Ranged
    case cmd_ranged:
      unit_ranged(game_map, u, cur_p);
      break;

      //Garrison
    case cmd_garrison:
      unit_garrison(game_map, u, cur_p);
      break;

      //Ungarrison
    case cmd_ungarrison:
      //If has a garrison, opens garrison window
      if(u->get_garrison_size()>0) { unit_ungarrison(game_map, u, cur_p); }
      break;

      //Upgrade
    case cmd_upgrade:
      unit_upgrade(game_map, u, cur_p);
      break;

      //Disband
    case cmd_disband:
      game_map->remove_unit(cur_p, u);
      break;

      //Info
    case cmd_info:
      unit_info(u);
      game_map->output_map(cur_p);
      break;

      //Cancel
    default:
      break;
    }
}

//(G) Building command
void building_command(map*game_map, building *b, int cur_p, WINDOW *win_cmd)
{
  //List of all commands
  enum cmd {cmd_recruit, cmd_research, cmd_attack, cmd_make_gate, cmd_ungarrison, cmd_destroy, cmd_info, cmd_cancel };
  int cmds[7];

  int num_cmds=0;
  //Populates command list

  //Non-owned entitites can only have their info looked at
  if(b->get_owner()==game_map->get_player(cur_p))
    {
      //Checks if building can recruit
      if(b->can_recruit()) 
	{
	  cmds[num_cmds]=cmd_recruit;
	  if(!b->recruiting())
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " Recruit");
	    }
	  else
	    {
	      mvwprintw(win_cmd,num_cmds,0, " Recrtng");
	    }
	  num_cmds++;
	}
      //Checks if building can research
      if(b->can_research()) 
	{
	  cmds[num_cmds]=cmd_research;
	  if(!b->researching())
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " Research");
	    }
	  else
	    {
	      mvwprintw(win_cmd,num_cmds,0, " Resrchng");
	    }
	  num_cmds++;
	}
      //Checks if has attacking capabilities (Requires action)
      if(b->has_action() && b->get_attack()>0 ) 
	{
	  cmds[num_cmds]=cmd_attack;
	  mvwaddstr(win_cmd,num_cmds,0, " Attack");
	  num_cmds++;
	}
      //If building is a wall, can be made into a gate
      if(b->get_type()==bldg_wall) 
	{
	  cmds[num_cmds]=cmd_make_gate;
	  mvwaddstr(win_cmd,num_cmds,0, " Make Gate");
	  num_cmds++;
	}
      //Checks if building is garrisonable and if it has a garrison
      if(b->get_max_garrison()>0 )
	{
	  cmds[num_cmds]=cmd_ungarrison;
	  if(b->get_garrison_size()>0)
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " Ungarrison");
	    }
	  else
	    {
	      mvwaddstr(win_cmd,num_cmds,0, " <Empty>");
	    }
	  num_cmds++;
	}
      //Always added regardless
      //Disband
      cmds[num_cmds]=cmd_destroy;
      mvwaddstr(win_cmd,num_cmds,0, " Destroy");
      num_cmds++;
    }

  //Any player can use these two commands
  //Info
  cmds[num_cmds]=cmd_info;
  mvwaddstr(win_cmd,num_cmds,0, " Info");
  num_cmds++;
  //Cancel
  cmds[num_cmds]=cmd_cancel;
  mvwaddstr(win_cmd,num_cmds,0, " Cancel");
  num_cmds++;

  int command=0, cur_cmd=0;
  //Menu Loop
  while(command!=' ')
    {
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

  //Commands menu no longer needed, restores output
  delwin(win_cmd);
  game_map->output_map(cur_p);
  refresh();

  //Command Switch
  switch(cmds[cur_cmd])
    {
      //Recruit
    case cmd_recruit:
      building_recruit(game_map, b, cur_p);
      break;

      //Research
    case cmd_research:
      building_research(game_map, b, cur_p);
      break;

      //Attack
    case cmd_attack:
      building_attack(game_map, b, cur_p);
      break;

      //Make Gate
    case cmd_make_gate:
      building_make_gate(game_map, b, cur_p);
      break;

      //Ungarrison
    case cmd_ungarrison:
      //If has a garrison, opens garrison window
      if(b->get_garrison_size()>0) { building_ungarrison(game_map, b, cur_p); }
      break;

      //Destroy
    case cmd_destroy:
      game_map->remove_building(cur_p, b);
      break;

      //Info
    case cmd_info:
      building_info(b);
      game_map->output_map(cur_p);
      break;

      //Cancel
    default:
      break;
    }
}

//(ZA) Is alive
//Checks if given player hasn't lost all their units and buildings
//If they, they are eliminated are thus dead
bool is_alive(map *game_map, int p)
{
  if( game_map->has_units(p) || game_map->has_buildings(p) ) { return true; }
  else { return false; }
}

//(ZB) Entity Reset
//Resets entity action flag and movement
void entity_reset(map *game_map, int cur_p)
{
  int k;

  //Buildings - Resets action flag only
  for(k=0; k<game_map->num_buildings(cur_p); k++)
    {
      game_map->get_building(cur_p, k)->set_action(true);
    }

  //Units - Resets action flag and movement
  for(k=0; k<game_map->num_units(cur_p); k++)
    {
      game_map->get_unit(cur_p, k)->set_action(true);
      game_map->get_unit(cur_p, k)->reset_move();
    }
}
