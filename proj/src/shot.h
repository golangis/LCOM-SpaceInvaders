#ifndef SHOT_H
#define SHOT_H

#include "framework/video/video.h"

enum shot_source {
    alien,
    player
};

typedef struct {
    int x_min;
    int x_max;
    int y_min;
    int y_max;
    enum shot_source source;
} Shot;

Shot (initShot)(int x, int y, enum shot_source source);
void (moveShot)(Shot* shot);
void (drawShot)(Shot* shot);

#endif
