#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"

#include "framework/video/video.h"

typedef struct {
    unsigned int x;
    unsigned int y;
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
