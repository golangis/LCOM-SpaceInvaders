#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

typedef struct {
    unsigned int x_min;
    unsigned int x_max;
    unsigned int y_min;
    unsigned int y_max;
    unsigned int y;
    unsigned int thickness;
    unsigned int lives;
} Shield;

Shield* (initShield)(unsigned int x_min);
void (drawShield)(Shield* shield);
void (damage)(Shield* shield);

#endif
