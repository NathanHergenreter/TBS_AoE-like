#ifndef ENTITY_H

#define ENTITY_H

#include <string>
#include <vector>
#include "macros.h"
#include "player.h"
#include "building_templates.h"
#include "unit_templates.h"

enum entity_type { entity_default, entity_building, entity_unit };

/*
 *(00) Default
 *(01) Castle
 *(02) House
 *(03) Farm
 *(04) Lumberyard
 *(05) Gold Mine
 *(06) Stone Mine
 *(07) Docks
 *(08) Market
 *(09) Barracks
 *(10) Range
 *(11) Stables
 *(12) Siege
 *(13) Wall
 *(14) Sentry Tower
 *(15) Tower
 *(16) Bombard Tower
 *(17) Blacksmith
 *(18) Academy
 */
enum building_type { bldg_default, bldg_castle, bldg_house, bldg_farm, bldg_lumberyard, bldg_gold, bldg_stone, bldg_dock, bldg_market, bldg_barracks, bldg_range, bldg_stables, bldg_siege, bldg_wall, bldg_gate, bldg_sentry_tower, bldg_tower, bldg_bombard_tower, bldg_blacksmith, bldg_academy };

/*
 *(0) Default
 *(1) Economic
 *(2) Military
 *(3) Defense
 *(4) Research
 */
enum building_class { bldg_class_default, bldg_class_economic, bldg_class_military, bldg_class_defense, bldg_class_research };

/*
 *(0) Default
 *(1) Builders
 *(2) Axemen -> (4) Halberdiers
 *(3) Spearmen -> (4) Halberdiers
 *(5) Swordsmen -> (6) Longswordsmen -> (7) Greatswordsmen
 *(8) Pikemen
 *(9) Javelinmen -> (10) Skirmishers
 *(11) Archers -> (12) Longbowmen
 *(13) Crossbowmen
 *(14) Handgunners -> (14) Musketeers
 *(16) Light Horsemen -> (17) Reiters
 *(18) Horse Archers
 *(19) Cavaliers -> (20) Knights -> Demi-Lancers (21)
 *(22) Ram
 *(23) Siege Tower
 *(24) Ballista
 *(25) Catapult -> (26) Trebuchet
 *(27) Mortar
 *(28) Bombard -> (29) Culverin
 *(30) Transport
 *(31) Galley -> (32) Galleass
 *(33) Carrack -> (34) Galleon
 *
 ***UNIQUES***
 *(+1) Afghan Ghilman
 *(+2) Arab Fursan
 *(+3) Aztec Cuauhtli
 *(+4) Burmese Sain
 *(+5) Chinese Nu Shou
 *(+6) Cuman Attar
 *(+7) English Yeoman Archers
 *(+8) Ethiopian Shotelai
 *(+9) French Gendarmes
 *(+10) Gaelic Gall Oglaigh
 *(+11) German Landsknechte
 *(+12) Incan Awqaq Macana
 *(+13) Indian Gaj
 *(+14) Iroquoian Tomahawk Ayawisgi
 *(+15) Italian Galea Bastarda
 *(+16) Japanese Samurai
 *(+17) Khmer Damri
 *(+18) Korean Geobukseon
 *(+19) Malay Lancaran
 *(+20) Mali Horon
 *(+21) Mayan Macahuitl
 *(+22) Mongol Mangudai
 *(+23) Moorish Jinetes
 *(+24) Muiscan Guecha
 *(+25) Norse Skeid
 *(+26) Persian Qizilbash
 *(+27) Polish Husarz
 *(+28) Portuguese Nau
 *(+29) Roman Kataphraktoi
 *(+30) Russian Boyare
 *(+31) Spanish Arcabuceros
 *(+32) Turkish Yeniceri
 *(+33) Vietnamese Sung Hoa Mai
 */
enum unit_type { unit_default, unit_builders, unit_axemen, unit_spearmen, unit_halberdiers, unit_swordsmen, unit_longswordsmen, unit_greatswordsmen, unit_pikemen, unit_javelinmen, unit_skirmishers, unit_archers, unit_longbowmen, unit_crossbowmen, unit_handgunners, unit_musketeers, unit_light_horsemen, unit_reiters, unit_horse_archers, unit_cavaliers, unit_knights, unit_demi_lancers, unit_ram, unit_siege_tower, unit_ballista, unit_catapult, unit_trebuchet, unit_mortar, unit_bombard, unit_culverin, unit_transport, unit_galley, unit_galleass, unit_carrack, unit_galleon, unit_ghilman, unit_fursan, unit_cuauhtli, unit_sain, unit_nu_shou, unit_attar, unit_yeoman_archers, unit_shotelai, unit_gendarmes, unit_gall_oglaigh, unit_landsknechte, unit_awqaq_macana, unit_gaj, unit_tomahawk_ayawisgi, unit_galea_bastarda, unit_samurai, unit_damri, unit_geobukseon, unit_lancaran, unit_horon, unit_macahuitl, unit_mangudai, unit_jinetes, unit_guecha, unit_skeid, unit_qizilbash, unit_husarz, unit_nau, unit_kataphraktoi, unit_boyare, unit_arcabuceros, unit_yeniceri, unit_sung_hoa_mai };

/*
 *(0) Default
 *(1) Melee
 *(2) Polearm
 *(3) Missile
 *(4) Mounted
 *(5) Siege
 *(6) Ship
 *(7) Unique
 *(8) Skirmisher
 *(9) Gunpowder
 */
enum unit_class { unit_class_default, unit_class_infantry, unit_class_melee, unit_class_missile, unit_class_mounted, unit_class_siege, unit_class_ship, unit_class_unique, unit_class_polearm, unit_class_skirmisher, unit_class_gunpowder };

/********** Entity Superclass ***********/
class entity
{
  enum entity_type ent_type;
  std::string name;
  char symbol;
  player *owner;
  bool action;
  int coords[2];
  int pop;
  int age;
  int prereq;
  int cur_hp;
  int max_hp;
  int hp_bonus;
  int armor;
  int armor_bonus;
  int range;
  int range_bonus;
  int accuracy;
  int accuracy_bonus;
  int mem_sight;
  int mem_sight_bon;
  bool can_garrison;
  std::vector<entity*> garrison;
  int max_garrison;
  int deploy_dist;

 public:
  entity();
  entity(building_template*, int, int);
  entity(unit_template*, int, int);
  ~entity();

  //Definitions
  enum entity_type get_entity_type() { return ent_type; }
  std::string get_name() { return name; }
  char get_symbol() { return symbol; }
  player * get_owner() { return owner; }
  void set_owner(player *p) { owner=p; }

  //Action State
  bool has_action() { return action; }
  void set_action(bool f) { action=f; }

  //Coords
  int x() { return coords[0]; }
  int y() { return coords[1]; }
  void set_coords(int x, int y) { coords[0]=x; coords[1]=y; }

  //Pop
  int get_pop() { return pop; }
  int get_age() { return age; }
  int get_prereq() { return prereq; }

  //HP
  int get_hp() { return cur_hp; }
  void mod_hp(int mod) { cur_hp+=mod; }
  int get_max_hp() { return max_hp; }
  int get_hp_bonus() { return hp_bonus; }
  void mod_hp_bonus(int mod) { hp_bonus+=mod; }

  //Armor
  int get_armor() { return armor; }
  int get_armor_bonus() { return armor_bonus; }
  void mod_armor_bonus(int mod) { armor_bonus+=mod; }

  //Range
  int get_range() { return range; }
  int get_range_bonus() { return range; }
  void mod_range_bonus(int mod) { range+=mod; }

  //Accuracy
  int get_accuracy() { return accuracy; }
  int get_accuracy_bonus() { return accuracy_bonus; }
  void mod_accuracy_bonus(int mod) { accuracy_bonus+=mod; }

  //Sight
  int sight() { return mem_sight; }
  int sight_bonus() { return mem_sight_bon; }
  void mod_sight_bonus(int mod) { mem_sight_bon+=mod; }

  //Garrison
  bool garrisonable() { return can_garrison && ((int)garrison.size()<max_garrison); }
  entity * get_garrison(int i) { return garrison[i]; }
  void add_garrison(entity *ent) { garrison.push_back(ent); }
  entity * remove_garrison(int i) { entity *temp=garrison[i]; garrison.erase(garrison.begin()+i); return temp; }
  int get_max_garrison() { return max_garrison; }
  int get_garrison_size() { return garrison.size(); }
  int get_deploy() { return deploy_dist; }
};

/************ Building Class **********/
class building : public entity
{
  enum building_type type;
  enum building_class b_class;
  int terrain_type;
  bool mem_passable;
  int out_gold;
  int out_gold_bonus;
  int out_food;
  int out_food_bonus;
  int out_wood;
  int out_wood_bonus;
  int out_stone;
  int out_stone_bonus;
  int attack;
  int attack_bonus;
  int attack_pierce;
  int mem_ap_bon;
  int recruit_class;
  int recruit_time;
  int recruit;
  std::vector<int> tech_pool;
  int research_time;
  int research;

 public:
  building();
  building(building_template*, int, int);
  ~building();

  //Definitions
  enum building_type get_type() { return type; }
  enum building_class get_class() { return b_class; }
  int get_terrain() { return terrain_type; }
  bool passable() { return mem_passable; }

  //Resources
  int get_gold() { return out_gold; }
  int get_gold_bonus() { return out_gold_bonus; }
  void mod_gold_bonus(int mod) { out_gold_bonus+=mod; }
  int get_food() { return out_food; }
  int get_food_bonus() { return out_food_bonus; }
  void mod_food_bonus(int mod) { out_food_bonus+=mod; }
  int get_wood() { return out_wood; }
  int get_wood_bonus() { return out_wood_bonus; }
  void mod_wood_bonus(int mod) { out_wood_bonus+=mod; }
  int get_stone() { return out_stone; }
  int get_stone_bonus() { return out_stone_bonus; }
  void mod_stone_bonus(int mod) { out_stone_bonus+=mod; }

  //Attack
  int get_attack() { return attack; }
  int get_attack_bonus() { return attack_bonus; }
  void mod_attack_bonus(int mod) { attack_bonus+=mod; }
  int get_attack_ap() { return attack_pierce; }
  int ap_bonus() { return mem_ap_bon; }
  void mod_ap_bonus(int mod) { mem_ap_bon+=mod; }

  //Recruiting
  int get_recruit_class() { return recruit_class; }
  bool can_recruit() { return recruit_class!=unit_class_default; }
  bool recruiting() { return recruit_time>0; }
  int rem_recruit_time() { return recruit_time; }
  void mod_recruit_time(int mod) { recruit_time+=mod; }
  int get_recruit() { return recruit; }
  void set_recruit(int rec) { recruit=rec; }

  //Researching
  int num_techs() { return tech_pool.size(); }
  int get_tech(int idx) { return tech_pool[idx]; }
  bool can_research() { return tech_pool.size()>0; }
  bool researching() { return research_time>0; }
  int rem_research_time() { return research_time; }
  void mod_research_time(int mod) { research_time+=mod; }
  int get_research() { return research; }
  void set_research(int res) { research=res; }
};

/************ Unit Class **********/
class unit : public entity
{
  enum unit_type type;
  enum unit_class u_class;
  int subclasses[NUM_UNIT_CLASSES];
  bool is_upgradable;
  enum unit_type upgrade;
  bool is_land;
  bool is_naval;
  bool is_indirect;
  int building_attack;
  int building_attack_bonus;
  int melee_attack;
  int melee_bonus;
  int melee_pierce;
  int melee_pierce_bonus;
  int ranged_attack;
  int ranged_bonus;
  int ranged_pierce;
  int ranged_pierce_bonus;
  int cur_move;
  int max_move;
  int move_bonus;

 public:
  unit();
  unit(unit_template*, int, int);
  ~unit();

  //Definition
  enum unit_type get_type() { return type; }
  enum unit_class get_class() { return u_class; }
  int has_subclass(enum unit_class c) { return this->subclasses[c]; }
  void set_class(enum unit_class c, int val) { this->subclasses[c]=val; }

  //Upgrade
  bool upgradable() { return is_upgradable; }
  enum unit_type get_upgrade() { return upgrade; }

  //Traits
  bool land() { return is_land; }
  bool naval() { return is_naval; }
  bool indirect() { return is_indirect; }

  //Building Attack
  int get_building_attack() { return building_attack; }
  int get_building_attack_bonus() { return building_attack_bonus; }
  void mod_building_attack_bonus(int mod) { building_attack_bonus+=mod; }

  //Melee Attack
  int get_melee() { return melee_attack; }
  int get_melee_bonus() { return melee_bonus; }
  void mod_melee_bonus(int mod) { melee_bonus+=mod; }
  int get_melee_ap() { return melee_pierce; }
  int get_melee_ap_bonus() { return melee_pierce_bonus; }
  void mod_melee_ap_bonus(int mod) { melee_pierce_bonus+=mod; }

  //Ranged Attack
  int get_ranged() { return ranged_attack; }
  int get_ranged_bonus() { return ranged_bonus; }
  void mod_ranged_bonus(int mod) { ranged_bonus+=mod; }
  int get_ranged_ap() { return ranged_pierce; }
  int get_ranged_ap_bonus() { return ranged_pierce_bonus; }
  void mod_ranged_ap_bonus(int mod) { ranged_pierce_bonus+=mod; }

  //Movement
  int get_cur_move() { return cur_move; }
  void mod_cur_move(int mod) { cur_move+=mod; }
  void reset_move() { cur_move=max_move+move_bonus; }
  int get_max_move() { return max_move; }
  int get_move_bonus() { return move_bonus; }
  void mod_move_bonus(int mod) { move_bonus+=mod; }
};

std::string get_bclass_loc(enum building_class);
std::string get_uclass_loc(enum unit_class);
std::string get_unit_loc(enum unit_type);
std::string get_bldg_loc(enum building_type);

#endif
