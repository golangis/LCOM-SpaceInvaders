#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"

#include "framework/video/video.h"
#include "xpm/rocket.xpm"

typedef struct {
    unsigned int x_min;
    unsigned int y_min;
    unsigned int x_max;
    unsigned int y_max;
    unsigned int lives;
    unsigned int score;
} Player;

Player* (initPlayer)();
void (movePlayer)(Player* ship, enum direction dir);
void (fire)(Player* ship);
void (looseLife)(Player* ship);
void (drawPlayer)(Player* ship);
void (incrementScore)(Player* ship, unsigned int n);

#endif
