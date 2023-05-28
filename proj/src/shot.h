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

Shot (init_shot)(int x, int y, enum shot_source source);
void (move_shot)(Shot* shot);
void (draw_shot)(Shot* shot);

#endif
