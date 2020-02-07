/********* CONTENTS **********/
//(A) Constructor

//(B) Factory Vector

/********* CONTENTS **********/

#include "macros.h"
#include "building_templates.h"
#include "technology.h"

//Local Dupes
enum building_type_dupe { bldg_default, bldg_castle, bldg_house, bldg_farm, bldg_lumberyard, bldg_gold, bldg_stone, bldg_dock, bldg_market, bldg_barracks, bldg_range, bldg_stables, bldg_siege, bldg_wall, bldg_gate, bldg_sentry_tower, bldg_tower, bldg_bombard_tower, bldg_blacksmith, bldg_academy };

enum building_class_dupe { bldg_class_default, bldg_class_economic, bldg_class_military, bldg_class_defense, bldg_class_research };

enum unit_class_dupe { unit_class_default, unit_class_infantry, unit_class_melee, unit_class_polearm, unit_class_missile, unit_class_mounted, unit_class_siege, unit_class_ship, unit_class_unique };

enum tile_type_dupe{ tile_default, tile_forest, tile_stone, tile_gold, tile_water, tile_water_shallow, tile_coast };


//(A) Constuctor - Specific
building_template :: building_template(int type)
{
  this->type=type;

  //Default Fall Back Initialization
  name="ERROR";
  symbol='?';
  init_gold=0;
  init_food=0;
  init_wood=0;
  init_stone=0;
  b_class=bldg_class_default;
  pop=0;
  age=0;
  prereq=tech_default;
  max_hp=1;
  hp_bonus=0;
  armor=0;
  armor_bonus=0;
  can_garrison=false;
  max_garrison=0;
  deploy_dist=1;
  terrain_type=tile_default;
  passable=false;
  out_gold=0;
  out_gold_bonus=0;
  out_food=0;
  out_food_bonus=0;
  out_wood=0;
  out_wood_bonus=0;
  out_stone=0;
  out_stone_bonus=0;
  attack=0;
  range=0;
  attack_bonus=0;
  range_bonus=0;
  attack_pierce=0;
  attack_pierce_bonus=0;
  accuracy=0;
  accuracy_bonus=0;
  sight=0;
  sight_bonus=0;
  recruit_class=unit_class_default;

  //Unique for each building type
  switch(type)
    {
      //Castle
    case bldg_castle:
      name="Castle";
      symbol='#';
      init_stone=500;
      b_class=bldg_class_military;
      pop=5;
      max_hp=1200;
      armor=5;
      can_garrison=true;
      max_garrison=10;
      attack=30;
      attack_pierce=2;
      range=5;
      accuracy=75;
      sight=6;
      recruit_class=unit_class_unique;
      tech_pool.push_back(tech_age1);
      tech_pool.push_back(tech_age2);
      tech_pool.push_back(tech_wheelbarrow);
      tech_pool.push_back(tech_loom);
      tech_pool.push_back(tech_keeps);
      tech_pool.push_back(tech_bastions);
      tech_pool.push_back(tech_bulwarks);
      tech_pool.push_back(tech_taxation);
      break;

      //House
    case bldg_house:
      name="House";
      symbol='^';
      init_wood=35;
      b_class=bldg_class_economic;
      pop=5;
      max_hp=100;
      armor=1;
      sight=5;
      break;

      //Farm
    case bldg_farm:
      name="Farm";
      symbol='@';
      init_wood=80;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=100;
      sight=5;
      out_food=15;
      tech_pool.push_back(tech_horse_collar);
      tech_pool.push_back(tech_heavy_plow);
      tech_pool.push_back(tech_crop_rotation);
      break;

      //Lumberyard
    case bldg_lumberyard:
      name="Lumberyard";
      symbol='<';
      init_food=80;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=100;
      sight=5;
      terrain_type=tile_forest;
      out_wood=1;
      tech_pool.push_back(tech_double_bit_axe);
      tech_pool.push_back(tech_bow_saw);
      tech_pool.push_back(tech_two_man_saw);
      break;

      //Gold Mine
    case bldg_gold:
      name="Gold Mine";
      symbol='}';
      init_wood=80;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=100;
      sight=5;
      terrain_type=tile_gold;
      out_gold=15;
      tech_pool.push_back(tech_gold_mining);
      tech_pool.push_back(tech_gold_shaft_mining);
      break;

      //Stone Mine
    case bldg_stone:
      name="Stone Mine";
      symbol='{';
      init_wood=80;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=100;
      sight=5;
      terrain_type=tile_stone;
      out_stone=15;
      tech_pool.push_back(tech_stone_mining);
      tech_pool.push_back(tech_stone_shaft_mining);
      break;

      //Docks
    case bldg_dock:
      name="Docks";
      symbol='&';
      init_wood=180;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=200;
      sight=5;
      can_garrison=true;
      max_garrison=5;
      terrain_type=6;
      out_gold=10;
      out_food=10;
      recruit_class=unit_class_ship;
      tech_pool.push_back(tech_galleass);
      tech_pool.push_back(tech_galleon);
      tech_pool.push_back(tech_gillnets);
      tech_pool.push_back(tech_careening);
      tech_pool.push_back(tech_shipwright);
      break;

      //Market
    case bldg_market:
      name="Market";
      symbol='$';
      init_gold=50;
      init_food=50;
      init_wood=150;
      b_class=bldg_class_economic;
      pop=-1;
      max_hp=100;
      sight=5;
      out_gold=10;
      tech_pool.push_back(tech_coinage);
      tech_pool.push_back(tech_banking);
      break;

      //Barracks
    case bldg_barracks:
      name="Barracks";
      symbol='/';
      init_food=50;
      init_wood=150;
      b_class=bldg_class_military;
      max_hp=250;
      armor=1;
      sight=5;
      can_garrison=true;
      max_garrison=5;
      recruit_class=unit_class_melee;
      tech_pool.push_back(tech_halberdiers);
      tech_pool.push_back(tech_longswordsmen);
      tech_pool.push_back(tech_greatswordsmen);
      tech_pool.push_back(tech_tracking);
      tech_pool.push_back(tech_arson);
      break;

      //Range
    case bldg_range:
      name="Range";
      symbol=')';
      init_wood=200;
      b_class=bldg_class_military;
      max_hp=250;
      armor=1;
      sight=5;
      can_garrison=true;
      max_garrison=5;
      recruit_class=unit_class_missile;
      tech_pool.push_back(tech_skirmishers);
      tech_pool.push_back(tech_longbowmen);
      tech_pool.push_back(tech_musketeers);
      tech_pool.push_back(tech_thumb_ring);
      break;

      //Stables
    case bldg_stables:
      name="Stables";
      symbol=']';
      init_gold=50;
      init_food=180;
      b_class=bldg_class_military;
      max_hp=250;
      armor=1;
      sight=5;
      can_garrison=true;
      max_garrison=5;
      recruit_class=unit_class_mounted;
      tech_pool.push_back(tech_knights);
      tech_pool.push_back(tech_reiters);
      tech_pool.push_back(tech_demi_lancers);
      tech_pool.push_back(tech_bloodlines);
      break;

      //Siege
    case bldg_siege:
      name="Siegeworks";
      symbol='%';
      init_wood=250;
      b_class=bldg_class_military;
      max_hp=200;
      armor=1;
      sight=5;
      can_garrison=true;
      max_garrison=5;
      recruit_class=unit_class_siege;
      tech_pool.push_back(tech_trebuchet);
      tech_pool.push_back(tech_culverin);
      break;

      //Wall
    case bldg_wall:
      name="Wall";
      symbol='+';
      init_stone=50;
      b_class=bldg_class_defense;
      max_hp=600;
      armor=5;
      sight=6;
      break;

      //Gate
    case bldg_gate:
      name="Gate";
      symbol='=';
      passable=true;
      init_stone=80;
      b_class=bldg_class_defense;
      max_hp=750;
      armor=5;
      sight=6;
      break;

      //Sentry Tower
    case bldg_sentry_tower:
      name="Sentry Tower";
      symbol='1';
      init_wood=40;
      b_class=bldg_class_defense;
      max_hp=500;
      armor=2;
      sight=10;
      break;

      //Tower
    case bldg_tower:
      name="Tower";
      symbol='|';
      init_wood=30;
      init_stone=100;
      b_class=bldg_class_defense;
      max_hp=2000;
      armor=4;
      can_garrison=true;
      max_garrison=1;
      attack=15;
      range=4;
      attack_pierce=1;
      accuracy=75;
      sight=6;
      break;

      //Bombard Tower
    case bldg_bombard_tower:
      name="Bombard Tower";
      symbol='!';
      init_gold=50;
      init_stone=100;
      b_class=bldg_class_defense;
      max_hp=2000;
      prereq=tech_gunpowder;
      armor=4;
      can_garrison=true;
      max_garrison=1;
      attack=35;
      range=6;
      attack_pierce=5;
      accuracy=50;
      sight=6;
      break;

      //Blacksmith
    case bldg_blacksmith:
      name="Blacksmith";
      symbol='8';
      init_gold=60;
      init_wood=120;
      b_class=bldg_class_research;
      max_hp=600;
      armor=1;
      sight=5;
      tech_pool.push_back(tech_forging);
      tech_pool.push_back(tech_iron_casting);
      tech_pool.push_back(tech_blast_furnace);
      tech_pool.push_back(tech_fletching);
      tech_pool.push_back(tech_bodkin_arrow);
      tech_pool.push_back(tech_bracer);
      tech_pool.push_back(tech_scale_armor);
      tech_pool.push_back(tech_chainmail_armor);
      tech_pool.push_back(tech_plate_armor);
      tech_pool.push_back(tech_scale_barding);
      tech_pool.push_back(tech_chainmail_armor);
      tech_pool.push_back(tech_plate_armor);
      break;

      //Academy
    case bldg_academy:
      name="Academy";
      symbol='~';
      init_gold=120;
      init_wood=160;
      b_class=bldg_class_research;
      age=1;
      max_hp=600;
      armor=1;
      sight=5;
      tech_pool.push_back(tech_masonry);
      tech_pool.push_back(tech_architecture);
      tech_pool.push_back(tech_ballistics);
      tech_pool.push_back(tech_arrowslits);
      tech_pool.push_back(tech_siege_engineers);
      tech_pool.push_back(tech_gunpowder);
      break;

      //Shouldn't happen
    default:
      break;
    }
}

//(B) Factory Vector
std::vector<building_template*> get_building_templates()
{
  std::vector<building_template*> ret;

  int i;
  for(i=0; i<NUM_BUILDINGS; i++)
    {
      ret.push_back( new building_template( (enum building_type_dupe) i) );
    }

  return ret;
}
