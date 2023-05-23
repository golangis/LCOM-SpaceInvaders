#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    int y;
    int thickness;
    int lives;
} Shield;

Shield* (initShield)(int x_min);
void (drawShield)(Shield* shield);
void (damage)(Shield* shield);

#endif
