#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <stdlib.h>

#include "direction.h"

#include "framework/video/video.h"

typedef struct {
    int id;
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    bool isAlive;
} Alien;

typedef struct {
    Alien* first;
    int size;
} AlienGroup;

AlienGroup* (initAliens)();
void (initAlien)(Alien* alien, int id, int x_min, int y_min);
void (moveAliens)(AlienGroup* group, enum direction dir, int speed);
void (dieAlien)(AlienGroup* group, Alien* alien);
void (drawAliens)(AlienGroup* group);
void (drawAlien)(Alien* alien);

#endif
