#ifndef SPACEINVADERS_H
#define SPACEINVADERS_H

#include <stdlib.h>

#include "framework/video/video.h"
#include "framework/mouse/mouse.h"

#include "alien.h"
#include "player.h"
#include "shield.h"
#include "shot.h"

#include "direction.h"
#include "xpm/logo.xpm"
#include "xpm/play-button.xpm"
#include "xpm/mouse.xpm"

extern char* video_mem;
extern uint8_t* vg_buffer;
extern unsigned h_res;
extern unsigned v_res;
extern unsigned bytes_per_pixel;

Player* ship;
Shield* shield1;
Shield* shield2;
Shield* shield3;
AlienGroup* aliens;
Shot* shots;

enum direction last_alien_mov;
unsigned int updates;

void (init_game)();
void (draw)();
void (update)();
void (drawMenu)();

enum state {
  game,
  menu
};

#endif
