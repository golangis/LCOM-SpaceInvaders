#include <lcom/lcf.h>
#include <stdbool.h>
#include <stdint.h>

#include "spaceinvaders.h"

typedef struct {
    int id;
    int x;
    int y;
    bool isAlive;
} Alien;

typedef struct {
    Alien* aliens = (Alien*) malloc(sizeof(Alien) * 30);
    int size = 30;
} AlienGroup;

void init(AlienGroup* group);
void move(AlienGroup* group, direction direction, int speed);
void die(AlienGroup* group, Alien* alien);
