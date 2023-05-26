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
    Shot* shots;
    int shots_no;
    bool alive;
} Alien;

typedef struct {
    Alien* set;
    int size;
    int alive_no;
} AlienGroup;

AlienGroup* (initAliens)();
Alien (initAlien)(int id, int x_min, int y_min);
void (moveAliens)(AlienGroup* group, enum direction dir);
void (dieAlien)(AlienGroup* group, int i);
void (shootAlien)(Alien* a);
void (shootAliens)(AlienGroup* group);
void (deleteAlienShot)(Alien* alien, int i);
bool (canAlienMove)(Alien* alien, enum direction dir);
bool (canAlienGroupMove)(AlienGroup* group, enum direction dir);
bool (wasIHitAlien)(Alien* alien, Shot* shot);
int (hitIndex)(AlienGroup* group, Shot* shot);
void (drawAliens)(AlienGroup* group);
void (drawAlien)(Alien* alien);

#endif
