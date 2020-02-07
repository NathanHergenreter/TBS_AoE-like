#ifndef TECHNOLOGY_H

#define TECHNOLOGY_H

#include <string>
#include <vector>
#include "bonus.h"

#define NUM_CORE_TECHS 60

/*
 *(0) Default
 *(1) - (13) Unit upgrades
 *(15) - Gunpowder
 *(16) High Middle Ages
 *(17) Late Middle Ages
 *(18) Wheelbarrow
 *(19) Loom
 *(20) Keeps
 *(21) Bastions
 *(22) Cannon Bulwarks
 *(23) Taxation
 *(24) Masonry
 *(25) Architecture
 *(26) Ballistics
 *(27) Arrowslits
 *(28) Siege Engineers
 *(29) Horse Collar
 *(30) Heavy Plow
 *(31) Crop Rotation
 *(32) Double-Bit Axe
 *(33) Bow Saw
 *(34) Two-Man Saw
 *(35) Gold Mining
 *(36) Gold Shaft Mining
 *(37) Stone Mining
 *(38) Stone Shaft Mining
 *(39) Coinage
 *(40) Banking
 *(41) Gillnets
 *(42) Careening
 *(43) Shipwright
 *(44) Forging
 *(45) Iron Casting
 *(46) Blast Furnace
 *(47) Fletching
 *(48) Bodkin Arrow
 *(49) Bracer
 *(50) Scale Armor
 *(51) Chainmail Armor
 *(52) Plate Armor
 *(53) Scale Barding
 *(54) Chainmail Barding
 *(55) Plate Barding
 *(56) Tracking
 *(57) Arson
 *(58) Thumb Ring
 *(59) Bloodlines
 */
enum technology { tech_default, tech_halberdiers, tech_longswordsmen, tech_greatswordsmen, tech_skirmishers, tech_longbowmen, tech_musketeers, tech_reiters, tech_knights, tech_demi_lancers, tech_trebuchet, tech_culverin, tech_galleass, tech_galleon, tech_gunpowder, tech_age1, tech_age2, tech_wheelbarrow, tech_loom, tech_keeps, tech_bastions, tech_bulwarks, tech_taxation, tech_masonry, tech_architecture, tech_ballistics, tech_arrowslits, tech_siege_engineers, tech_horse_collar, tech_heavy_plow, tech_crop_rotation, tech_double_bit_axe, tech_bow_saw, tech_two_man_saw, tech_gold_mining, tech_gold_shaft_mining, tech_stone_mining, tech_stone_shaft_mining, tech_coinage, tech_banking, tech_gillnets, tech_careening, tech_shipwright, tech_forging, tech_iron_casting, tech_blast_furnace, tech_fletching, tech_bodkin_arrow, tech_bracer, tech_scale_armor, tech_chainmail_armor, tech_plate_armor, tech_scale_barding, tech_chainmail_barding, tech_plate_barding, tech_tracking, tech_arson, tech_thumb_ring, tech_bloodlines };

class tech
{
  //Definitions
  std::string mem_name;
  enum technology mem_technology;

  //Prerequisites
  int mem_time;
  int mem_gold;
  int mem_food;
  int mem_wood;
  int mem_stone;
  int mem_age;
  enum technology mem_prereq;

  //Bonus
  std::vector<bonus *> mem_bonus;

 public:
  tech();
  tech(enum technology);
  ~tech();
  std::string name() { return mem_name; }
  enum technology technology() { return mem_technology; }
  int time() { return mem_time; }
  int gold() { return mem_gold; }
  int food() { return mem_food; }
  int wood() { return mem_wood; }
  int stone()  {return mem_stone; }
  int age() { return mem_age; }
  enum technology prereq() { return mem_prereq; }
  std::vector<bonus *> * get_bonus() { return &mem_bonus; }

};

std::vector<tech*> get_technologies();

#endif
