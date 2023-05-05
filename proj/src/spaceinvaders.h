#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <stdlib.h>

#include "framework/video/video.h"
#include "alien.h"
#include "player.h"
#include "shield.h"
#include "shot.h"

extern char* video_mem;
extern uint8_t* vg_buffer;
extern unsigned h_res;
extern unsigned v_res;
extern unsigned bytes_per_pixel;

Player* player;
Shield* shield1;
Shield* shield2;
Shield* shield3;
AlienGroup* aliens;

typedef enum direction {
    right,
    left,
    up,
    down
} direction;

void (init_game)();
void (draw)();

#endif
