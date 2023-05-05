#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <stdlib.h>

#include "spaceinvaders.h"

typedef struct {
    int id;
    int x;
    int y;
    bool isAlive;
} Alien;

typedef struct {
    Alien* first;
    int size;
} AlienGroup;


AlienGroup* (initAliens)();
void (moveAliens)(AlienGroup* group, enum direction dir, int speed);
void (dieAlien)(AlienGroup* group, Alien* alien);
void (drawAliens)(AlienGroup* group);
void (drawAlien)(Alien* alien);

#endif
