#ifndef SHOT_H
#define SHOT_H

#include "spaceinvaders.h"

typedef struct{
    int x;
    int y;
} Shot;

void moveShot(Shot* shot, direction direction);
void drawShot(Shot* shot);

#endif
