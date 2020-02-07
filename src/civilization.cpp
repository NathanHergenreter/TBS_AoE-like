/********* CONTENTS **********/
//(A) Civ Constructor and Destructor

//(ZA) Civilization Type Loc
//(ZB) Civ Bonuses
//(ZC) Create Civs

/********* CONTENTS **********/

#include "civilization.h"
#include "entity.h"

std::string civ_loc[] = { "Afghans", "Arabs", "Aztecs", "Burmese", "Chinese", "Cumans", "English", "Ethiopians", "French", "Gaels", "Germans", "Incas", "Indians", "Iroquois", "Italians", "Japanese", "Khmer", "Koreans", "Malay", "Malians", "Mayans", "Mongols", "Moors", "Muisca", "Norse", "Persians", "Poles", "Portuguese", "Romans", "Russians", "Spanish", "Turks", "Vietnamese", "Random" };

std::string civ_adj_loc[] = { "Afghan", "Arab", "Aztec", "Burmese", "Chinese", "Cuman", "English", "Ethiopian", "French", "Gaelic", "German", "Incan", "Indiab", "Iroquoian", "Italian", "Japanese", "Khmer", "Korean", "Malay", "Malian", "Mayan", "Mongol", "Moorish", "Muiscan", "Norse", "Persian", "Polish", "Portuguese", "Roman", "Russian", "Spanish", "Turkish", "Vietnamese", "ERROR" };

//(A) Civ Constructor
civilization :: civilization(enum civ_type civ)
{
  name=civ_loc[civ];
  adjective=civ_adj_loc[civ];

  //Bonuses and Unique Unit/Techs
  switch(civ)
    {
      //Afghans
    case civ_afghans:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_armor, unit_horse_archers, 2, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_range, unit_javelinmen, 2, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_javelinmen, 2, mod_additive));
      mem_unique=unit_ghilman;
      break;

      //Arabs
    case civ_arabs:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_building, unit_class_skirmisher, 18, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_market, 4, mod_additive));
      mem_unique=unit_fursan;
      break;

      //Aztecs
    case civ_aztecs:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_axemen, 6, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_melee_ap, unit_axemen, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_move, unit_javelinmen, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_accuracy, unit_javelinmen, 15, mod_additive));
      mem_unique=unit_cuauhtli;
      break;

      //Burmese
    case civ_burmese:
      bon1.push_back(new bonus(bonus_bldg, bldg_bonus_cost_wood, bldg_lumberyard, -50, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_polearm, 8, mod_additive));
      mem_unique=unit_sain;
      break;

      //Chinese
    case civ_chinese:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_ranged, unit_crossbowmen, 8, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_range, unit_crossbowmen, 1, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_farm, 4, mod_additive));
      mem_unique=unit_nu_shou;
      break;

      //Cumans
    case civ_cumans:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_class_missile, 2, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_cost_wood, bldg_stables, -60, mod_additive));
      mem_unique=unit_attar;
      break;

      //English
    case civ_english:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_range, unit_archers, 2, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_archers, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_wood, unit_carrack, -25, mod_multiplier));
      mem_unique=unit_yeoman_archers;
      break;

      //Ethiopians
    case civ_ethiopians:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_accuracy, unit_archers, 20, mod_additive));
      bon1.push_back(new bonus(bonus_bldg, bldg_bonus_cost_wood, bldg_gold, -30, mod_additive));
      mem_unique=unit_shotelai;
      break;

      //French
    case civ_french:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_hp, unit_class_mounted, 20, mod_multiplier));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_cost_stone, bldg_castle, -33, mod_multiplier));
      mem_unique=unit_gendarmes;
      break;

      //Gaels
    case civ_gaels:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_javelinmen, 12, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_swordsmen, 8, mod_additive));
      mem_unique=unit_gall_oglaigh;
      break;

      //Germans
    case civ_germans:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_hp, unit_class_melee, 20, mod_multiplier));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_siege, 15, mod_multiplier));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_building, unit_class_siege, 15, mod_multiplier));
      mem_unique=unit_landsknechte;
      break;

      //Incas
    case civ_incas:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_melee_ap, unit_class_polearm, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_spearmen, 8, mod_additive));
      mem_unique=unit_awqaq_macana;
      break;

      //Indians
    case civ_indians:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_gold, unit_class_mounted, -20, mod_multiplier));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_food, unit_class_mounted, -20, mod_multiplier));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_move, unit_bombard, 2, mod_additive));
      mem_unique=unit_gaj;
      break;

      //Iroquois
    case civ_iroquois:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_move, unit_class_infantry, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_move, unit_axemen, 1, mod_additive));
      mem_unique=unit_tomahawk_ayawisgi;
      break;

      //Italians
    case civ_italians:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_ship, 15, mod_multiplier));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_dock, 4, mod_additive));
      mem_unique=unit_galea_bastarda;
      break;

      //Japanese
    case civ_japanese:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_horse_archers, 20, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_armor, unit_horse_archers, 2, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_gold, unit_horse_archers, 60, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_food, bldg_dock, 4, mod_additive));
      mem_unique=unit_samurai;
      break;

      //Khmer
    case civ_khmer:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_food, unit_class_infantry, -33, mod_multiplier));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_wood, unit_class_infantry, -33, mod_multiplier));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_infantry, -15, mod_multiplier));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_infantry, -15, mod_multiplier));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_wood, bldg_lumberyard, 4, mod_additive));
      mem_unique=unit_damri;
      break;

      //Koreans
    case civ_koreans:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_armor, unit_class_ship, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_range, unit_class_siege, 1, mod_additive));
      mem_unique=unit_geobukseon;
      break;

      //Malay
    case civ_malay:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_wood, unit_galley, -33, mod_multiplier));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_range, unit_galley, 2, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_galley, 2, mod_additive));
      mem_unique=unit_lancaran;
      break;

      //Malians
    case civ_malians:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_wood, unit_class_missile, -25, mod_multiplier));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_gold, bldg_gold, 4, mod_additive));
      mem_unique=unit_horon;
      break;

      //Mayans
    case civ_mayans:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_class_infantry, 2, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_stone, bldg_stone, 4, mod_additive));
      mem_unique=unit_macahuitl;
      break;

      //Mongols
    case civ_mongols:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_hp, unit_class_siege, 20, mod_multiplier));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_move, unit_class_siege, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_ranged, unit_class_mounted, 25, mod_multiplier));
      mem_unique=unit_mangudai;
      break;

      //Moors
    case civ_moors:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_building, unit_light_horsemen, 15, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_move, unit_light_horsemen, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_building, unit_galley, 20, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_move, unit_galley, 2, mod_additive));
      mem_unique=unit_jinetes;
      break;

      //Muisca
    case civ_muisca:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_accuracy, unit_class_missile, 15, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_sight, unit_class_missile, 2, mod_additive));
      mem_unique=unit_guecha;
      break;

      //Norse
    case civ_norse:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_hp, unit_axemen, 15, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_move, unit_class_ship, 2, mod_additive));
      mem_unique=unit_skeid;
      break;

      //Persians
    case civ_persians:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_cavaliers, 12, mod_additive));
      bon2.push_back(new bonus(bonus_unit_class, unit_bonus_gold, unit_class_gunpowder, -20, mod_multiplier));
      mem_unique=unit_qizilbash;
      break;

      //Poles
    case civ_poles:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_melee, unit_class_mounted, 12, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_move, unit_cavaliers, 1, mod_additive));
      mem_unique=unit_husarz;
      break;

      //Portuguese
    case civ_portuguese:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_move, unit_carrack, 2, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_carrack, 3, mod_additive));
      bon2.push_back(new bonus(bonus_bldg, bldg_bonus_cost_wood, bldg_dock, -50, mod_additive));
      mem_unique=unit_nau;
      break;

      //Romans
    case civ_romans:
      bon1.push_back(new bonus(bonus_bldg, bldg_bonus_hp, bldg_wall, 200, mod_additive));
      bon1.push_back(new bonus(bonus_bldg, bldg_bonus_hp, bldg_gate, 250, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_galley, 20, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_melee_ap, unit_galley, 3, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_building, unit_galley, 10, mod_additive));
      mem_unique=unit_kataphraktoi;
      break;

      //Russians
    case civ_russians:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_sight, unit_light_horsemen, 2, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_melee, unit_light_horsemen, 8, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_armor, unit_light_horsemen, 1, mod_additive));
      mem_unique=unit_boyare;
      break;

      //Spanish
    case civ_spanish:
      bon1.push_back(new bonus(bonus_unit, unit_bonus_accuracy, unit_carrack, 20, mod_additive));
      bon1.push_back(new bonus(bonus_unit, unit_bonus_ranged, unit_carrack, 15, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_hp, unit_pikemen, 25, mod_additive));
      mem_unique=unit_arcabuceros;
      break;

      //Turks
    case civ_turks:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_accuracy, unit_class_gunpowder, 15, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_food, unit_light_horsemen, -30, mod_additive));
      mem_unique=unit_yeniceri;
      break;

      //Vietnamese
    case civ_vietnamese:
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_sight, unit_class_gunpowder, 2, mod_additive));
      bon1.push_back(new bonus(bonus_unit_class, unit_bonus_move, unit_class_gunpowder, 1, mod_additive));
      bon2.push_back(new bonus(bonus_unit, unit_bonus_accuracy, unit_handgunners, 25, mod_additive));
      mem_unique=unit_sung_hoa_mai;
      break;

      //Basically default
    case civ_random:
      break;
    }
}

//(ZA) Civ Loc
std::string get_civ_name(enum civ_type civ) { return civ_loc[civ]; }

//(ZB) Civ Bonuses

//(ZC) Civ Creation
std::vector<civilization*> create_civs()
{
  std::vector<civilization*> ret;
  int i;

  for(i=0; i<civ_random+1; i++)
    {
      ret.push_back( new civilization((enum civ_type) i) );
    }

  return ret;
}
