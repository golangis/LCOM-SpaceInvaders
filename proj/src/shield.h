#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

#include "shot.h"

#include "xpm/shield.xpm"

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int lives;
    int id;
} Shield;

Shield* (initShield)(int x_min, int id);
void (drawShield)(Shield* shield);
void (damage)(Shield* shield, enum shot_source src);

#endif
