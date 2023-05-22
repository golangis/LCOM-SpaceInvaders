#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <stdlib.h>

#include "direction.h"

#include "framework/video/video.h"

typedef struct {
    unsigned int id;
    unsigned int x_min;
    unsigned int y_min;
    unsigned int x_max;
    unsigned int y_max;
    bool isAlive;
} Alien;

typedef struct {
    Alien* first;
    unsigned int size;
} AlienGroup;

AlienGroup* (initAliens)();
void (initAlien)(Alien* alien, unsigned int id, unsigned int x_min, unsigned int y_min);
void (moveAliens)(AlienGroup* group, enum direction dir, unsigned int speed);
void (dieAlien)(AlienGroup* group, Alien* alien);
void (drawAliens)(AlienGroup* group);
void (drawAlien)(Alien* alien);

#endif
