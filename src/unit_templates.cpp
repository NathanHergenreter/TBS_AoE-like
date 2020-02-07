/********* CONTENTS **********/
//(A) Constructor

//(B) Factory Vector

/********* CONTENTS **********/

#include "unit_templates.h"
#include "technology.h"

//Local Dupes
enum unit_type_dupe { unit_default, unit_builders, unit_axemen, unit_spearmen, unit_halberdiers, unit_swordsmen, unit_longswordsmen, unit_greatswordsmen, unit_pikemen, unit_javelinmen, unit_skirmishers, unit_archers, unit_longbowmen, unit_crossbowmen, unit_handgunners, unit_musketeers, unit_light_horsemen, unit_reiters, unit_horse_archers, unit_cavaliers, unit_knights, unit_demi_lancers, unit_ram, unit_siege_tower, unit_ballista, unit_catapult, unit_trebuchet, unit_mortar, unit_bombard, unit_culverin, unit_transport, unit_galley, unit_galleass, unit_carrack, unit_galleon, unit_ghilman, unit_fursan, unit_cuauhtli, unit_sain, unit_nu_shou, unit_attar, unit_yeoman_archers, unit_shotelai, unit_gendarmes, unit_gall_oglaigh, unit_landsknechte, unit_awqaq_macana, unit_gaj, unit_tomahawk_ayawisgi, unit_galea_bastarda, unit_samurai, unit_damri, unit_geobukseon, unit_lancaran, unit_horon, unit_macahuitl, unit_mangudai, unit_jinetes, unit_guecha, unit_skeid, unit_qizilbash, unit_husarz, unit_nau, unit_kataphraktoi, unit_boyare, unit_arcabuceros, unit_yeniceri, unit_sung_hoa_mai };

enum unit_class_dupe { unit_class_default, unit_class_infantry, unit_class_melee, unit_class_polearm, unit_class_missile, unit_class_mounted, unit_class_siege, unit_class_ship, unit_class_unique, unit_class_skirmisher, unit_class_gunpowder };


//(A) Constuctor
unit_template :: unit_template(int t)
{
  this->type=t;

  init_gold=0;
  init_food=0;
  init_wood=0;
  init_stone=0;
  name="ERROR";
  symbol='?';
  pop=-1;
  age=0;
  prereq=tech_default;
  max_hp=0;
  hp_bonus=0;
  armor=0;
  armor_bonus=0;
  range=0;
  range_bonus=0;
  accuracy=0;
  accuracy_bonus=0;
  sight=0;
  sight_bonus=0;
  can_garrison=false;
  max_garrison=0;
  deploy_dist=1;
  type=unit_default;
  u_class=unit_class_default;
  subclasses[unit_class_default]=0, subclasses[unit_class_infantry]=0, subclasses[unit_class_melee]=0, subclasses[unit_class_polearm]=0, subclasses[unit_class_missile]=0, subclasses[unit_class_mounted]=0, subclasses[unit_class_siege]=0, subclasses[unit_class_ship]=0, subclasses[unit_class_unique]=0, subclasses[unit_class_skirmisher]=0, subclasses[unit_class_gunpowder]=0;
  time=1;
  is_upgradable=false;
  upgrade=unit_default;
  is_land=true;
  is_naval=false;
  is_indirect=false;
  building_attack=10;
  building_attack_bonus=0;
  melee_attack=10;
  melee_bonus=0;
  melee_pierce=0;
  melee_pierce_bonus=0;
  ranged_attack=10;
  ranged_bonus=0;
  ranged_pierce=0;
  ranged_pierce_bonus=0;
  max_move=1;
  move_bonus=0;

  //Unique for each building type
  switch(t)
    {
      //Builders
    case unit_builders:
      init_gold=10;
      init_food=10;
      name="Builders";
      symbol='e';
      max_hp=30;
      type=unit_builders;
      u_class=unit_class_unique;
      max_move=2;
      sight=4;
      building_attack=10;
      melee_attack=0;
      ranged_attack=0;
      break;

      //Axemen
    case unit_axemen:
      init_gold=20;
      init_food=30;
      name="Axemen";
      symbol='w';
      max_hp=60;
      type=unit_axemen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=1;
      is_upgradable=true;
      upgrade=unit_halberdiers;
      building_attack=15;
      melee_attack=24;
      melee_pierce=1;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Spearmen
    case unit_spearmen:
      init_gold=10;
      init_food=20;
      init_wood=20;
      name="Spearmen";
      symbol='d';
      max_hp=80;
      type=unit_spearmen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_polearm]=1;
      is_upgradable=true;
      upgrade=unit_halberdiers;
      building_attack=15;
      melee_attack=18;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Halberdiers
    case unit_halberdiers:
      init_gold=30;
      init_food=30;
      init_wood=30;
      name="Halberdiers";
      symbol='h';
      prereq=tech_halberdiers;
      max_hp=100;
      armor=2;
      type=unit_halberdiers;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_polearm]=1;
      building_attack=15;
      melee_attack=28;
      melee_pierce=2;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Swordsmen
    case unit_swordsmen:
      init_gold=50;
      init_food=50;
      name="Swordsmen";
      symbol='s';
      max_hp=65;
      armor=1;
      type=unit_swordsmen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=2;
      is_upgradable=true;
      upgrade=unit_longswordsmen;
      building_attack=15;
      melee_attack=26;
      melee_pierce=1;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Longswordsmen
    case unit_longswordsmen:
      init_gold=75;
      init_food=85;
      name="Longswordsmen";
      symbol='l';
      prereq=tech_longswordsmen;
      max_hp=80;
      armor=2;
      type=unit_longswordsmen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=2;
      is_upgradable=true;
      upgrade=unit_greatswordsmen;
      building_attack=15;
      melee_attack=30;
      melee_pierce=1;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Greatswordsmen
    case unit_greatswordsmen:
      init_gold=115;
      init_food=135;
      name="Greatswordsmen";
      symbol='g';
      prereq=tech_greatswordsmen;
      max_hp=95;
      armor=3;
      type=unit_greatswordsmen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=2;
      building_attack=15;
      melee_attack=36;
      melee_pierce=2;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Pikemen
    case unit_pikemen:
      init_food=80;
      name="Pikemen";
      symbol='p';
      age=1;
      max_hp=130;
      type=unit_pikemen;
      u_class=unit_class_melee;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_polearm]=1;
      building_attack=15;
      melee_attack=22;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Javelinmen
    case unit_javelinmen:
      init_food=30;
      init_wood=20;
      name="Javelinmen";
      symbol='j';
      max_hp=50;
      range=2;
      accuracy=80;
      type=unit_javelinmen;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      is_upgradable=true;
      upgrade=unit_skirmishers;
      ranged_attack=24;
      ranged_pierce=1;
      max_move=4;
      sight=7;
      break;

      //Skirmishers
    case unit_skirmishers:
      init_food=40;
      init_wood=30;
      name="Skirmishers";
      symbol='v';
      prereq=tech_skirmishers;
      max_hp=80;
      range=2;
      accuracy=90;
      type=unit_skirmishers;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      ranged_attack=28;
      ranged_pierce=1;
      max_move=4;
      sight=6;
      break;

      //Archers
    case unit_archers:
      init_gold=20;
      init_wood=30;
      name="Archers";
      symbol='a';
      max_hp=40;
      range=4;
      accuracy=60;
      type=unit_archers;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      is_upgradable=true;
      upgrade=unit_longbowmen;
      is_indirect=true;
      ranged_attack=20;
      max_move=4;
      sight=6;
      break;

      //Longbowmen
    case unit_longbowmen:
      init_gold=35;
      init_wood=50;
      name="Longbowmen";
      symbol='b';
      prereq=tech_longbowmen;
      max_hp=65;
      range=5;
      accuracy=75;
      type=unit_longbowmen;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      is_indirect=true;
      ranged_attack=26;
      ranged_pierce=1;
      max_move=4;
      sight=6;
      break;

      //Crossbowmen
    case unit_crossbowmen:
      init_gold=30;
      init_wood=40;
      name="Crossbowmen";
      symbol='x';
      age=1;
      max_hp=60;
      range=4;
      accuracy=70;
      type=unit_crossbowmen;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      is_indirect=true;
      ranged_attack=26;
      ranged_pierce=2;
      max_move=4;
      sight=6;
      break;

      //Handgunners
    case unit_handgunners:
      init_gold=60;
      init_food=40;
      name="Handgunners";
      symbol='c';
      prereq=tech_gunpowder;
      max_hp=40;
      range=3;
      accuracy=33;
      type=unit_handgunners;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_gunpowder]=1;
      time=2;
      is_upgradable=true;
      upgrade=unit_musketeers;
      ranged_attack=28;
      ranged_pierce=3;
      max_move=3;
      sight=5;
      break;

      //Musketeers
    case unit_musketeers:
      init_gold=80;
      init_food=55;
      name="Musketeers";
      symbol='m';
      prereq=tech_musketeers;
      max_hp=60;
      range=4;
      accuracy=50;
      type=unit_musketeers;
      u_class=unit_class_missile;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_gunpowder]=1;
      ranged_attack=36;
      ranged_pierce=4;
      max_move=3;
      sight=5;
      break;

      //Light Horsemen
    case unit_light_horsemen:
      init_gold=40;
      init_food=60;
      name="Light Horsemen";
      symbol='L';
      max_hp=80;
      range=2;
      accuracy=70;
      type=unit_light_horsemen;
      u_class=unit_class_mounted;
      subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      time=1;
      is_upgradable=true;
      upgrade=unit_reiters;
      melee_attack=18;
      ranged_attack=22;
      ranged_pierce=1;
      max_move=6;
      sight=8;
      break;

      //Reiters
    case unit_reiters:
      init_gold=80;
      init_food=100;
      name="Reiters";
      symbol='R';
      prereq=tech_reiters;
      max_hp=105;
      range=2;
      accuracy=60;
      type=unit_reiters;
      u_class=unit_class_mounted;
      subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1, subclasses[unit_class_gunpowder]=1;
      time=2;
      building_attack=5;
      melee_attack=21;
      ranged_attack=31;
      ranged_pierce=3;
      max_move=6;
      sight=8;
      break;

      //Horse Archers
    case unit_horse_archers:
      init_gold=60;
      init_food=40;
      init_wood=30;
      name="Horse Archers";
      symbol='A';
      max_hp=80;
      range=4;
      accuracy=75;
      type=unit_horse_archers;
      u_class=unit_class_mounted;
      subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      ranged_attack=24;
      ranged_pierce=1;
      max_move=6;
      sight=8;
      break;

      //Cavaliers
    case unit_cavaliers:
      init_gold=80;
      init_food=60;
      name="Cavaliers";
      symbol='E';
      max_hp=120;
      armor=3;
      type=unit_cavaliers;
      u_class=unit_class_mounted;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=3;
      is_upgradable=true;
      upgrade=unit_knights;
      building_attack=15;
      melee_attack=28;
      melee_pierce=1;
      ranged_attack=0;
      max_move=5;
      sight=7;
      break;

      //Knights
    case unit_knights:
      init_gold=120;
      init_food=100;
      name="Knights";
      symbol='K';
      prereq=tech_knights;
      max_hp=150;
      armor=4;
      type=unit_knights;
      u_class=unit_class_mounted;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=3;
      is_upgradable=true;
      upgrade=unit_demi_lancers;
      building_attack=15;
      melee_attack=36;
      melee_pierce=2;
      ranged_attack=0;
      max_move=5;
      sight=7;
      break;

      //Demi-Lancers
    case unit_demi_lancers:
      init_gold=150;
      init_food=115;
      name="Demi-Lancers";
      symbol='D';
      prereq=tech_demi_lancers;
      max_hp=165;
      armor=3;
      type=unit_demi_lancers;
      u_class=unit_class_mounted;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      building_attack=6;
      melee_attack=39;
      melee_pierce=2;
      range=2;
      accuracy=60;
      ranged_attack=27;
      ranged_pierce=2;
      max_move=5;
      sight=7;
      break;

      //Battering Ram
    case unit_ram:
      init_wood=80;
      name="Battering Ram";
      symbol='S';
      max_hp=220;
      armor=3;
      can_garrison=true;
      max_garrison=5;
      type=unit_ram;
      u_class=unit_class_siege;
      subclasses[unit_class_siege]=1;
      time=2;
      building_attack=40;
      melee_pierce=4;
      ranged_attack=0;
      max_move=2;
      sight=5;
      break;

      //Siege Tower
    case unit_siege_tower:
      init_gold=20;
      init_wood=140;
      name="Siege Tower";
      symbol='H';
      max_hp=325;
      armor=3;
      range=4;
      accuracy=80;
      can_garrison=true;
      max_garrison=3;
      deploy_dist=2;
      type=unit_siege_tower;
      u_class=unit_class_siege;
      subclasses[unit_class_siege]=1;
      time=3;
      is_indirect=true;
      building_attack=24;
      melee_attack=0;
      ranged_attack=24;
      ranged_pierce=1;
      max_move=2;
      sight=5;
      break;

      //Ballista
    case unit_ballista:
      init_food=50;
      init_wood=50;
      name="Ballista";
      symbol='O';
      max_hp=120;
      armor=1;
      range=6;
      accuracy=60;
      type=unit_ballista;
      u_class=unit_class_siege;
      subclasses[unit_class_siege]=1;
      time=2;
      building_attack=29;
      melee_attack=0;
      ranged_attack=43;
      ranged_pierce=3;
      max_move=3;
      sight=7;
      break;

      //Catapult
    case unit_catapult:
      init_gold=60;
      init_wood=80;
      init_stone=40;
      name="Catapult";
      symbol='P';
      max_hp=140;
      armor=1;
      range=5;
      accuracy=30;
      type=unit_catapult;
      u_class=unit_class_siege;
      subclasses[unit_class_siege]=1;
      time=3;
      is_upgradable=true;
      upgrade=unit_trebuchet;
      building_attack=40;
      melee_attack=0;
      ranged_attack=28;
      ranged_pierce=4;
      max_move=2;
      sight=5;
      break;

      //Trebuchet
    case unit_trebuchet:
      init_gold=80;
      init_wood=115;
      init_stone=60;
      name="Trebuchet";
      symbol='T';
      prereq=tech_trebuchet;
      max_hp=165;
      armor=1;
      range=6;
      accuracy=35;
      type=unit_trebuchet;
      u_class=unit_class_siege;
      subclasses[unit_class_siege]=1;
      time=3;
      building_attack=55;
      melee_attack=0;
      ranged_attack=35;
      ranged_pierce=4;
      max_move=2;
      sight=5;
      break;

      //Mortar
    case unit_mortar:
      init_gold=100;
      init_food=30;
      name="Mortar";
      symbol='M';
      prereq=tech_gunpowder;
      max_hp=80;
      range=3;
      accuracy=30;
      type=unit_mortar;
      u_class=unit_class_siege;
      subclasses[unit_class_gunpowder]=1;
      time=2;
      is_indirect=true;
      building_attack=34;
      melee_attack=0;
      ranged_attack=34;
      ranged_pierce=5;
      max_move=2;
      sight=5;
      break;

      //Bombard
    case unit_bombard:
      init_gold=120;
      init_food=60;
      name="Bombard";
      symbol='B';
      prereq=tech_gunpowder;
      max_hp=95;
      range=7;
      accuracy=20;
      type=unit_bombard;
      u_class=unit_class_siege;
      subclasses[unit_class_gunpowder]=1;
      time=3;
      is_upgradable=true;
      upgrade=unit_culverin;
      building_attack=60;
      melee_attack=0;
      ranged_attack=42;
      ranged_pierce=6;
      max_move=2;
      sight=5;
      break;

      //Culverin
    case unit_culverin:
      init_gold=160;
      init_food=90;
      name="Culverin";
      prereq=tech_culverin;
      symbol='S';
      max_hp=115;
      range=8;
      accuracy=33;
      type=unit_culverin;
      u_class=unit_class_siege;
      subclasses[unit_class_gunpowder]=1;
      time=3;
      building_attack=72;
      melee_attack=0;
      ranged_attack=48;
      ranged_pierce=6;
      max_move=2;
      sight=5;
      break;

      //Transport Ship
    case unit_transport:
      init_wood=60;
      name="Transport Ship";
      symbol='E';
      max_hp=200;
      armor=2;
      can_garrison=true;
      max_garrison=10;
      type=unit_transport;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1;
      time=2;
      is_land=false;
      is_naval=true;
      building_attack=0;
      melee_attack=0;
      ranged_attack=0;
      max_move=4;
      sight=6;
      break;

      //Galley
    case unit_galley:
      init_gold=40;
      init_wood=70;
      name="Galley";
      symbol='D';
      max_hp=220;
      armor=2;
      range=4;
      accuracy=75;
      type=unit_galley;
      u_class=unit_class_ship;
      subclasses[unit_class_missile]=1, subclasses[unit_class_ship]=1;
      time=3;
      is_upgradable=true;
      upgrade=unit_galleass;
      is_land=false;
      is_naval=true;
      building_attack=20;
      melee_attack=15;
      ranged_attack=25;
      ranged_pierce = 1;
      max_move=6;
      sight=6;
      break;

      //Galleass
    case unit_galleass:
      init_gold=80;
      init_wood=115;
      name="Galleass";
      symbol='F';
      prereq=tech_gunpowder;
      max_hp=280;
      armor=2;
      range=6;
      accuracy=75;
      type=unit_galleass;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      is_land=false;
      is_naval=true;
      building_attack=45;
      melee_attack=15;
      ranged_attack=38;
      ranged_pierce=5;
      max_move=6;
      sight=6;
      break;

      //Carrack
    case unit_carrack:
      init_gold=80;
      init_wood=150;
      name="Carrack";
      symbol='N';
      prereq=tech_gunpowder;
      max_hp=300;
      armor=3;
      range=4;
      accuracy=70;
      type=unit_carrack;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=4;
      is_upgradable=true;
      upgrade=unit_galleon;
      is_land=false;
      is_naval=true;
      building_attack=58;
      melee_attack=15;
      ranged_attack=48;
      ranged_pierce=5;
      max_move=5;
      sight=6;
      break;

      //Galleon
    case unit_galleon:
      init_gold=115;
      init_wood=225;
      name="Galleon";
      symbol='G';
      prereq=tech_galleon;
      max_hp=425;
      armor=3;
      range=6;
      accuracy=65;
      type=unit_galleon;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=4;
      is_land=false;
      is_naval=true;
      building_attack=70;
      melee_attack=15;
      ranged_attack=65;
      ranged_pierce=5;
      max_move=6;
      sight=6;
      break;

      //Ghilman
    case unit_ghilman:
      init_gold=90;
      init_food=50;
      name="Ghilman";
      symbol='U';
      max_hp=120;
      armor=2;
      range=4;
      accuracy=80;
      type=unit_ghilman;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      building_attack=15;
      melee_attack=33;
      ranged_attack=29;
      ranged_pierce=1;
      max_move=6;
      sight=6;
      break;

      //Fursan
    case unit_fursan:
      init_gold=130;
      init_food=85;
      name="Fursan";
      symbol='U';
      max_hp=210;
      armor=3;
      range=4;
      accuracy=80;
      type=unit_fursan;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1;
      time=4;
      is_indirect=true;
      building_attack=15;
      melee_attack=44;
      melee_pierce=2;
      ranged_attack=28;
      ranged_pierce=1;
      max_move=5;
      sight=7;
      break;

      //Cuauhtli
    case unit_cuauhtli:
      init_gold=80;
      init_food=185;
      name="Cuauhtli";
      symbol='U';
      max_hp=120;
      type=unit_cuauhtli;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=3;
      building_attack=15;
      melee_attack=44;
      melee_pierce=2;
      ranged_attack=0;
      max_move=5;
      sight=7;
      break;

      //Sain
    case unit_sain:
      init_food=230;
      name="Sain";
      symbol='U';
      max_hp=380;
      armor=2;
      type=unit_sain;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=4;
      building_attack=35;
      melee_attack=47;
      melee_pierce=3;
      ranged_attack=0;
      max_move=4;
      sight=5;
      break;

      //Nu Shou
    case unit_nu_shou:
      init_gold=60;
      init_wood=90;
      name="Nu Shou";
      symbol='U';
      max_hp=85;
      range=6;
      accuracy=75;
      type=unit_nu_shou;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      ranged_attack=38;
      ranged_pierce=3;
      max_move=4;
      sight=6;
      break;

      //Attar
    case unit_attar:
      init_food=100;;
      init_wood=60;
      name="Attar";
      symbol='U';
      max_hp=100;
      range=5;
      accuracy=90;
      type=unit_attar;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      building_attack=20;
      melee_attack=24;
      ranged_attack=35;
      ranged_pierce=1;
      max_move=8;
      sight=10;
      break;

      //Yeoman Archers
    case unit_yeoman_archers:
      init_gold=60;
      init_wood=100;
      name="Yeoman Archers";
      symbol='U';
      max_hp=80;
      range=6;
      accuracy=95;
      type=unit_yeoman_archers;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      ranged_attack=40;
      ranged_pierce=2;
      max_move=4;
      sight=7;
      break;

      //Shotelai
    case unit_shotelai:
      init_gold=60;
      init_food=90;
      name="Shotelai";
      symbol='U';
      max_hp=110;
      armor=2;
      type=unit_shotelai;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=2;
      building_attack=15;
      melee_attack=34;
      melee_pierce=1;
      ranged_attack=0;
      max_move=4;
      sight=6;
      break;

      //Gendarmes
    case unit_gendarmes:
      init_gold=160;
      init_food=120;
      name="Gendarmes";
      symbol='U';
      age=2;
      max_hp=185;
      armor=4;
      type=unit_gendarmes;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=4;
      building_attack=15;
      melee_attack=56;
      melee_pierce=2;
      max_move=4;
      sight=6;
      break;

      //Gall Oglaigh
    case unit_gall_oglaigh:
      init_gold=80;
      init_food=80;
      name="Gall Oglaigh";
      symbol='U';
      max_hp=125;
      type=unit_gall_oglaigh;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1;
      time=3;
      building_attack=25;
      melee_attack=40;
      melee_pierce=2;
      ranged_attack=0;
      max_move=5;
      sight=7;
      break;

      //Landsknechte
    case unit_landsknechte:
      init_gold=80;
      init_food=40;
      name="Landsknechte";
      symbol='U';
      age=2;
      max_hp=160;
      armor=2;
      type=unit_landsknechte;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_polearm]=1;
      time=2;
      building_attack=15;
      melee_attack=30;
      melee_pierce=2;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Awqaq Macana
    case unit_awqaq_macana:
      init_food=50;
      init_wood=30;
      name="Awqaq Macana";
      symbol='U';
      max_hp=100;
      type=unit_awqaq_macana;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_polearm]=1;
      building_attack=15;
      melee_attack=27;
      melee_pierce=2;
      ranged_attack=0;
      max_move=3;
      sight=5;
      break;

      //Gaj
    case unit_gaj:
      init_gold=80;
      init_food=185;
      name="Gaj";
      symbol='U';
      max_hp=250;
      armor=3;
      range=4;
      accuracy=75;
      type=unit_gaj;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1;
      time=4;
      is_indirect=true;
      building_attack=35;
      melee_attack=40;
      melee_pierce=3;
      ranged_attack=24;
      max_move=4;
      sight=6;
      break;

      //Tomahawk Ayawisgi
    case unit_tomahawk_ayawisgi:
      init_food=50;
      name="Tomahawk Ayawisgi";
      symbol='U';
      max_hp=85;
      type=unit_tomahawk_ayawisgi;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_skirmisher]=1;
      building_attack=20;
      melee_attack=38;
      melee_pierce=1;
      ranged_attack=0;
      max_move=5;
      sight=8;
      break;

      //Galea Bastarda
    case unit_galea_bastarda:
      init_gold=120;
      init_wood=200;
      name="Galea Bastarda";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=460;
      armor=2;
      range=6;
      accuracy=80;
      type=unit_galea_bastarda;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=4;
      is_land=false;
      is_naval=true;
      building_attack=50;
      melee_attack=25;
      ranged_attack=48;
      ranged_pierce=5;
      max_move=5;
      sight=6;
      break;

      //Samurai
    case unit_samurai:
      init_gold=80;
      init_food=50;
      init_wood=50;
      name="Samurai";
      symbol='U';
      age=1;
      max_hp=140;
      armor=2;
      range=5;
      accuracy=85;
      type=unit_samurai;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_infantry]=1;
      time=3;
      is_indirect=true;
      building_attack=15;
      melee_attack=36;
      ranged_attack=41;
      ranged_pierce=1;
      max_move=3;
      sight=5;
      break;

      //Damri
    case unit_damri:
      init_gold=105;
      init_food=170;
      name="Damri";
      symbol='U';
      max_hp=235;
      armor=3;
      range=6;
      accuracy=65;
      type=unit_damri;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1;
      time=4;
      building_attack=35;
      melee_attack=36;
      melee_pierce=3;
      ranged_attack=35;
      ranged_pierce=3;
      max_move=3;
      sight=6;
      break;

      //Geobukseon
    case unit_geobukseon:
      init_gold=120;
      init_wood=160;
      name="Geobukseon";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=400;
      armor=4;
      range=4;
      accuracy=65;
      type=unit_geobukseon;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=4;
      is_land=false;
      is_naval=true;
      building_attack=38;
      melee_attack=20;
      ranged_attack=41;
      ranged_pierce=4;
      max_move=3;
      sight=4;
      break;

      //Lancaran
    case unit_lancaran:
      init_gold=80;
      init_wood=80;
      name="Lancaran";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=250;
      armor=2;
      range=5;
      accuracy=75;
      type=unit_lancaran;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      is_land=false;
      is_naval=true;
      building_attack=38;
      melee_attack=25;
      ranged_attack=36;
      ranged_pierce=3;
      max_move=8;
      sight=6;
      break;

      //Horon
    case unit_horon:
      init_food=40;
      init_wood=40;
      name="Horon";
      symbol='U';
      max_hp=70;
      range=4;
      accuracy=75;
      type=unit_horon;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_infantry]=1, subclasses[unit_class_skirmisher]=1;
      is_indirect=true;
      building_attack=15;
      melee_attack=22;
      ranged_attack=23;
      max_move=4;
      sight=5;
      break;

      //Macahuitl
    case unit_macahuitl:
      init_food=90;
      name="Macahuitl";
      symbol='U';
      max_hp=100;
      type=unit_macahuitl;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_skirmisher]=1;
      building_attack=15;
      melee_attack=28;
      melee_pierce=2;
      ranged_attack=0;
      max_move=6;
      sight=8;
      break;

      //Mangudai
    case unit_mangudai:
      init_gold=40;
      init_food=80;
      init_wood=60;
      name="Mangudai";
      symbol='U';
      max_hp=125;
      range=5;
      accuracy=90;
      type=unit_attar;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      is_indirect=true;
      building_attack=35;
      melee_attack=27;
      ranged_attack=39;
      ranged_pierce=1;
      max_move=6;
      sight=7;
      break;

      //Jinetes
    case unit_jinetes:
      init_food=90;
      name="Jinetes";
      symbol='U';
      max_hp=95;
      range=2;
      accuracy=85;
      type=unit_jinetes;
      u_class=unit_class_unique;
      subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      building_attack=35;
      melee_attack=21;
      ranged_attack=31;
      ranged_pierce=1;
      max_move=7;
      sight=9;
      break;

      //Guecha
    case unit_guecha:
      init_food=80;
      name="Guecha";
      symbol='U';
      max_hp=105;
      range=2;
      accuracy=90;
      type=unit_guecha;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      melee_attack=23;
      ranged_attack=24;
      ranged_pierce=1;
      max_move=4;
      sight=7;
      break;

      //Skeid
    case unit_skeid:
      init_food=60;
      init_wood=80;
      name="Skeid";
      symbol='U';
      max_hp=200;
      armor=1;
      range=4;
      accuracy=80;
      can_garrison=true;
      max_garrison=10;
      type=unit_galley;
      u_class=unit_class_ship;
      subclasses[unit_class_missile]=1, subclasses[unit_class_ship]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      is_land=false;
      is_naval=true;
      building_attack=40;
      melee_attack=28;
      ranged_attack=25;
      ranged_pierce=1;
      max_move=8;
      sight=9;
      break;

      //Qizilbash
    case unit_qizilbash:
      init_gold=40;
      init_food=120;
      name="Qizilbash";
      symbol='U';
      age=2;
      max_hp=110;
      armor=1;
      range=5;
      accuracy=85;
      type=unit_qizilbash;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      time=2;
      is_indirect=true;
      building_attack=15;
      melee_attack=27;
      ranged_attack=38;
      ranged_pierce=1;
      max_move=6;
      sight=8;
      break;

      //Husarz
    case unit_husarz:
      init_food=160;
      name="Husarz";
      symbol='U';
      age=2;
      max_hp=150;
      armor=2;
      type=unit_husarz;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=3;
      building_attack=15;
      melee_attack=47;
      melee_pierce=1;
      max_move=6;
      sight=8;
      break;

      //Nau
    case unit_nau:
      init_gold=90;
      init_wood=120;
      name="Nau";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=265;
      armor=2;
      range=4;
      accuracy=85;
      type=unit_nau;
      u_class=unit_class_ship;
      subclasses[unit_class_ship]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      is_land=false;
      is_naval=true;
      building_attack=44;
      melee_attack=15;
      ranged_attack=41;
      ranged_pierce=5;
      max_move=8;
      sight=8;
      break;

      //Kataphraktoi
    case unit_kataphraktoi:
      init_gold=115;
      init_food=80;
      name="Kataphraktoi";
      symbol='U';
      max_hp=190;
      armor=3;
      type=unit_kataphraktoi;
      u_class=unit_class_unique;
      subclasses[unit_class_melee]=1, subclasses[unit_class_mounted]=1;
      time=3;
      building_attack=15;
      melee_attack=42;
      melee_pierce=3;
      max_move=3;
      sight=4;
      break;

      //Boyare
    case unit_boyare:
      init_gold=30;
      init_food=80;
      name="Boyare";
      symbol='U';
      age=1;
      max_hp=115;
      range=2;
      accuracy=80;
      type=unit_boyare;
      u_class=unit_class_unique;
      subclasses[unit_class_missile]=1, subclasses[unit_class_mounted]=1, subclasses[unit_class_skirmisher]=1;
      building_attack=15;
      melee_attack=27;
      ranged_attack=29;
      ranged_pierce=1;
      max_move=6;
      sight=6;
      break;

      //Arcabuceros
    case unit_arcabuceros:
      init_gold=95;
      init_food=60;
      name="Arcabuceros";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=80;
      range=5;
      accuracy=50;
      type=unit_arcabuceros;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      ranged_attack=44;
      ranged_pierce=5;
      max_move=3;
      sight=5;
      break;

      //Yeniceri
    case unit_yeniceri:
      init_gold=115;
      init_food=90;
      name="Yeniceri";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=115;
      range=4;
      accuracy=60;
      type=unit_yeniceri;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_gunpowder]=1;
      time=3;
      melee_attack=30;
      ranged_attack=41;
      ranged_pierce=4;
      max_move=3;
      sight=5;
      break;


      //Sung Hoa Mai
    case unit_sung_hoa_mai:
      init_gold=110;
      init_food=40;
      name="Sung Hoa Mai";
      symbol='U';
      prereq=tech_gunpowder;
      max_hp=65;
      range=5;
      accuracy=70;
      type=unit_sung_hoa_mai;
      u_class=unit_class_unique;
      subclasses[unit_class_infantry]=1, subclasses[unit_class_missile]=1, subclasses[unit_class_gunpowder]=1, subclasses[unit_class_skirmisher]=1;
      time=3;
      ranged_attack=39;
      ranged_pierce=4;
      max_move=4;
      sight=6;
      break;

      //Default - shouldn't happen
    default:
      break;
    }
}

//(B) Factory Vector
std::vector<unit_template*> get_unit_templates()
{
  std::vector<unit_template*> ret;

  int i;
  for(i=0; i<NUM_UNITS_BASIC; i++)
    {
      ret.push_back( new unit_template( (enum unit_type_dupe) i) );
    }

  return ret;
}
