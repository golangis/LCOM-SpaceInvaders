#ifndef SHIELD_H
#define SHIELD_H

#include "framework/video/video.h"

typedef struct {
    unsigned int x;
    unsigned int y;
    unsigned int thickness;
    unsigned int lives;
} Shield;

Shield* (initShield)(unsigned int x);
void (drawShield)(Shield* shield);
void (damage)(Shield* shield);

#endif
