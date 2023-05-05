#ifndef ALIEN_H
#define ALIEN_H

#include <stdbool.h>
#include <stdlib.h>

#include "framework/video/video.h"
#include "spaceinvaders.h"

typedef struct {
    int id;
    int x;
    int y;
    bool isAlive;
} Alien;

typedef struct {
    Alien* aliens;
    int size;
} AlienGroup;


void initAliens(AlienGroup* group);
void moveAliens(AlienGroup* group, direction dir, int speed);
void dieAliens(AlienGroup* group, Alien* alien);

#endif
