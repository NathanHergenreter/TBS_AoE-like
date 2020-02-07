/********* CONTENTS **********/
//(A) Main Menu

//(B) New Game Menu
void menu_new_game();

/********* CONTENTS **********/

//Misc
#include <cstdlib>
#include <ctime>
#include <string>
#include <vector>
#include <ncurses.h>
#include "macros.h"
#include "colors.h"
#include "map.h"
#include "skirmish.h"
#include "civilization.h"

//Main Function - Main Menu
int main(int argc, char *argv[])
{

  //Randomness Seeding
  srand(time(NULL));

  //Initializes screen
  initscr();
  cbreak();
  keypad(stdscr, TRUE);
  noecho();
  start_color();
  initialize_colors();
  curs_set(0);

  //Main Game Outer Loop
  bool exit=false;
  while(!exit)
    {
      erase();
      attron(COLOR_PAIR(255));

      //If full colors, changes background color
      if(COLORS>8) { int kx,ky; for(ky=0; ky<SCR_H+1; ky++) { for(kx=0; kx<SCR_W; kx++){ mvaddch(ky,kx, ' '); } } }

      //Prints menu options
      mvprintw(0,6, " _______  _______  _______      _       _________ _        _______ ");
      mvprintw(1,6, "(  ___  )(  ___  )(  ____ \\    ( \\      \\__   __/| \\    /\\(  ____ \\");
      mvprintw(2,6, "| (   ) || (   ) || (    \\/    | (         ) (   |  \\  / /| (    \\/");
      mvprintw(3,6, "| (___) || |   | || (__  _____ | |         | |   |  (_/ / | (__    ");
      mvprintw(4,6, "|  ___  || |   | ||  __)(_____)| |         | |   |   _ (  |  __)   ");
      mvprintw(5,6, "| (   ) || |   | || (          | |         | |   |  ( \\ \\ | (      ");
      mvprintw(6,6, "| )   ( || (___) || (____/\\    | (____/\\___) (___|  /  \\ \\| (____/\\");
      mvprintw(7,6, "|/     \\|(_______)(_______/    (_______/\\_______/|_/    \\/(_______/");

      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color for options
      std::string opt[4] = {"New Game", "Guide", "Encyclopedia", "Quit" };
      mvprintw((SCR_H/2)+0, (SCR_W/2)-16/2, "                ");
      mvprintw((SCR_H/2)+0, (SCR_W/2)-opt[0].length()/2, opt[0].c_str());
      mvprintw((SCR_H/2)+2, (SCR_W/2)-16/2, "                ");
      mvprintw((SCR_H/2)+2, (SCR_W/2)-opt[1].length()/2, opt[1].c_str());
      mvprintw((SCR_H/2)+4, (SCR_W/2)-16/2, "                ");
      mvprintw((SCR_H/2)+4, (SCR_W/2)-opt[2].length()/2, opt[2].c_str());
      mvprintw((SCR_H/2)+6, (SCR_W/2)-16/2, "                ");
      mvprintw((SCR_H/2)+6, (SCR_W/2)-opt[3].length()/2, opt[3].c_str());
      //mvprintw(SCR_H/2-2, (SCR_W/2)-20, "An AoE inspired TBS by Nathan Hergenreter");
      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Reset
      mvprintw(SCR_H-1, (SCR_W/2)-15, "Press Arrow Keys to move cursor"); 
      mvprintw(SCR_H, (SCR_W/2)-10, "Press Space to select");
      refresh();

      //Main Menu Select
      int command;
      int cur_opt = 0;
      bool select=false;

      //Menu Loop
      while(!select)
	{
	  mvaddch( (SCR_H/2)+(cur_opt*2), (SCR_W/2)-9, '>');
	  refresh();
	  command=getch();

	  //Input Switch
	  switch(command)
	    {
	    case KEY_UP:
	      mvaddch( (SCR_H/2)+(cur_opt*2), (SCR_W/2)-9, ' ');
	      if(cur_opt==0) { cur_opt=3; }
	      else { cur_opt-=1; }
	      break;

	    case KEY_DOWN:
	      mvaddch( (SCR_H/2)+(cur_opt*2), (SCR_W/2)-9, ' ');
	      if(cur_opt==3) { cur_opt=0; }
	      else { cur_opt+=1; }
	      break;

	    case ' ':
	      if(cur_opt==0) { menu_new_game(); }
	      else if(cur_opt==1) { }
	      else if(cur_opt==2) { }
	      else if(cur_opt==3) { exit=true; }
	      select=true;
	      break;

	    default:
	      break;
	    }
	}
    }

  //Game exited, screen closed
  attroff(COLOR_PAIR(255));
  endwin();
}

//(B) New Game Menu
void menu_new_game()
{
  erase();
  //If full colors, changes background color
  if(COLORS>8) { int kx,ky; for(ky=0; ky<SCR_H+1; ky++) { for(kx=0; kx<SCR_W; kx++){ mvaddch(ky,kx, ' '); } } }
  std::vector<civilization*> civs = create_civs();
  int cur_map = map_plains;
  bool h_p1=true, h_p2=true;
  int civ_p1=civ_english, civ_p2=civ_french;
  int c_p1=P_RED, c_p2=P_BLUE;
  int colors[12] = {1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0};
  std::string opt[5] = {"    Map Type:", "--Player 1--", "--Player 2--", "Start", "Exit" };
  int opt_y[9] = {SCR_H/5, SCR_H/5+4, SCR_H/5+5, SCR_H/5+6, SCR_H/5+9, SCR_H/5+10, SCR_H/5+11, SCR_H/5+13, SCR_H/5+15};

  //Map Info Box
  int i, k;
  for(i=1; i<8; i++) { mvaddch(i, SCR_W-36, '|'); }
  for(i=1; i<8; i++) { mvaddch(i, SCR_W-1, '|'); }
  for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(0, i, '_'); }
  for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(8, i, '_'); }

  //Map Desc
  std::vector<std::string> desc = get_map_desc( (enum map_type) cur_map);
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  for(k=0; k < (int) desc.size(); k++)
    {
      mvprintw(2+k, SCR_W-34, "                                ");
      mvprintw(2+k, SCR_W-34, desc[k].c_str());
    }
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg

  //Civilization Info Box
  for(i=9; i<20; i++) { mvaddch(i, SCR_W-36, '|'); }
  for(i=9; i<20; i++) { mvaddch(i, SCR_W-1, '|'); }
  for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(9, i, '_'); }
  for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(19, i, '_'); }
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  for(k=8; k < 17; k++)
    {
      mvprintw(2+k, SCR_W-34, "                                ");
    }
  mvprintw(10, SCR_W-34, "%s", civs[civ_p1]->get_name().c_str());
  mvprintw(11, SCR_W-34, "Unique Unit: %s", get_unit_loc( (enum unit_type) civs[civ_p1]->unique()  ).c_str());
  mvprintw(12, SCR_W-34, "Civ Bonuses:");
  //Bonuses
  for(k=0; k < (int) civs[civ_p1]->bonus_1()->size(); k++)
    {
      mvprintw(13+k, SCR_W-34, "  * %s", civs[civ_p1]->bonus_1()->at(k)->desc().c_str());
    }
  for(k=0; k < (int) civs[civ_p1]->bonus_2()->size(); k++)
    {
      mvprintw(13+civs[civ_p1]->bonus_1()->size()+k, SCR_W-34, "  * %s", civs[civ_p1]->bonus_2()->at(k)->desc().c_str());
    }
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg

  //Map
  mvprintw(opt_y[0], 6, opt[0].c_str());
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  mvprintw(opt_y[0], 6+opt[0].length()+1, "                "); 
  mvprintw(opt_y[0], 6+opt[0].length()+1, map_type_loc( (enum map_type) cur_map).c_str());
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
  
  //P1
  mvprintw(SCR_H/5+3, 6, opt[1].c_str());
  mvprintw(opt_y[1], 6, " Player Type:");
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  mvprintw(opt_y[1], 6+14, "                "); 
  mvprintw(opt_y[1], 6+14, "Human");
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
  mvprintw(opt_y[2], 6, "Civilization:");
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  mvprintw(opt_y[2], 6+14, "                "); 
  mvprintw(opt_y[2], 6+14, civs[civ_p1]->get_name().c_str());
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
  mvprintw(opt_y[3], 6, "       Color:");
  attron(COLOR_PAIR(230+c_p1));
  mvaddch(opt_y[3], 6 + 14, ' ');
  attron(COLOR_PAIR(255));

  //P2
  mvprintw(SCR_H/5+8, 6, opt[2].c_str());
  mvprintw(opt_y[4], 6, " Player Type:");
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  mvprintw(opt_y[4], 6+14, "                "); 
  mvprintw(opt_y[4], 6+14, "Human");
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
  mvprintw(opt_y[5], 6, "Civilization:");
  if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
  mvprintw(opt_y[5], 6+14, "                "); 
  mvprintw(opt_y[5], 6+14, civs[civ_p2]->get_name().c_str());
  if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
  mvprintw(opt_y[6], 6, "       Color:");
  attron(COLOR_PAIR(230+c_p2));
  mvaddch(opt_y[6], 6 + 14, ' ');
  attron(COLOR_PAIR(255));
  
  //Start/Exit
  mvprintw(opt_y[7], 6, opt[3].c_str());
  mvprintw(opt_y[8], 6, opt[4].c_str());
  
  mvprintw(SCR_H-1, (SCR_W/2)-36, "Press Arrow Keys to move cursor (Up/Down) and change selection (Left/Right)"); 
  mvprintw(SCR_H, (SCR_W/2)-18, "Press Space to select Start or Exit");
  refresh();

  //New Game Selection Loop
  int command;
  int cur_opt = 0;
  bool exit=false, start=false;
  
  while(!exit)
    {
      mvaddch( opt_y[cur_opt], 5, '>');
      move( opt_y[cur_opt], 5 );
      refresh();
      command=getch();

      //Input Switch
      switch(command)
	{
	case KEY_UP:
	  mvaddch( opt_y[cur_opt], 5, ' ');
	  if(cur_opt==0) { cur_opt=8; }
	  else { cur_opt-=1; }
	  break;

	case KEY_DOWN:
	  mvaddch( opt_y[cur_opt], 5, ' ');
	  if(cur_opt==8) { cur_opt=0; }
	  else { cur_opt+=1; }
	  break;

	case KEY_LEFT:
	  //Map Type
	  if(cur_opt==0) 
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(cur_map==0) { cur_map=3; }
	      cur_map-=1;
	      mvprintw(opt_y[0], 6+opt[0].length()+1, "                "); 
	      mvprintw(opt_y[0], 6+opt[0].length()+1, map_type_loc( (enum map_type) cur_map).c_str()); 
	      
	      //Map Desc
	      desc = get_map_desc( (enum map_type) cur_map);
	      for(k=0; k < (int) desc.size(); k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		  mvprintw(2+k, SCR_W-34, desc[k].c_str());
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Player Type P1
	  else if(cur_opt==1)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(h_p1) { h_p1=false; mvprintw(opt_y[1], 6+14, "CPU  "); } 
	      else {  h_p1=true; mvprintw(opt_y[1], 6+14, "Human"); }
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Civ P1
	  else if(cur_opt==2)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(civ_p1==0) { civ_p1=civs.size(); }
	      civ_p1-=1;
	      mvprintw(opt_y[2], 6+14, "                "); 
	      mvprintw(opt_y[2], 6+14, civs[civ_p1]->get_name().c_str());
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg 

	      //Civilization Info Box
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-36, '|'); }
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-1, '|'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(9, i, '_'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(19, i, '_'); }
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      for(k=8; k < 17; k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		}

	      //Checks if not random
	      if(civ_p1!=civ_random)
		{
		  mvprintw(10, SCR_W-34, "%s", civs[civ_p1]->get_name().c_str());
		  mvprintw(11, SCR_W-34, "Unique Unit: %s", get_unit_loc( (enum unit_type) civs[civ_p1]->unique()  ).c_str());
		  mvprintw(12, SCR_W-34, "Civ Bonuses:");
		  //Bonuses
		  for(k=0; k < (int) civs[civ_p1]->bonus_1()->size(); k++)
		    {
		      mvprintw(13+k, SCR_W-34, " * %s", civs[civ_p1]->bonus_1()->at(k)->desc().c_str());
		    }
		  for(k=0; k < (int) civs[civ_p1]->bonus_2()->size(); k++)
		    {
		      mvprintw(13+civs[civ_p1]->bonus_1()->size()+k, SCR_W-34, " * %s", civs[civ_p1]->bonus_2()->at(k)->desc().c_str());
		    }
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Color P1
	  else if(cur_opt==3)
	    {
	      colors[c_p1]=0;
	      if(c_p1==0) { c_p1 = 12; }
	      if(colors[c_p1-1]==0) { c_p1-=1; } 
	      else { if(c_p1!=1) { c_p1-=2; } else { c_p1=11; } }
	      attroff(COLOR_PAIR(255));
	      attron(COLOR_PAIR(230+c_p1));
	      mvaddch(opt_y[3], 6 + 14, ' ');
	      attron(COLOR_PAIR(255));
	      colors[c_p1]=1;
	    }
	  //Player Type P2
	  else if(cur_opt==4)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(h_p2) { h_p2=false; mvprintw(opt_y[4], 6+14, "CPU  "); } 
	      else {  h_p2=true; mvprintw(opt_y[4], 6+14, "Human"); }
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Civ P2
	  else if(cur_opt==5)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(civ_p2==0) { civ_p2=civs.size(); }
	      civ_p2-=1;
	      mvprintw(opt_y[5], 6+14, "                "); 
	      mvprintw(opt_y[5], 6+14, civs[civ_p2]->get_name().c_str()); 
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg

	      //Civilization Info Box
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-36, '|'); }
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-1, '|'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(9, i, '_'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(19, i, '_'); }
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      for(k=8; k < 17; k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		}

	      //Checks if not random
	      if(civ_p2!=civ_random)
		{
		  mvprintw(10, SCR_W-34, "%s", civs[civ_p2]->get_name().c_str());
		  mvprintw(11, SCR_W-34, "Unique Unit: %s", get_unit_loc( (enum unit_type) civs[civ_p2]->unique()  ).c_str());
		  mvprintw(12, SCR_W-34, "Civ Bonuses:");
		  //Bonuses
		  for(k=0; k < (int) civs[civ_p2]->bonus_1()->size(); k++)
		    {
		      mvprintw(13+k, SCR_W-34, " * %s", civs[civ_p2]->bonus_1()->at(k)->desc().c_str());
		    }
		  for(k=0; k < (int) civs[civ_p2]->bonus_2()->size(); k++)
		    {
		      mvprintw(13+civs[civ_p2]->bonus_1()->size()+k, SCR_W-34, " * %s", civs[civ_p2]->bonus_2()->at(k)->desc().c_str());
		    }
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Color P2
	  else if(cur_opt==6)
	    {
	      colors[c_p2]=0;
	      if(c_p2==0) { c_p2 = 12; }
	      if(colors[c_p2-1]==0) { c_p2-=1; } 
	      else { if(c_p2!=1) { c_p2-=2; } else { c_p2=11; }  }
	      attroff(COLOR_PAIR(255));
	      attron(COLOR_PAIR(230+c_p2));
	      mvaddch(opt_y[6], 6 + 14, ' ');
	      attron(COLOR_PAIR(255));
	      colors[c_p2]=1;
	    }
	  break;

	case KEY_RIGHT:
	  //Map Type
	  if(cur_opt==0)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(cur_map==2) { cur_map=-1; }
	      cur_map+=1;
	      mvprintw(opt_y[0], 6+opt[0].length()+1, "                "); 
	      mvprintw(opt_y[0], 6+opt[0].length()+1, map_type_loc( (enum map_type) cur_map).c_str()); 
	      
	      //Map Desc
	      desc = get_map_desc( (enum map_type) cur_map);
	      for(k=0; k < (int) desc.size(); k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		  mvprintw(2+k, SCR_W-34, desc[k].c_str());
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Player Type P1
	  else if(cur_opt==1)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(h_p1) { h_p1=false; mvprintw(opt_y[1], 6+14, "CPU  "); } 
	      else {  h_p1=true; mvprintw(opt_y[1], 6+14, "Human"); }
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Civ P1
	  else if(cur_opt==2)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(civ_p1==civs.size()-1) { civ_p1=-1; }
	      civ_p1+=1;
	      mvprintw(opt_y[2], 6+14, "                "); 
	      mvprintw(opt_y[2], 6+14, civs[civ_p1]->get_name().c_str()); 
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg

	      //Civilization Info Box
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-36, '|'); }
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-1, '|'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(9, i, '_'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(19, i, '_'); }
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      for(k=8; k < 17; k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		}

	      //Checks if not random
	      if(civ_p1!=civ_random)
		{
		  mvprintw(10, SCR_W-34, "%s", civs[civ_p1]->get_name().c_str());
		  mvprintw(11, SCR_W-34, "Unique Unit: %s", get_unit_loc( (enum unit_type) civs[civ_p1]->unique()  ).c_str());
		  mvprintw(12, SCR_W-34, "Civ Bonuses:");
		  //Bonuses
		  for(k=0; k < (int) civs[civ_p1]->bonus_1()->size(); k++)
		    {
		      mvprintw(13+k, SCR_W-34, " * %s", civs[civ_p1]->bonus_1()->at(k)->desc().c_str());
		    }
		  for(k=0; k < (int) civs[civ_p1]->bonus_2()->size(); k++)
		    {
		      mvprintw(13+civs[civ_p1]->bonus_1()->size()+k, SCR_W-34, " * %s", civs[civ_p1]->bonus_2()->at(k)->desc().c_str());
		    }
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Color P1
	  else if(cur_opt==3)
	    {
	      colors[c_p1]=0;
	      if(c_p1==11) { c_p1 = -1; }
	      if(colors[c_p1+1]==0) { c_p1+=1; } 
	      else { if(c_p1!=10) { c_p1+=2; } else { c_p1=0; }  }
	      attroff(COLOR_PAIR(255));
	      attron(COLOR_PAIR(230+c_p1));
	      mvaddch(opt_y[3], 6 + 14, ' ');
	      attron(COLOR_PAIR(255));
	      colors[c_p1]=1;
	    }
	  //Player Type P2
	  else if(cur_opt==4)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(h_p2) { h_p2=false; mvprintw(opt_y[4], 6+14, "CPU  "); } 
	      else {  h_p2=true; mvprintw(opt_y[4], 6+14, "Human"); }
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Civ P2
	  else if(cur_opt==5)
	    {
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      if(civ_p2==civs.size()-1) { civ_p2=-1; }
	      civ_p2+=1;
	      mvprintw(opt_y[5], 6+14, "                "); 
	      mvprintw(opt_y[5], 6+14, civs[civ_p2]->get_name().c_str()); 
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg

	      //Civilization Info Box
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-36, '|'); }
	      for(i=9; i<20; i++) { mvaddch(i, SCR_W-1, '|'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(9, i, '_'); }
	      for(i=SCR_W-36; i<SCR_W; i++) { mvaddch(19, i, '_'); }
	      if(COLORS>8) { attron(COLOR_PAIR(254)); } //Dark Color bg
	      for(k=8; k < 17; k++)
		{
		  mvprintw(2+k, SCR_W-34, "                                ");
		}

	      //Checks if not random
	      if(civ_p2!=civ_random)
		{
		  mvprintw(10, SCR_W-34, "%s", civs[civ_p2]->get_name().c_str());
		  mvprintw(11, SCR_W-34, "Unique Unit: %s", get_unit_loc( (enum unit_type) civs[civ_p2]->unique()  ).c_str());
		  mvprintw(12, SCR_W-34, "Civ Bonuses:");
		  //Bonuses
		  for(k=0; k < (int) civs[civ_p2]->bonus_1()->size(); k++)
		    {
		      mvprintw(13+k, SCR_W-34, " * %s", civs[civ_p2]->bonus_1()->at(k)->desc().c_str());
		    }
		  for(k=0; k < (int) civs[civ_p2]->bonus_2()->size(); k++)
		    {
		      mvprintw(13+civs[civ_p2]->bonus_1()->size()+k, SCR_W-34, " * %s", civs[civ_p2]->bonus_2()->at(k)->desc().c_str());
		    }
		}
	      if(COLORS>8) { attron(COLOR_PAIR(255)); } //Light Color bg
	    }
	  //Color P2
	  else if(cur_opt==6)
	    {
	      colors[c_p2]=0;
	      if(c_p2==11) { c_p2 = -1; }
	      if(colors[c_p2+1]==0) { c_p2+=1; } 
	      else { if(c_p2!=10) { c_p2+=2; } else { c_p2=0; }  }
	      attron(COLOR_PAIR(230+c_p2));
	      mvaddch(opt_y[6], 6 + 14, ' ');
	      attron(COLOR_PAIR(255));
	      colors[c_p2]=1;
	    }
	  break;

	case ' ':
	  //Start
	  if(cur_opt==7) { exit=true; start=true;}
	  //Exit
	  else if(cur_opt==8) { exit=true; }
	  break;

	default:
	  break;
	}
    }

  //If menu was not exited, start was selected and game is started
  if(start) 
    {
      if(civ_p1==civ_random) { civ_p1 = rand()%civ_random; } 
      if(civ_p2==civ_random) { civ_p2 = rand()%civ_random; } 
      initialize_game(cur_map, h_p1, civs[civ_p1], c_p1, h_p2, civs[civ_p2], c_p2); 
    }
}
