/********* CONTENTS **********/
//(A) Superclass Constructor

//(B) Building Constructor

//(C) Unit Constructor

//(Za/b) Class Localization

//(Zc) Unit Localization

/********* CONTENTS **********/

#include "entity.h"

std::string bclass_loc[] = {"ERROR", "Economic", "Military", "Defense", "Research"};

std::string uclass_loc[] = {"ERROR", "Infantry","Melee", "Polearm", "Missile", "Mounted", "Siege", "Ship", "Unique", "Skirmisher", "Gunpowder" };

std::string unit_loc[] = {"ERROR", "Builders", "Axemen", "Spearmen", "Halberdiers", "Swordsmen", "Longswordsmen", "Greatswordsmen", "Pikemen", "Javelinmen", "Skirmishers", "Archers", "Longbowmen", "Crossbowmen", "Handgunners", "Musketeers", "Light Horsemen", "Reiters", "Horse Archers", "Cavaliers", "Knights", "Demi-Lancers", "Battering Ram", "Siege Tower", "Ballista", "Catapult", "Trebuchet", "Mortar", "Bombard", "Culverin", "Transport", "Galley", "Galleass", "Carrack", "Galleon", "Ghilman", "Fursan", "Cuauhtli", "Sain", "Nu Shou", "Attar", "Yeoman Archers", "Shotelai", "Gendarmes", "Gall Oglaigh", "Landsknechte", "Awqaq Macana", "Gaj", "Tomahawk Ayawisgi", "Galea Bastarda", "Samurai", "Damri", "Geobukseon", "Lancaran", "Horon", "Macahuitl", "Mangudai", "Jinetes", "Guecha", "Skeid", "Qizilbash", "Husarz", "Nau", "Kataphraktoi", "Boyare", "Arcabuceros", "Yeniceri", "Sung Hoa Mai"};

std::string bldg_loc[] = {"ERROR", "Castle", "House", "Farm", "Lumberyard", "Gold Mine", "Stone Mine", "Docks", "Market", "Barracks", "Range", "Stables", "Siege", "Wall", "Sentry Tower", "Tower", "Bombard Tower", "Blacksmith", "Academy"};

//(A) Superclass Constructor
entity :: entity() {}

//(A) Superclass Constructor - Building Factory
entity :: entity(building_template *t, int x, int y) 
{
  ent_type=entity_building;
  name=t->name;
  symbol=t->symbol;

  action=true;
  coords[0]=x, coords[1]=y;
  pop=t->pop;
  age=t->age;
  prereq=t->prereq;
  can_garrison=t->can_garrison;
  max_garrison=t->max_garrison;
  deploy_dist=t->deploy_dist;

  max_hp = t->max_hp;
  hp_bonus=t->hp_bonus;
  cur_hp=max_hp+hp_bonus;

  armor = t->armor;
  armor_bonus=t->armor_bonus;

  range = t->range;
  range_bonus = t->range_bonus;

  accuracy=t->accuracy;
  accuracy_bonus=t->accuracy_bonus;

  mem_sight=t->sight;
  mem_sight_bon=t->sight_bonus;
}


//(A) Superclass Constructor - Unit Factory
entity :: entity(unit_template *t, int x, int y) 
{
  ent_type=entity_unit;
  name=t->name;
  symbol=t->symbol;

  action=true;
  coords[0]=x, coords[1]=y;
  pop=t->pop;
  age=t->age;
  prereq=t->prereq;
  can_garrison=t->can_garrison;
  max_garrison=t->max_garrison;
  deploy_dist=t->deploy_dist;

  max_hp = t->max_hp;
  hp_bonus=t->hp_bonus;
  cur_hp=max_hp+hp_bonus;

  armor = t->armor;
  armor_bonus=t->armor_bonus;

  range = t->range;
  range_bonus = t->range_bonus;

  accuracy=t->accuracy;
  accuracy_bonus=t->accuracy_bonus;

  mem_sight=t->sight;
  mem_sight_bon=t->sight_bonus;
}

//(A) Entity Destructor
entity :: ~entity() { }

//(B) Building Constructor
building :: building() {}

//(B) Building Constructor - Factory
building :: building(building_template *t, int x, int y) : entity(t, x, y)
{
  type = (enum building_type) t->type;
  b_class = (enum building_class) t->b_class;
  terrain_type=t->terrain_type;
  mem_passable=t->passable;

  attack=t->attack;
  attack_bonus=t->attack_bonus;
  attack_pierce=t->attack_pierce;
  mem_ap_bon=t->attack_pierce_bonus;

  out_gold=t->out_gold;
  out_gold_bonus=t->out_gold_bonus;
  out_food=t->out_food;
  out_food_bonus=t->out_food_bonus;
  out_wood=t->out_wood;
  out_wood_bonus=t->out_wood_bonus;
  out_stone=t->out_stone;
  out_stone_bonus=t->out_stone_bonus;

  recruit_class = t->recruit_class;
  recruit_time=0;
  recruit=0;
  tech_pool=t->tech_pool;
  research_time = 0;
  research=0;
}

//(B) Building Destructor
building :: ~building() {}

//(C) Unit Constructor
unit :: unit() {}

//(C) Unit Constructor - Factory
unit :: unit(unit_template *t, int x, int y) : entity(t, x, y)
{
  type = (enum unit_type) t->type;
  u_class = (enum unit_class) t->u_class;
  int i; for(i=0; i<NUM_UNIT_CLASSES; i++) { subclasses[i] = (enum unit_class) t->subclasses[i]; }
  is_upgradable = t->is_upgradable;
  upgrade=(enum unit_type) t->upgrade;
  is_land = t->is_upgradable;
  is_land = t->is_land;
  is_naval = t->is_naval;
  is_indirect = t->is_indirect;
  building_attack = t->building_attack;
  building_attack_bonus = t->building_attack_bonus;
  melee_attack = t->melee_attack;
  melee_bonus = t->melee_bonus;
  melee_pierce = t->melee_pierce;
  melee_pierce_bonus = t->melee_pierce_bonus;
  ranged_attack = t->ranged_attack;
  ranged_bonus = t->ranged_bonus;
  ranged_pierce = t->ranged_pierce;
  ranged_pierce_bonus = t->ranged_pierce_bonus;
  max_move = t->max_move;
  cur_move = max_move;
  move_bonus = t->move_bonus;
}
//(C) Unit Destructor
unit :: ~unit() {}

//(Za) Building Class Localization
std::string get_bclass_loc(enum building_class bclass)
{
  return bclass_loc[bclass];
}

//(Zb) Unit Class Localization
std::string get_uclass_loc(enum unit_class uclass)
{
  return uclass_loc[uclass];
}

//(Zc)
std::string get_unit_loc(enum unit_type u)
{
  return unit_loc[u];
}

//(Zd)
std::string get_bldg_loc(enum building_type b)
{
  return bldg_loc[b];
}
