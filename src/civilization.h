#ifndef CIVILIZATION_H

#define CIVILIZATION_H

#include <string>
#include <vector>
#include "bonus.h"

enum civ_type { civ_afghans, civ_arabs, civ_aztecs, civ_burmese, civ_chinese, civ_cumans, civ_english, civ_ethiopians, civ_french, civ_gaels, civ_germans, civ_incas, civ_indians, civ_iroquois, civ_italians, civ_japanese, civ_khmer, civ_koreans, civ_malay, civ_malians, civ_mayans, civ_mongols, civ_moors, civ_muisca, civ_norse, civ_persians, civ_poles, civ_portuguese, civ_romans, civ_russians, civ_spanish, civ_turks, civ_vietnamese, civ_random };

class civilization
{
  enum civ_type civ;
  std::string name;
  std::string adjective;
  std::vector<bonus *> bon1;
  std::vector<bonus *> bon2;
  int mem_unique;

 public:
  civilization();
  civilization(enum civ_type);
  ~civilization();
  enum civ_type get_civ() { return civ; }
  std::string get_name() { return name; }
  std::string get_adj() { return adjective; }
  std::vector<bonus *> * bonus_1() { return &bon1; }
  std::vector<bonus *> * bonus_2() { return &bon2; }
  int unique() { return mem_unique; }
};

std::string get_civ_name(enum civ_type);
std::vector<civilization*> create_civs();

#endif
