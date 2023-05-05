#ifndef DRAW_H
#define DRAW_H

#include "framework/video/video.h"
#include "alien.h"
#include "player.h"
#include "shield.h"
#include "shot.h"

extern char* video_mem;
extern uint8_t* vg_buffer;
extern unsigned h_res;
extern unsigned v_res;
extern unsigned bits_per_pixel;
extern unsigned bytes_per_pixel;

extern Shield* shield1;
extern Shield* shield2;
extern Shield* shield3;

void draw();

#endif
