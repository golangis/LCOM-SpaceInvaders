#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

#include "shot.h"

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int lives;
} Shield;

Shield* (initShield)(int x_min);
void (drawShield)(Shield* shield);
void (damage)(Shield* shield, enum shot_source src);

#endif
