#ifndef SHOT_H
#define SHOT_H

#include "spaceinvaders.h"

enum {
    alien,
    player
} shot_source;

typedef struct{
    int x;
    int y;
    enum shot_source source;
} Shot;

Shot* (initShot)(int x, int y, enum shot_source source);
void (moveShot)(Shot* shot);
void (drawShot)(Shot* shot);

#endif
