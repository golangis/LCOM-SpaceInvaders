#ifndef SHOT_H
#define SHOT_H

#include "framework/video/video.h"

enum shot_source {
    alien,
    player
};

typedef struct{
    unsigned int x;
    unsigned int y;
    enum shot_source source;
} Shot;

Shot (initShot)(unsigned int x, unsigned int y, enum shot_source source);
void (moveShot)(Shot* shot);
void (drawShot)(Shot* shot);

#endif
