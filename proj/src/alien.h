#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <stdlib.h>

#include "direction.h"

#include "xpm/aliens.xpm"

#include "framework/video/video.h"

#include "shot.h"

typedef struct {
    int id;
    int x_min;
    int y_min;
    int x_max;
    int y_max;
} Alien;

typedef struct {
    Alien* set;
    int size;
} AlienGroup;

AlienGroup* (initAliens)();
Alien (initAlien)(int id, int x_min, int y_min);
void (moveAliens)(AlienGroup* group, enum direction dir);
void (dieAlien)(AlienGroup* group, int i);
bool (canAlienMove)(Alien* alien, enum direction dir);
bool (canAlienGroupMove)(AlienGroup* group, enum direction dir);
bool (wasIHit)(Alien* alien, Shot* shot);
int (hitIndex)(AlienGroup* group, Shot* shot);
void (drawAliens)(AlienGroup* group);
void (drawAlien)(Alien* alien);

#endif
