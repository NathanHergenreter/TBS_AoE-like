#ifndef UNIT_COMMANDS_H

#define UNIT_COMMANDS_H

#include "entity.h"
#include "map.h"

void unit_move(map*, unit*, int);

void unit_construct(map*, unit*, int);

void unit_melee(map*, unit*, int);

void unit_ranged(map*, unit*, int);

void unit_garrison(map *, unit *, int);

void unit_ungarrison(map *, unit *, int);

void unit_upgrade(map *, unit *, int);

void unit_info(unit *);

#endif
