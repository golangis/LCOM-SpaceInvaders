#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"
#include "shot.h"

#include "framework/video/video.h"
#include "xpm/rocket.xpm"

typedef struct {
    int x_min;
    int y_min;
    int x_max;
    int y_max;
    int lives;
    int score;
    Shot* shots;
    int shots_no;
} Player;

Player* (initPlayer)();
void (movePlayer)(Player* ship, enum direction dir);
bool (canPlayerMove)(Player* ship, enum direction dir);
void (fire)(Player* ship);
void (looseLife)(Player* ship);
void (deletePlayerShot)(Player* ship, int i);
void (drawPlayer)(Player* ship);
void (incrementScore)(Player* ship, int n);

#endif
