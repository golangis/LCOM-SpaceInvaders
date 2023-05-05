#include "player.h"

Player* (initPlayer)(){
  Player* player = (Player*) malloc (sizeof(Player));

  player->x = 400;
  player->y = 480;
  player->lives = 3;
  player->score = 0;

  return player;
}

void (movePlayer)(Player* player, enum direction dir) {
  player->x += dir == left ? -1 : 1;
}

void (fire)(Player* player) {
  /*
  create shot
  */
}

void (looseLife)(Player* player) {
  player->lives--;
}

void (drawPlayer)(Player* player) {
  vg_draw_rectangle(player->x, player->y, 20, 20, 0xfffffff);
}

void (incrementScore)(Player* player, int n) {
  player->score += n;
}
