#ifndef PLAYER_H
#define PLAYER_H

#include "direction.h"
#include "shot.h"

#include "framework/video/video.h"

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
void (incrementScore)(Player* ship, int id);
void (drawScore)(Player* ship);
void (draw_score_aux)(uint16_t x, uint16_t y, int score);
void (loop_draw_score_aux)(uint16_t x, uint16_t y, int score);
void (drawLives)(int lives);

#endif
