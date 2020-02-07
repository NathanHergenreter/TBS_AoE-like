#include "technology.h"
#include "entity.h"

/********* CONTENTS **********/

//(A) Technology Constructor

/********* CONTENTS **********/

tech :: tech(enum technology technology) 
{
  //Default
  this->mem_name = "ERROR";
  this->mem_technology = tech_default;
  this->mem_time=1;
  this->mem_gold=0;
  this->mem_food=0;
  this->mem_wood=0;
  this->mem_stone=0;
  this->mem_age=0;
  this->mem_prereq = tech_default;

  switch(technology)
    {
      //Unit Upgrade Unlocks
    case tech_halberdiers:
      this->mem_name = "Halberdiers";
      this->mem_technology = tech_halberdiers;
      this->mem_time=3;
      this->mem_food=200;
      this->mem_age=2;
      break;
    case tech_longswordsmen:
      this->mem_name = "Longswordsmen";
      this->mem_technology = tech_longswordsmen;
      this->mem_time=2;
      this->mem_gold=180;
      this->mem_food=220;
      this->mem_age=1;
      break;
    case tech_greatswordsmen:
      this->mem_name = "Greatswordsmen";
      this->mem_technology = tech_greatswordsmen;
      this->mem_time=3;
      this->mem_gold=300;
      this->mem_food=350;
      this->mem_age=2;
      this->mem_prereq=tech_longswordsmen;
      break;
    case tech_skirmishers:
      this->mem_name = "Skirmishers";
      this->mem_technology = tech_skirmishers;
      this->mem_time=2;
      this->mem_food=150;
      this->mem_wood=150;
      this->mem_age=1;
      break;
    case tech_longbowmen:
      this->mem_name = "Longbownmen";
      this->mem_technology = tech_longbowmen;
      this->mem_time=2;
      this->mem_gold=200;
      this->mem_wood=200;
      this->mem_age=1;
      break;
    case tech_musketeers:
      this->mem_name = "Musketeers";
      this->mem_technology = tech_musketeers;
      this->mem_time=4;
      this->mem_gold=300;
      this->mem_food=300;
      this->mem_prereq=tech_gunpowder;
      break;
    case tech_reiters:
      this->mem_name = "Reiters";
      this->mem_technology = tech_reiters;
      this->mem_time=3;
      this->mem_food=300;
      this->mem_prereq=tech_gunpowder;
      break;
    case tech_knights:
      this->mem_name = "Knights";
      this->mem_technology = tech_knights;
      this->mem_gold=400;
      this->mem_food=350;
      this->mem_age=1;
      break;
    case tech_demi_lancers:
      this->mem_name = "Demi-Lancers";
      this->mem_technology = tech_demi_lancers;
      this->mem_gold=600;
      this->mem_food=475;
      this->mem_prereq=tech_gunpowder;
      break;
    case tech_trebuchet:
      this->mem_name = "Trebuchet";
      this->mem_technology = tech_trebuchet;
      this->mem_time=2;
      this->mem_gold=200;
      this->mem_wood=300;
      this->mem_stone=250;
      this->mem_age=1;
      break;
    case tech_culverin:
      this->mem_name = "Culverin";
      this->mem_technology = tech_culverin;
      this->mem_time=4;
      this->mem_gold=600;
      this->mem_prereq=tech_gunpowder;
      break;
    case tech_galleass:
      this->mem_name = "Galleass";
      this->mem_technology = tech_galleass;
      this->mem_time=3;
      this->mem_gold=300;
      this->mem_wood=400;
      this->mem_prereq=tech_gunpowder;
      break;
    case tech_galleon:
      this->mem_name = "Galleon";
      this->mem_technology = tech_galleon;
      this->mem_time=4;
      this->mem_gold=500;
      this->mem_wood=600;
      this->mem_prereq=tech_gunpowder;
      break;
      //Gunpowder
    case tech_gunpowder:
      this->mem_name = "Gunpowder";
      this->mem_technology = tech_gunpowder;
      this->mem_time=3;
      this->mem_gold = 500;
      this->mem_age=2;
      break;
      //Age Up 1
    case tech_age1:
      this->mem_name = "High M. Ages";
      this->mem_technology = tech_age1;
      this->mem_time=6;
      this->mem_gold = 200;
      this->mem_food = 300;
      this->mem_wood = 200;
      this->mem_stone = 200;
      this->mem_bonus.push_back(new bonus(bonus_age, 0, 0, 0, mod_default));
      break;
      //Age Up 2
    case tech_age2:
      this->mem_name = "Late M. Ages";
      this->mem_technology = tech_age2;
      this->mem_time=8;
      this->mem_gold = 500;
      this->mem_food = 350;
      this->mem_wood = 200;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_age, 0, 0, 0, mod_default));
      break;
      //Wheelbarrow
    case tech_wheelbarrow:
      this->mem_name = "Wheelbarrow";
      this->mem_technology = tech_wheelbarrow;
      this->mem_time=2;
      this->mem_food = 120;
      this->mem_wood = 80;
      this->mem_bonus.push_back(new bonus(bonus_unit, unit_bonus_move, unit_builders, 1, mod_additive));
      break;
      //Loom
    case tech_loom:
      this->mem_name = "Loom";
      this->mem_technology = tech_loom;
      this->mem_time=2;
      this->mem_food = 100;
      this->mem_bonus.push_back(new bonus(bonus_unit, unit_bonus_hp, unit_builders, 20, mod_additive));
      break;
      //Keeps
    case tech_keeps:
      this->mem_name = "Keeps";
      this->mem_technology = tech_keeps;
      this->mem_time=4;
      this->mem_gold = 200;
      this->mem_stone = 350;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_hp, bldg_castle, 400, mod_additive));
      break;
      //Bastions
    case tech_bastions:
      this->mem_name = "Bastions";
      this->mem_technology = tech_bastions;
      this->mem_time=4;
      this->mem_gold = 300;
      this->mem_stone = 400;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_armor, bldg_castle, 2, mod_additive));
      break;
      //Cannon Bulwarks
    case tech_bulwarks:
      this->mem_name = "Cannon Bulwarks";
      this->mem_technology = tech_bulwarks;
      this->mem_time=5;
      this->mem_gold = 300;
      this->mem_stone = 400;
      this->mem_prereq=tech_gunpowder;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_attack, bldg_castle, 20, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_ap, bldg_castle, 3, mod_additive));
      break;
      //Taxation
    case tech_taxation:
      this->mem_name = "Taxation";
      this->mem_technology = tech_taxation;
      this->mem_time=3;
      this->mem_gold = 200;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_house, 2, mod_additive));
      break;
      //Masonry
    case tech_masonry:
      this->mem_name = "Masonry";
      this->mem_technology = tech_masonry;
      this->mem_time=4;
      this->mem_wood = 150;
      this->mem_stone = 175;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_hp, bldg_house, 40, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_armor, bldg_house, 1, mod_additive));
      break;
      //Architecture
    case tech_architecture:
      this->mem_name = "Architecture";
      this->mem_technology = tech_architecture;
      this->mem_time=6;
      this->mem_wood = 200;
      this->mem_stone = 250;
      this->mem_age=1;
      this->mem_prereq=tech_masonry;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_hp, bldg_house, 40, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_armor, bldg_house, 1, mod_additive));
      break;
      //Ballistics
    case tech_ballistics:
      this->mem_name = "Ballistics";
      this->mem_technology = tech_ballistics;
      this->mem_time=5;
      this->mem_gold=150;
      this->mem_wood=300;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_accuracy, unit_class_missile, 10, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_accuracy, bldg_castle, 10, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_accuracy, bldg_tower, 10, mod_additive));
      break;
      //Arrowslits
    case tech_arrowslits:
      this->mem_name = "Arrowslits";
      this->mem_technology = tech_arrowslits;
      this->mem_time=6;
      this->mem_food=250;
      this->mem_wood=250;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_attack, bldg_tower, 12, mod_additive));
      break;
      //Siege Engineers
    case tech_siege_engineers:
      this->mem_name = "Siege Engineers";
      this->mem_technology = tech_siege_engineers;
      this->mem_time=4;
      this->mem_food=400;
      this->mem_wood=500;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_range, unit_class_siege, 1, mod_additive));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_building, unit_class_siege, 20, mod_multiplier));
      break;
      //Horse Collar
    case tech_horse_collar:
      this->mem_name = "Horse Collar";
      this->mem_technology = tech_horse_collar;
      this->mem_time=3;
      this->mem_food=75;
      this->mem_wood=75;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_farm, 2, mod_additive));
      break;
      //Heavy Plow
    case tech_heavy_plow:
      this->mem_name = "Heavy Plow";
      this->mem_technology = tech_heavy_plow;
      this->mem_time=4;
      this->mem_food=125;
      this->mem_wood=125;
      this->mem_prereq=tech_horse_collar;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_farm, 2, mod_additive));
      break;
      //Crop Rotation
    case tech_crop_rotation:
      this->mem_name = "Crop Rotation";
      this->mem_technology = tech_crop_rotation;
      this->mem_time=5;
      this->mem_food=250;
      this->mem_wood=250;
      this->mem_prereq=tech_heavy_plow;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_farm, 3, mod_additive));
      break;
      //Double-Bit Axe
    case tech_double_bit_axe:
      this->mem_name = "Double-Bit Axe";
      this->mem_technology = tech_double_bit_axe;
      this->mem_time=3;
      this->mem_food=100;
      this->mem_wood=50;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_wood, bldg_lumberyard, 2, mod_additive));
      break;
      //Bow Saw
    case tech_bow_saw:
      this->mem_name = "Bow Saw";
      this->mem_technology = tech_bow_saw;
      this->mem_time=4;
      this->mem_food=150;
      this->mem_wood=100;
      this->mem_prereq=tech_bow_saw;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_wood, bldg_lumberyard, 2, mod_additive));
      break;
      //Two-Man Saw
    case tech_two_man_saw:
      this->mem_name = "Two-Man Saw";
      this->mem_technology = tech_two_man_saw;
      this->mem_time=5;
      this->mem_food=300;
      this->mem_wood=200;
      this->mem_prereq=tech_bow_saw;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_wood, bldg_lumberyard, 3, mod_additive));
      break;
      //Gold Mining
    case tech_gold_mining:
      this->mem_name = "Gold Mining";
      this->mem_technology = tech_gold_mining;
      this->mem_time=3;
      this->mem_food=100;
      this->mem_wood=75;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_gold, 2, mod_additive));
      break;
      //Gold Shaft Mining
    case tech_gold_shaft_mining:
      this->mem_name = "Gold Shaft Mining";
      this->mem_technology = tech_gold_shaft_mining;
      this->mem_time=4;
      this->mem_food=200;
      this->mem_wood=150;
      this->mem_prereq=tech_gold_mining;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_gold, 2, mod_additive));
      break;
      //Stone Mining
    case tech_stone_mining:
      this->mem_name = "Stone Mining";
      this->mem_technology = tech_stone_mining;
      this->mem_time=3;
      this->mem_food=100;
      this->mem_wood=75;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_stone, bldg_stone, 2, mod_additive));
      break;
      //Stone Shaft Mining
    case tech_stone_shaft_mining:
      this->mem_name = "Stone Shaft Mining";
      this->mem_technology = tech_stone_shaft_mining;
      this->mem_time=4;
      this->mem_food=200;
      this->mem_wood=150;
      this->mem_prereq=tech_stone_mining;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_stone, bldg_stone, 2, mod_additive));
      break;
      //Coinage
    case tech_coinage:
      this->mem_name = "Coinage";
      this->mem_technology = tech_coinage;
      this->mem_time=5;
      this->mem_gold=250;
      this->mem_food=200;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_market, 2, mod_additive));
      break;
      //Banking
    case tech_banking:
      this->mem_name = "Banking";
      this->mem_technology = tech_banking;
      this->mem_time=6;
      this->mem_gold=350;
      this->mem_food=300;
      this->mem_prereq=tech_coinage;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_market, 2, mod_additive));
      break;
      //Gillnets
    case tech_gillnets:
      this->mem_name = "Gillnets";
      this->mem_technology = tech_gillnets;
      this->mem_time=4;
      this->mem_gold=200;
      this->mem_food=150;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_dock, 3, mod_additive));
      break;
      //Careening
    case tech_careening:
      this->mem_name = "Careening";
      this->mem_technology = tech_careening;
      this->mem_time=4;
      this->mem_gold=150;
      this->mem_food=250;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_ship, 1, mod_additive));
      break;
      //Shipwright
    case tech_shipwright:
      this->mem_name = "Shipwright";
      this->mem_technology = tech_shipwright;
      this->mem_time=6;
      this->mem_gold=300;
      this->mem_food=1000;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_wood, unit_class_ship, -20, mod_multiplier));
      break;
      //Forging
    case tech_forging:
      this->mem_name = "Forging";
      this->mem_technology = tech_forging;
      this->mem_time=4;
      this->mem_food=150;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_melee, 10, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee_ap, unit_class_melee, 1, mod_additive));
      break;
      //Iron Casting
    case tech_iron_casting:
      this->mem_name = "Iron Casting";
      this->mem_technology = tech_iron_casting;
      this->mem_time=5;
      this->mem_gold=120;
      this->mem_food=220;
      this->mem_prereq=tech_forging;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_melee, 10, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee_ap, unit_class_melee, 1, mod_additive));
      break;
      //Blast Furnace
    case tech_blast_furnace:
      this->mem_name = "Blast Furnace";
      this->mem_technology = tech_blast_furnace;
      this->mem_time=7;
      this->mem_gold=225;
      this->mem_food=275;
      this->mem_prereq=tech_iron_casting;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_melee, 20, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_melee_ap, unit_class_melee, 1, mod_additive));
      break;
      //Fletching
    case tech_fletching:
      this->mem_name = "Fletching";
      this->mem_technology = tech_fletching;
      this->mem_time=4;
      this->mem_gold=50;
      this->mem_food=100;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_missile, 10, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged_ap, unit_class_missile, 1, mod_additive));
      break;
      //Bodking Arrow
    case tech_bodkin_arrow:
      this->mem_name = "Bodkin Arrow";
      this->mem_technology = tech_bodkin_arrow;
      this->mem_time=5;
      this->mem_gold=100;
      this->mem_food=200;
      this->mem_prereq=tech_fletching;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_missile, 10, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged_ap, unit_class_missile, 1, mod_additive));
      break;
      //Bracer
    case tech_bracer:
      this->mem_name = "Bracer";
      this->mem_technology = tech_bracer;
      this->mem_time=7;
      this->mem_gold=200;
      this->mem_food=300;
      this->mem_prereq=tech_bodkin_arrow;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_missile, 20, mod_multiplier));
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged_ap, unit_class_missile, 1, mod_additive));
      break;
      //Scale Armor
    case tech_scale_armor:
      this->mem_name = "Scale Armor";
      this->mem_technology = tech_scale_armor;
      this->mem_time=4;
      this->mem_food=100;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_infantry, 1, mod_additive));
      break;
      //Chainmail Armor
    case tech_chainmail_armor:
      this->mem_name = "Chainmail Armor";
      this->mem_technology = tech_chainmail_armor;
      this->mem_time=5;
      this->mem_gold=100;
      this->mem_food=200;
      this->mem_prereq=tech_scale_armor;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_infantry, 1, mod_additive));
      break;
      //Plate Armor
    case tech_plate_armor:
      this->mem_name = "Plate Armor";
      this->mem_technology = tech_plate_armor;
      this->mem_time=7;
      this->mem_gold=150;
      this->mem_food=300;
      this->mem_prereq=tech_chainmail_armor;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_infantry, 1, mod_additive));
      break;
      //Scale Barding
    case tech_scale_barding:
      this->mem_name = "Scale Barding";
      this->mem_technology = tech_scale_barding;
      this->mem_time=4;
      this->mem_food=150;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_mounted, 1, mod_additive));
      break;
      //Chainmail Barding
    case tech_chainmail_barding:
      this->mem_name = "Chainmail Barding";
      this->mem_technology = tech_chainmail_barding;
      this->mem_time=5;
      this->mem_gold=150;
      this->mem_food=250;
      this->mem_prereq=tech_scale_barding;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_mounted, 1, mod_additive));
      break;
      //Plate Barding
    case tech_plate_barding:
      this->mem_name = "Plate Barding";
      this->mem_technology = tech_plate_barding;
      this->mem_time=7;
      this->mem_gold=200;
      this->mem_food=350;
      this->mem_prereq=tech_chainmail_barding;
      this->mem_age=2;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_mounted, 1, mod_additive));
      break;
      //Tracking
    case tech_tracking:
      this->mem_name = "Tracking";
      this->mem_technology = tech_tracking;
      this->mem_time=3;
      this->mem_food=50;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_sight, unit_class_infantry, 1, mod_additive));
      break;
      //Arson
    case tech_arson:
      this->mem_name = "Arson";
      this->mem_technology = tech_arson;
      this->mem_time=5;
      this->mem_gold=50;
      this->mem_food=150;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_building, unit_class_infantry, 25, mod_multiplier));
      break;
      //Thumb Ring
    case tech_thumb_ring:
      this->mem_name = "Thumb Ring";
      this->mem_technology = tech_thumb_ring;
      this->mem_time=5;
      this->mem_food=300;
      this->mem_wood=250;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_missile, 20, mod_multiplier));
      break;
      //Thumb Ring
    case tech_bloodlines:
      this->mem_name = "Bloodlines";
      this->mem_technology = tech_bloodlines;
      this->mem_time=6;
      this->mem_gold=100;
      this->mem_food=150;
      this->mem_age=1;
      this->mem_bonus.push_back(new bonus(bonus_unit_class, unit_bonus_hp, unit_class_mounted, 15, mod_multiplier));
      break;

    default:
      break;
    }
}

//(B) Tech Pool
std::vector<tech*> get_technologies()
{
  std::vector<tech*> ret;

  int i;
  for(i=0; i<NUM_CORE_TECHS; i++)
    {
      ret.push_back(new tech( (enum technology) i));
    }

  return ret;
}
