#ifndef BUILDING_COMMANDS_H

#define BUILDING_COMMANDS_H

#include "entity.h"
#include "map.h"

void building_recruit(map*, building*, int);

void building_research(map*, building*, int);

void building_attack(map*, building*, int);

void building_ungarrison(map *, building *, int);

void building_info(building *);

void building_make_gate(map *, building *, int);

#endif
