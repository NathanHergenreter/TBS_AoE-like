#ifndef TILE_H

#define TILE_H

#include "entity.h"

/* Tiles
 *(0) - Default
 *(1) - Forest
 *(2) - Stone
 *(3) - Gold
 *(4) - Water
 *(5) - Shallow Water
 *(6) - Coast
 */
enum tile_type{ tile_default, tile_forest, tile_stone, tile_gold, tile_water, tile_water_shallow, tile_coast };


class tile {
  enum tile_type type;
  bool is_land;
  bool is_water;
  entity* ent;
 public:
  tile();
  tile(enum tile_type);
  ~tile();
  enum tile_type get_type() { return type; }
  void set_type(enum tile_type t) { type=t; }
  bool land() { return is_land; }
  void set_land(bool land) { is_land=land; }
  bool water() { return is_water; }
  void set_water(bool water) { is_water=water; }
  void tile_output(int, int, player*);
  entity * get_entity() { return ent; }
  void set_entity(entity *e) { ent=e; }

  void update_tile(enum tile_type);
  void update_tile_info(int, int);
  std::string get_loc();
};

#endif
