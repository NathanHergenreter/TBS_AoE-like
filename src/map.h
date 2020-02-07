#ifndef MAP_H

#define MAP_H

#include <vector>
#include <string>
#include <cmath>
#include "macros.h"
#include "tile.h"
#include "entity.h"
#include "player.h"

//Map Types
enum map_type { map_plains, map_rhine, map_caspian };

//Map Class
class map {
  //type - Map type
  //tiles 2D matrix of tiles for map
  enum map_type type;
  std::string desc;
  int start[2][2];
  std::vector<player*> players;
  std::vector< std::vector<tile*> > tiles;
  std::vector< std::vector<unit*> > units;
  std::vector< std::vector<building*> > buildings;

  //LoS Helper Functions
void sight_corner(entity *, std::vector< std::vector<bool> > *, int, int, int, int, int);
 void sight_flat(entity *, std::vector< std::vector<bool> > *, int, int, int, int, int);

  //Map Constructor Functions
  void bld_plains();
  void bld_rhine();
  void bld_caspian();

 public:
  map(enum map_type type);
  ~map();

  //Map
  tile* get_tile(int x, int y) { return tiles[y][x]; }
  unit* get_unit(int p, int i) { return units[p][i]; }

  //Player Entity Functions - Units
  void add_unit(int, unit *);
  void recruit_unit(int, unit *);
  void remove_unit(int, unit*);
  void remove_unit(int, int);
  bool has_units(int p) { return units[p].size() > 0; }
  int num_units(int p) { return (int) units[p].size(); }

  //Player Entity Functions - Buildings
  building* get_building(int p, int i) { return buildings[p][i]; }
  void add_building(int, building *);
  void remove_building(int, building *);
  void remove_building(int, int);
  bool has_buildings(int p) { return buildings[p].size() > 0; }
  int num_buildings(int p) { return (int) buildings[p].size(); }

  //Player Functions
  player * get_player(int p) { return players[p]; }
  void add_player(player *p) { players.push_back(p); }
  int get_player_count() { return (int) players.size(); }
  int get_start_x(int p) { return start[p][0]; }
  int get_start_y(int p) { return start[p][1]; }
  void output_map(int);
  void line_of_sight(entity*, std::vector< std::vector<bool> >*, int, bool);
  void update_building_queue(int);
  void apply_bonus(bonus *, int);
  void update_los(int);
  void update_los_entity(entity*, int);
};

std::string map_type_loc(enum map_type);
std::vector<std::string> get_map_desc(enum map_type);

#endif
