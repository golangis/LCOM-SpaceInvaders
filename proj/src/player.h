#ifndef PLAYER_H
#define PLAYER_H

#include "spaceinvaders.h"

typedef struct {
    int x;
    int y;
    int lives;
    int score;
} Player;

Player* initPlayer();
void move(Player* player, direction direction);
void fire(Player* player);
void looseLife(Player* player);
void drawPlayer(Player* player);
void incrementScore(Player* player, int n);

#endif
