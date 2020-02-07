#ifndef COMBAT_H

#define COMBAT_H

#include "entity.h"

enum combat_type { combat_melee, combat_ranged };

void combat(entity*, entity*, enum combat_type);

void combat_calc(entity*, entity*, int&, int&, enum combat_type, int);

void combat_results(entity*, entity*, enum combat_type type);

#endif
